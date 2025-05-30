#include "../include/Log.h"
#include "Database.h"
#include <cstdlib>
#include <iostream>

int main() {

  Database<Log> db("./data/db-test.txt");

  Log lg(1, 1);
  Log lg1(2, 2);
  //  std::cout << lg.GetLogString();

  db.Create(lg);
  db.Create(lg1);
  db.GetById(2);
  db.DeleteById(4);

  return EXIT_SUCCESS;
}
