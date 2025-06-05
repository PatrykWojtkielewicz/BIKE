#ifndef GUI_MENU_H
#define GUI_MENU_H
#include "GUINode.h"
#include <memory>
#include <vector>

class GUIMenu {
  std::vector<std::unique_ptr<GUINodeBase>> nodes;
  size_t currItem;

public:
  GUIMenu() : currItem(0){};

  void AddNode(std::unique_ptr<GUINodeBase>);

  template <typename T> void AddNode(std::unique_ptr<GUINode<T>> &&node) {
    nodes.emplace_back(node.release());
  };

  template <typename T, typename... Args> void CreateNode(Args &&...args) {
    nodes.emplace_back(new GUINode<T>(std::forward<Args>(args)...));
  };

  void Render();
  void NextItem();
  void PreviousItem();

  void
  InputHandler(std::function<void(std::vector<std::unique_ptr<GUINodeBase>> &)>
                   reloadData);
  void InputHandler();
  static char GetKeyPress();
  static void Clear();

  void PrintLowerBar();

  class RequestToExit : public std::runtime_error {
  public:
    explicit RequestToExit(const std::string &message = "")
        : std::runtime_error(message) {}
  };

  class RequestToContinue : public std::runtime_error {
  public:
    explicit RequestToContinue(const std::string &message = "")
        : std::runtime_error(message) {}
  };
};
#endif
