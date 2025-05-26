#ifndef DATABASE_H
#define DATABASE_H

#include <fstream>
#include <iostream>
#include <vector>

template <typename T> class Database {
  std::vector<T> localData;
  std::fstream fileData;

public:
  ~Database() { fileData.close(); }
  Database(std::string path) : fileData(std::fstream(path)) {
    try {
      fileData.exceptions(std::fstream::failbit | std::fstream::badbit);
    } catch (const std::fstream::failure &e) {
      std::cerr << e.what();
      throw;
    }
  }

  // Set of basic crud operations

  T &GetById();                   // Read
  void SetById(size_t id, T obj); // update
  void Create(T obj);             // create
  void DeleteById();              // delete

  // Synchronize data with filedata
  // (in case of a conflict, file data is always right)
  void SyncData();

  // Loads a record into localData from the associated by Id
  T &LoadRecord(size_t id);

  // Unloads from localData by Id
  void UnloadRecord(size_t id);
};

#endif
