#include "../include/Log.h"
#include "../include/RentLog.h"
#include "../include/ReturnLog.h"
#include <cstdlib>
#include <iostream>

int main() {
  ReturnLog lg(1, 1);
  std::cout << lg.GetLogString();
  lg.SaveToFile("log.txt");

  return EXIT_SUCCESS;
}
