#include "GUI.h"
#include "Database.h"
#include "GUIMenu.h"
#include "GUINode.h"
#include "State.h"
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <vector>

#ifdef WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

void GUI::Start() {
  extern size_t userId;
  extern State state;

  std::string mail, password;

  std::cout << "Mail: ";
  std::cin >> mail;
  std::cout << "Password: ";
  std::cin >> password;

  bool isAdmin = false;

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
  if (!isAdmin) {
    StartStationsPanel();
  } else {
    StartAdminPanel();
  }
}

void GUI::StartAdminPanel() {
  extern State state;
  GUIMenu guimAdmin;

  auto node = std::unique_ptr<GUINode<void>>(new GUINode<void>());
  node->SetContent("Add Bike");
  node->SetActivatedFunction([]() {
    GUIMenu::Clear();

    size_t stationId;
    std::cout << "Provide station id: ";
    std::cin >> stationId;

    if (stationId >= stationsSize) {
      GUIMenu::Clear();
      std::cout << "Invalid station id, press anything to continue"
                << std::endl;

      GUIMenu::GetKeyPress();
      throw GUIMenu::RequestToContinue();
    }

    Bike bk(stationId);
    state.AddToDatabase(bk);
  });

  guimAdmin.AddNode(std::move(node));
  guimAdmin.InputHandler();
}

void GUI::StartStationsPanel() {
  extern State state;
  extern size_t userId;

  GUIMenu guimStations;

  for (size_t i = 0; i < stationsSize; ++i) {

    auto node = std::unique_ptr<GUINode<void>>(new GUINode<void>());
    Station curStation = state.GetStationById(i);
    std::ostringstream oss;

    oss << i + 1 << " Station " << curStation.GetNonZeroFieldsSize() << "/"
        << curStation.GetCapacity();

    node->SetContent(oss.str());
    node->SetActivatedFunction([this, i]() { StartStationContentPanel(i); });

    guimStations.AddNode(std::move(node));
  }

  auto node = std::unique_ptr<GUINode<void>>(new GUINode<void>());

  size_t userIdCopy = userId;

  node->SetContent("View History");

  node->SetActivatedFunction(
      [this, userIdCopy]() { StartLogsPanel(userIdCopy); });

  guimStations.AddNode(std::move(node));

  guimStations.InputHandler(
      [this](std::vector<std::unique_ptr<GUINodeBase>> &nodes) {
        SynchronizeStationNodesContent(nodes);
      });
}

void GUI::SynchronizeStationNodesContent(
    std::vector<std::unique_ptr<GUINodeBase>> &nodes) {
  extern State state;

  size_t i = 0;
  for (auto &node : nodes) {
    if (i >= stationsSize)
      continue;
    Station curStation = state.GetStationById(i);

    std::ostringstream oss;
    oss << i + 1 << " Station " << curStation.GetNonZeroFieldsSize() << "/"
        << curStation.GetCapacity();

    node->SetContent(oss.str());
    ++i;
  }
}

void GUI::StartStationContentPanel(size_t stationId) {
  extern State state;
  extern size_t userId;
  GUIMenu guimStation;

  if (!state.GetStationById(stationId).GetNonZeroFieldsSize() &&
      !state.GetBikeIsTaken(state.GetUserBikeRented(userId))) {
    return;
  }

  for (auto i : state.GetStationById(stationId).bikeIds) {
    if (i == 0)
      continue;
    auto node = std::unique_ptr<GUINode<void>>(new GUINode<void>());

    std::ostringstream oss;
    oss << "Bike " << i;

    node->SetContent(oss.str());
    size_t userIdCopy = userId;
    node->SetActivatedFunction([i, userIdCopy]() {
      try {
        state.RentBike(i, userIdCopy);
      } catch (const std::runtime_error &e) {
        throw GUIMenu::RequestToExit(e.what());
      }
      throw GUIMenu::RequestToExit();
    });

    guimStation.AddNode(std::move(node));
  }

  if (state.GetBikeIsTaken(state.GetUserBikeRented(userId))) {
    auto node = std::unique_ptr<GUINode<void>>(new GUINode<void>());
    node->SetContent("Return bike Here");

    size_t bikeId = state.GetUserBikeRented(userId);

    node->SetActivatedFunction([bikeId, stationId]() {
      state.ReturnBike(bikeId, stationId);
      throw GUIMenu::RequestToExit();
    });

    guimStation.AddNode(std::move(node));
  }

  guimStation.InputHandler();
}

void GUI::StartLogsPanel(size_t id) {
  extern State state;

  GUIMenu guimLogs;
  std::shared_ptr<std::vector<std::string>> logs = state.GetUserLogs(id);

  for (auto log : *logs) {
    auto node = std::unique_ptr<GUINode<void>>(new GUINode<void>());
    node->SetContent(log);
    node->SetActivatedFunction([]() { return; });
    guimLogs.AddNode(std::move(node));
  }

  guimLogs.InputHandler();
}
