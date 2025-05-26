#include "../include/Log.h"
#include <cstdlib>
#include <iostream>

int main() {
  Log lg(1, 1);
  std::cout << lg.GetLogString();
  return EXIT_SUCCESS;
}
