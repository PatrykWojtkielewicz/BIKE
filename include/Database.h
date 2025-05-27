#ifndef DATABASE_H
#define DATABASE_H

#include <algorithm>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

template <typename T> class Database {
  std::vector<T> localData;
  std::fstream fileData;

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

      if (fileData.eof())
        return maxId;

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

  void DecodeCurrLine(T &obj) {
    std::stringstream ss;
    std::string line;
    getline(fileData, line);
    ss << line.substr(0, line.find_last_of(";"));
    ss >> obj;
  }

public:
  ~Database() { fileData.close(); }

  Database(std::string path)
      : fileData(path, std::ios_base::in | std::ios_base::out) {

    if (!fileData) {
      std::ofstream create(path);
      create.close();
      fileData = std::fstream(path, std::ios_base::in | std::ios_base::out);
    }

    if (!fileData.is_open())
      throw std::ios_base::failure("Failed to open database file");

    fileData.exceptions(std::fstream::failbit | std::fstream::badbit);

    T::idCounter = GetBiggestId();
  }

  // Set of basic crud operations

  T GetById(size_t id) { // Read

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

  void SetById(size_t id, T obj); // update

  void Create(T obj) { // create

    try {

      if (IsIdTaken(obj.id))
        throw IdCollision();

      std::ostringstream oss;

      // TODO: think about adding human-readable timestamps
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

  void DeleteById(); // delete

  // Synchronize data with filedata
  // (in case of a conflict, file data is always right)
  void SyncData() {}

  // Loads a record into localData from the associated by Id
  T &LoadRecord(size_t id);

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
