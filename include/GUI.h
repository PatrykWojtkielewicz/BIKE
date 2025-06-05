#ifndef GUI_H
#define GUI_H
#include "GUINode.h"
#include <memory>
#include <vector>
class GUI {
public:
  void Start();
  void SynchronizeStationNodesContent();
  void AdminPanelAddBike();
  void StartAdminPanel();
  void StartStationsPanel();
  void StartStationContentPanel(size_t);
  void SynchronizeStationNodesContent(
      std::vector<std::unique_ptr<GUINodeBase>> &nodes);
  void StartLogsPanel(size_t);
};
#endif
