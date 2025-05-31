#ifndef DATABASE_H
#define DATABASE_H

#include "DatabaseEntry.h"
#include <algorithm>
#include <boost/filesystem/operations.hpp>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iosfwd>
#include <iostream>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

template <typename T> class Database {

  static_assert(std::is_base_of<DatabaseEntry<T>, T>::value,
                "Database can only store types derived from DatabaseEntry<T>");

  std::vector<T> localData;
  std::fstream fileData;
  std::string filepath;

  bool IsIdTaken(size_t id) {

    try {
      FindInFileById(id);
    } catch (const NoRecordsFound &e) {
      return false;
    }

    return true;
  }

  size_t GetBiggestId() {

    size_t maxId = 0;
    size_t curId;

    std::string line;
    std::stringstream ss;

    try {
      fileData.clear();
      fileData.seekg(0);
      fileData.seekp(0);

      while (getline(fileData, line)) {

        ss.clear();
        ss.str("");
        ss << line.substr(0, line.find(";"));
        ss >> curId;

        maxId = curId > maxId ? curId : maxId;
      }
    } catch (const std::ios_base::failure &e) {
      if (!fileData.eof())
        throw;
    }
    return maxId; // It's here just to avoid warnings
  }

  void FindInFileById(size_t id) {

    std::string line;
    std::stringstream ss;
    size_t curId;
    std::streampos curLinePos;

    try {
      fileData.clear();
      fileData.seekg(0);
      curLinePos = 0;

      while (((curLinePos = fileData.tellg()) | true) &&
             getline(fileData, line)) {

        ss.clear();
        ss.str("");
        std::streampos delimPos = line.find(";");

        if (delimPos == std::string::npos)
          throw InvalidRecordFormat("Invalid record format \';\' not found");

        ss << line.substr(0, delimPos);
        ss >> curId;

        if (curId == id) {
          fileData.seekp(curLinePos);
          return;
        }
      }

    } catch (const std::ios_base::failure &e) {

      if (fileData.eof())
        throw NoRecordsFound("End of file reached, no records found");
      std::cerr << std::endl << e.code() << std::endl;
      throw;
    } catch (const InvalidRecordFormat &e) {
      std::cerr << e.what() << std::endl; // TODO: add invalid row deletion
    }
  }

  time_t DecodeCurrLine(T &obj) {
    std::stringstream ss, tstampss;
    std::string line;
    time_t timestamp;

    getline(fileData, line);
    ss << line.substr(0, line.find_last_of(";"));
    tstampss << line.substr(line.find_last_of(";"), line.length() - 1);
    tstampss >> timestamp;
    ss >> obj;
    return timestamp;
  }

public:
  ~Database() { fileData.close(); }

  Database(std::string path) : filepath(path) { setupFile(); }

  void setupFile() {

    if (fileData.is_open())
      fileData.close();

    fileData = std::fstream(filepath, std::ios_base::in | std::ios_base::out);

    if (!fileData) {
      std::ofstream create(filepath);
      create.close();
      fileData = std::fstream(filepath, std::ios_base::in | std::ios_base::out);
    }

    if (!fileData.is_open())
      throw std::ios_base::failure("Failed to open database file");

    fileData.exceptions(std::fstream::failbit | std::fstream::badbit);

    T::idCounter = GetBiggestId();
  }

  // Set of basic crud operations

  T GetById(size_t id) { // read

    auto objIter = std::find_if(localData.begin(), localData.end(),
                                [&](const T &obj) { return obj.id == id; });

    if (objIter != localData.end())
      return *objIter;

    FindInFileById(id);
    T obj;
    DecodeCurrLine(obj);
    localData.push_back(obj);
    return obj;
  }

  void SetById(size_t id, T &obj) { // update

    FindInFileById(id);

    T old;
    DecodeCurrLine(old);

    obj.id = id;
    if (obj == old)
      return;

    DeleteById(id);
    Create(obj);
  }

  void Create(T obj) { // create

    try {

      if (IsIdTaken(obj.id))
        throw IdCollision();

      std::ostringstream oss;

      oss << obj << ";" << std::time(nullptr) << "\n";
      localData.push_back(obj);

      fileData.clear();
      fileData.seekp(0, std::ios::end);
      fileData << oss.str();

    } catch (const std::fstream::failure &e) {
      std::cerr << e.what() << std::endl;
      throw;
    } catch (const IdCollision &e) {
      std::cerr << e.what() << std::endl;
      throw;
    }
  }

  void DeleteById(size_t id) { // delete

    std::remove_if(localData.begin(), localData.end(),
                   [&](T obj) { return obj.id == id; });

    std::ostringstream ossPath;
    ossPath << "./data/tmp-" << std::time(nullptr) << "-" << std::rand()
            << ".txt";

    std::string rndPath = ossPath.str();

    if (boost::filesystem::exists(rndPath))
      if (std::remove(rndPath.c_str()) != 0)
        throw std::ios_base::failure("Error fallback cleanup failed");

    std::fstream tmpFile(rndPath, std::fstream::app);

    if (!tmpFile.is_open()) {
      if (std::remove(rndPath.c_str()) != 0)
        throw std::ios_base::failure("Error fallback cleanup failed");

      throw std::ios_base::failure("Failed to create a tmp file");
    }

    try {
      FindInFileById(id);

      fileData.clear();
      std::streampos lineToDel = fileData.tellg();

      if (lineToDel == std::fstream::pos_type(-1))
        throw NoRecordsFound();

      std::streampos curLinePos = 0;
      std::string line;

      fileData.seekg(0);

      while (((curLinePos = fileData.tellg()) | true) &&
             getline(fileData, line)) {

        if (lineToDel == curLinePos)
          continue;

        tmpFile << line << '\n';
      }

    } catch (const NoRecordsFound &e) {
      std::cerr << "Cannot delete non-existent object" << std::endl;

      if (std::remove(rndPath.c_str()) != 0)
        throw std::ios_base::failure("Error fallback cleanup failed");

      throw;

    } catch (const std::ios_base::failure &e) {
      if (!fileData.eof()) {
        std::cerr << e.what() << std::endl;
        if (std::remove(rndPath.c_str()) != 0)
          throw std::ios_base::failure("Error fallback cleanup failed");

        throw;
      }
    }

    try {

      tmpFile.close();
      fileData.close();

      if (std::remove(filepath.c_str()) != 0)
        throw std::ios_base::failure("Failed to remove old db file");

      if (std::rename(rndPath.c_str(), filepath.c_str()) != 0)
        throw std::ios_base::failure("Failed to move tmp file");

      setupFile();

    } catch (const std::ios_base::failure &e) {
      std::cerr << e.what() << std::endl;

      if (std::remove(rndPath.c_str()) != 0)
        throw std::ios_base::failure("Error fallback cleanup failed");

      throw;
    }
  }

  // tbh it's not that important, it just works rn without those methods
  // Synchronize data with filedata
  // (in case of a conflict, file data is always right)
  void SyncData() {}

  // Loads a record into localData from the associated file by Id
  T &LoadRecord(size_t id) {}

  // Unloads from localData by Id
  void UnloadRecord(size_t id);

  class IdCollision : public std::runtime_error {
  public:
    explicit IdCollision(
        const std::string &message = "Entry with a given id already exists")
        : std::runtime_error(message) {}
  };

  class NoRecordsFound : public std::runtime_error {
  public:
    explicit NoRecordsFound(const std::string &message = "End of file reached")
        : std::runtime_error(message) {}
  };

  class InvalidRecordFormat : public std::runtime_error {
  public:
    explicit InvalidRecordFormat(
        const std::string &message = "Invalid record format")
        : std::runtime_error(message) {}
  };
};

#endif
