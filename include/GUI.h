#ifndef GUI_H
#define GUI_H

#include "GUINode.h"
#include "State.h"

class GUI {
  StationsEnum currItem;
  std::array<GUINode<void, size_t>, stationsSize> items;
  void Render();
  void NextItem();
  void PreviousItem();
  static void RenderStation(size_t);
  void RenderAdminPanel();
  void SynchronizeStationNodesContent();
  void AdminPanelAddBike();

public:
  GUI() : currItem(static_cast<StationsEnum>(0)) {
    items[0].Focus();

    for (size_t i = 0; i < stationsSize; ++i) {
      items[i].SetActivatedFunction(RenderStation);
    }
    SynchronizeStationNodesContent();
  }

  void Start();
};
#endif
