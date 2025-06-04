#ifndef GUI_NODE_H
#define GUI_NODE_H
#include <cstdlib>
#include <functional>
#include <string>
#include <type_traits>

template <typename T, typename... Args> class GUINode {
  bool isFocused;
  std::string content;
  std::function<T(Args...)> activatedFunction;

public:
  GUINode(bool isFocused = false, std::string content = "Placeholder",
          std::function<T(Args...)> fn = nullptr)
      : isFocused(isFocused), content(content), activatedFunction(fn) {}

  bool IsFocused() { return isFocused; }
  std::string GetContent() { return content; }

  void Focus() { isFocused = true; }
  void Unfocus() { isFocused = false; }

  void SetContent(std::string str) { content = str; }

  template <typename U = T>
  typename std::enable_if<std::is_same<U, void>::value, void>::type
  Activate(Args... args) {
    if (activatedFunction) {
      activatedFunction(args...);
    }
  }

  template <typename U = T>
  typename std::enable_if<!std::is_same<U, void>::value, T>::type
  Activate(Args... args) {
    if (!activatedFunction) {
      return T();
    }
    return activatedFunction(args...);
  }

  void SetActivatedFunction(std::function<T(Args...)> fn) {
    activatedFunction = fn;
  }
};

#endif
