#ifndef GUI_H
#define GUI_H

#include "GUINode.h"
#include "State.h"
#include <sstream>

class GUI {
  StationsEnum currItem;
  std::array<GUINode<void, size_t>, stationsSize> items;
  void Render();
  void NextItem();
  void PreviousItem();
  static void RenderStation(size_t);

public:
  GUI() : currItem(static_cast<StationsEnum>(0)) {
    items[0].Focus();

    for (size_t i = 0; i < stationsSize; ++i) {
      items[i].SetActivatedFunction(RenderStation);

      std::ostringstream oss;
      oss << "Station " << i;

      items[i].SetContent(oss.str());
    }
  }

  void Start();
  static char GetKeyPress();
  static void Clear();
};
#endif
