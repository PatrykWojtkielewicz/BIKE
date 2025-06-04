#include "GUI.h"
#include "GUINode.h"
#include <cstdlib>
#include <sstream>

#ifdef WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

void GUI::Start() {
  char choice;
  while (true) {
    Render();

    choice = GetKeyPress();
    switch (choice) {
    case 'w':
      NextItem();
      break;
    case 's':
      PreviousItem();
      break;
    case 'd':
      items[static_cast<int>(currItem)].Activate(static_cast<int>(currItem));
      break;
    default:;
    }
  }
}

void GUI::Render() {
  Clear();
  for (auto item : items) {
    std::cout << "[" << (item.IsFocused() ? "\033[36m*\033[0m" : " ") << "]"
              << item.GetContent() << "\n";
  }
}

void GUI::PreviousItem() {
  this->items[static_cast<int>(currItem--)].Unfocus();
  this->items[static_cast<int>(currItem)].Focus();
}

void GUI::NextItem() {
  this->items[static_cast<int>(currItem++)].Unfocus();
  this->items[static_cast<int>(currItem)].Focus();
}

void GUI::Clear() {
#ifdef WIN32
  system("cls");
#else
  system("clear");
#endif
}

char GUI::GetKeyPress() {
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

void GUI::RenderStation(size_t stationId) {
  extern State state;
  extern size_t userId;
  std::vector<GUINode<void, size_t, size_t>> nodes;

  char choice;
  while (true) {
    GUI::Clear();

    std::vector<GUINode<void, size_t, size_t>>::iterator nodesIt =
        nodes.begin();

    for (auto item : state.GetStationById(stationId).bikeIds) {
      std::ostringstream oss;
      oss << item;
      nodesIt->SetContent(oss.str());
      nodesIt->SetActivatedFunction(
          std::bind(&State::RentBike, &state, item, userId));

      nodesIt++;
    }

    for (auto item : nodes) {
      std::cout << "[" << (item.IsFocused() ? "\033[36m*\033[0m" : " ") << "]"
                << item.GetContent() << "\n";
    }

    choice = GUI::GetKeyPress();
    switch (choice) {
    case 'w':
      break;
    case 's':
      break;
    case 'd':
      break;
    default:;
    }
  }
}
