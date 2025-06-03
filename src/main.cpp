#include "../include/State.h"
#include "Bike.h"
#include <cstdlib>

constexpr char logDBPath[] = "./data/logs.txt";
constexpr char userDBPath[] = "./data/users.txt";
constexpr char bikeDBPath[] = "./data/bikes.txt";

int main() {

  State state(logDBPath, userDBPath, bikeDBPath);

  Bike bk(1);

  User newUser("Partyk", "Wojtulewicz", "Made-up@email.com");

  state.AddToDatabase(newUser);
  state.AddToDatabase(bk);

  state.RentBike(bk.id, newUser.id);

  state.ReturnBike(bk.id, 0);

  return EXIT_SUCCESS;
}
