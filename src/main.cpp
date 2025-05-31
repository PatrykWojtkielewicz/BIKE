#include "../include/Log.h"
#include "Database.h"
#include <cstdlib>

int main() {

  Database<Log> db("./data/db-test.txt");

  Log lg(1, 1);
  Log lg1(2, 2);

  db.Create(lg);
  db.Create(lg1);
  Log lgsub(3, 3);
  db.SetById(2, lgsub);

  return EXIT_SUCCESS;
}
