#include "../include/State.h"
#include <cstdlib>

constexpr char logDBPath[] = "./data/logs.txt";
constexpr char userDBPath[] = "./data/users.txt";
constexpr char bikeDBPath[] = "./data/bikes.txt";

int main() {

  State state(logDBPath, userDBPath, bikeDBPath);

  return EXIT_SUCCESS;
}
