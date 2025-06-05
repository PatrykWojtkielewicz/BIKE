#include "GUIMenu.h"
#include "GUINode.h"
#include "State.h"
#include <ctime>
#include <functional>
#include <iomanip>
#include <iostream>
#include <memory>
#include <ostream>
#ifdef WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

char GUIMenu::GetKeyPress() {
#ifdef WIN32
  return _getch();
#else
  char buf = 0;
  struct termios old = {0};
  if (tcgetattr(0, &old) < 0)
    perror("tcsetattr()");
  old.c_lflag &= ~ICANON;
  old.c_lflag &= ~ECHO;
  old.c_cc[VMIN] = 1;
  old.c_cc[VTIME] = 0;
  if (tcsetattr(0, TCSANOW, &old) < 0)
    perror("tcsetattr ICANON");
  if (read(0, &buf, 1) < 0)
    perror("read()");
  old.c_lflag |= ICANON;
  old.c_lflag |= ECHO;
  if (tcsetattr(0, TCSADRAIN, &old) < 0)
    perror("tcsetattr ~ICANON");
  return buf;

#endif
}

void GUIMenu::Clear() {
#ifdef WIN32
  system("cls");
#else
  system("clear");
#endif
}

void GUIMenu::AddNode(std::unique_ptr<GUINodeBase> node) {
  nodes.push_back(std::move(node));
}

void GUIMenu::Render() {
  Clear();
  for (auto &item : nodes) {
    std::cout << "[" << (item->IsFocused() ? "\033[36m*\033[0m" : " ") << "]"
              << item->GetContent() << "\n";
  }
  PrintLowerBar();
}

void GUIMenu::PrintLowerBar() {

  std::cout << "w/s - move up/down" << "\n";
  std::cout << "a - go back/exit" << "\n";
  std::cout << "d - press button" << "\n";

  extern State state;
  extern size_t userId;

  if (state.GetBikeIsTaken(state.GetUserBikeRented(userId))) {
    std::cout << "\n\n";
    state.GetUserBikeRented(userId);
    time_t timeDiff = std::time(nullptr) - state.GetNewestUserActivity(userId);

    int hours = timeDiff / 3600;
    int minutes = (timeDiff % 3600) / 60;
    int seconds = timeDiff % 60;

    std::cout << "Bike rented for: " << std::setfill('0') << std::setw(2)
              << hours << ":" << std::setw(2) << minutes << ":" << std::setw(2)
              << seconds << std::endl;
  }
}

void GUIMenu::NextItem() {
  nodes[currItem]->Unfocus();
  currItem = (currItem + 1) % nodes.size();
  nodes[currItem]->Focus();
}

void GUIMenu::PreviousItem() {
  nodes[currItem]->Unfocus();
  currItem = (currItem - 1 + nodes.size()) % nodes.size();
  nodes[currItem]->Focus();
}

void GUIMenu::InputHandler(
    std::function<void(std::vector<std::unique_ptr<GUINodeBase>> &)>
        reloadData) {
  char choice;
  if (nodes.empty())
    return;

  for (auto &i : nodes)
    i->Unfocus();

  nodes[0]->Focus();

  while (true) {
    reloadData(nodes);
    Render();

    choice = GUIMenu::GetKeyPress();

    switch (choice) {
    case 'w':
      PreviousItem();
      break;
    case 's':
      NextItem();
      break;
    case 'd':
      try {
        nodes[currItem]->Activate();
      } catch (const RequestToExit &e) {
        return;
      } catch (const RequestToContinue &e) {
        continue;
      }

      break;

    case 'a':
      return;
    default:
      break;
    }
  }
}

void GUIMenu::InputHandler() {
  GUIMenu::InputHandler(
      [this](std::vector<std::unique_ptr<GUINodeBase>> &nodes) {});
}
