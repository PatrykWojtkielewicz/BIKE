#include "GUIMenu.h"
#include <iostream>
#include <memory>

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
}

void GUIMenu::NextItem() {
  nodes[currItem]->Unfocus();
  currItem = (currItem + 1) % currItem;
  nodes[currItem]->Focus();
}

void GUIMenu::PreviousItem() {
  nodes[currItem]->Unfocus();
  currItem = (currItem - 1 + currItem) % currItem;
  nodes[currItem]->Focus();
}

void GUIMenu::InputHandler() {
  char choice;

  for (auto &i : nodes)
    i->Unfocus();

  nodes[0]->Focus();

  while (true) {
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
      nodes[currItem]->Activate();
    case 'a':
      return;
    default:
      break;
    }
  }
}
