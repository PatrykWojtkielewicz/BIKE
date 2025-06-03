#include "../include/State.h"
#include "Bike.h"
#include <cstdlib>

constexpr char logDBPath[] = "./data/logs.txt";
constexpr char userDBPath[] = "./data/users.txt";
constexpr char bikeDBPath[] = "./data/bikes.txt";

int main() {

  State state(logDBPath, userDBPath, bikeDBPath);

  Bike bk(1);

  User newUser("Karol", "Bobryk", "Made-up@email");

  state.AddToDatabase(bk);
  state.AddToDatabase(newUser);

  state.RentBike(bk.id, newUser.id);

  Bike bkret = state.GetObjectById<Bike>(2);

  std::cout << bkret;

  return EXIT_SUCCESS;
}
