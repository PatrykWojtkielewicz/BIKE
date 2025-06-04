#include "../include/State.h"
#include "GUI.h"
#include "User.h"
#include <cstdlib>

constexpr char logDBPath[] = "./data/logs.txt";
constexpr char userDBPath[] = "./data/users.txt";
constexpr char bikeDBPath[] = "./data/bikes.txt";

State state(logDBPath, userDBPath, bikeDBPath);
size_t userId;

int main() {

  GUI gui;

  User usr("Karol", "Bobryk", "mail@com");

  state.AddToDatabase(usr);

  gui.Start();
  return EXIT_SUCCESS;
}
