#include "GUIMenu.h"
#include "State.h"
#include <cstdio>
#include <cstdlib>

constexpr char logDBPath[] = "./data/logs.txt";
constexpr char userDBPath[] = "./data/users.txt";
constexpr char bikeDBPath[] = "./data/bikes.txt";

State state(logDBPath, userDBPath, bikeDBPath);

size_t userId;

int main() {

  GUIMenu guim;

  guim.CreateNode<void>();
  guim.CreateNode<void>();
  guim.CreateNode<void>();

  guim.Render();
  guim.InputHandler();

  return EXIT_SUCCESS;
}
