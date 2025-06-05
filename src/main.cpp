#include "GUI.h"
#include "State.h"
#include <cstdio>
#include <cstdlib>

constexpr char logDBPath[] = "./data/logs.txt";
constexpr char userDBPath[] = "./data/users.txt";
constexpr char bikeDBPath[] = "./data/bikes.txt";

State state(logDBPath, userDBPath, bikeDBPath);

size_t userId;

int main() {

  // for (size_t i = 0; i < 10; ++i) {
  //   Bike bk(i % 2);
  //   state.AddToDatabase(bk);
  // }

  GUI gui;
  gui.Start();

  return EXIT_SUCCESS;
}
