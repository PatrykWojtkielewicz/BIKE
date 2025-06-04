#include "GUI.h"
#include "Database.h"
#include "GUINode.h"
#include <cstdlib>
#include <functional>
#include <sstream>
#include <stdexcept>

#ifdef WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

void GUI::Start() {
  extern size_t userId;
  extern State state;
  Clear();
  std::string mail, password;
  bool isAdmin = false;
  std::cout << "Mail: ";
  std::cin >> mail;
  std::cout << "Password: ";
  std::cin >> password;

  if (mail == "root" && password == "root")
    isAdmin = true;
  else {
    try {
      userId = state.CheckUserCredentials(mail, password);
    } catch (const Database<User>::NoRecordsFound &e) {
      std::cout << std::endl
                << e.what() << ", creating new account:" << std::endl;

      std::string name, surname;
      std::cout << "Name: ";
      std::cin >> name;
      std::cout << "Surname: ";
      std::cin >> surname;

      User newUsr(name, surname, mail, password);
      state.AddToDatabase(newUsr);
      userId = newUsr.id;
    }
  }

  char choice;

  if (!isAdmin) {

    while (true) {
      SynchronizeStationNodesContent();
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

  } else {

    while (true) {

      RenderAdminPanel();

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

void GUI::RenderStation(size_t stationId) {
  extern State state;
  extern size_t userId;
  std::vector<GUINode<void, size_t, size_t>> nodes;

  size_t curFocus = 0;

  for (auto item : state.GetStationById(stationId).bikeIds) {
    if (item == 0)
      continue;
    GUINode<void, size_t, size_t> node;
    std::ostringstream oss;
    oss << item;

    node.SetContent(oss.str());

    node.SetActivatedFunction(std::bind(&State::ReturnBike, &state,
                                        std::placeholders::_1,
                                        std::placeholders::_2));
    nodes.push_back(node);
  }

  if (state.GetBikeIsTaken(
          state.GetObjectById<User>(userId).GetBikeRentedId())) {
    GUINode<void, size_t, size_t> retNode;

    retNode.SetContent("Return Bike here");
    retNode.SetActivatedFunction(std::bind(&State::ReturnBike, &state,
                                           std::placeholders::_1,
                                           std::placeholders::_2));

    nodes.push_back(retNode);
  }

  if (!nodes.empty()) {
    nodes[0].Focus();
  }

  char choice;

  while (true) {
    GUI::Clear();

    for (auto item : nodes) {
      std::cout << "[" << (item.IsFocused() ? "\033[36m*\033[0m" : " ") << "]"
                << item.GetContent() << "\n";
    }

    choice = GUI::GetKeyPress();
    switch (choice) {

    case 'w':
      nodes[curFocus].Unfocus();
      curFocus = (curFocus - 1 + nodes.size()) % nodes.size();
      nodes[curFocus].Focus();
      break;

    case 's':
      nodes[curFocus].Unfocus();
      curFocus = (curFocus + 1) % nodes.size();
      nodes[curFocus].Focus();
      break;

    case 'd': {
      try {
        std::istringstream iss(nodes[curFocus].GetContent());
        size_t bikeId;
        iss >> bikeId;
        std::cout << bikeId << ";" << userId;
        nodes[curFocus].Activate(bikeId, userId);
      } catch (const std::runtime_error &e) { // ERROR HERE
        std::cout << e.what() << ", Press anything to continue" << "\n";
        GUI::GetKeyPress();
      }
      return;
      break;
    }

    case 'a':
      return;

    default:;
      break;
    }
  }
}

void GUI::SynchronizeStationNodesContent() {
  extern State state;
  for (size_t i = 0; i < stationsSize; ++i) {

    std::ostringstream oss;
    Station st = state.GetStationById(i);
    oss << i + 1 << ". Station " << st.GetNonZeroFieldsSize() << "/"
        << st.GetCapacity();

    items[i].SetContent(oss.str());
  }
}

void GUI::RenderAdminPanel() {
  extern State state;
  extern size_t userId;
  std::vector<GUINode<void>> nodes;

  size_t curFocus = 0;

  GUINode<void> addBikeNode;
  addBikeNode.SetContent("Add Bike");

  addBikeNode.SetActivatedFunction(std::bind(&GUI::AdminPanelAddBike, this));

  nodes.push_back(addBikeNode);

  char choice;

  nodes[0].Focus();

  while (true) {
    GUI::Clear();

    for (auto item : nodes) {
      std::cout << "[" << (item.IsFocused() ? "\033[36m*\033[0m" : " ") << "]"
                << item.GetContent() << "\n";
    }

    choice = GUI::GetKeyPress();
    switch (choice) {

    case 'w':
      nodes[curFocus].Unfocus();
      curFocus = (curFocus - 1 + nodes.size()) % nodes.size();
      nodes[curFocus].Focus();
      break;

    case 's':
      nodes[curFocus].Unfocus();
      curFocus = (curFocus + 1) % nodes.size();
      nodes[curFocus].Focus();
      break;

    case 'd': {
      try {
        nodes[curFocus].Activate();
      } catch (const std::runtime_error &e) {
        std::cout << e.what() << ", Press anything to continue" << "\n";
        GUI::GetKeyPress();
      }
      break;
    }

    default:;
      break;
    }
  }
}

void GUI::AdminPanelAddBike() {
  extern State state;
  size_t stationId;
  std::cout << "Station id: ";
  std::cin >> stationId;
  Bike newBk(stationId);
  state.AddToDatabase(newBk);
}
