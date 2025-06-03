#include "../include/State.h"
#include "Bike.h"
#include <cstdlib>

constexpr char logDBPath[] = "./data/logs.txt";
constexpr char userDBPath[] = "./data/users.txt";
constexpr char bikeDBPath[] = "./data/bikes.txt";

int main() {

  State state(logDBPath, userDBPath, bikeDBPath);

  Bike bk(1);

  state.AddToDatabase(bk);

  Bike bkret = state.GetObjectById<Bike>(2);

  std::cout << bkret;

  return EXIT_SUCCESS;
}
