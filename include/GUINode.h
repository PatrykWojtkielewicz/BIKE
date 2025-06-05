#ifndef GUI_NODE_H
#define GUI_NODE_H
#include <cstdlib>
#include <functional>
#include <stdexcept>
#include <string>
#include <tuple>
#include <type_traits>

template <size_t... Is> struct index_sequence {};

template <size_t N, size_t... Is>
struct make_index_sequence : make_index_sequence<N - 1, N - 1, Is...> {};

template <size_t... Is>
struct make_index_sequence<0, Is...> : index_sequence<Is...> {};

class GUINodeBase {
protected:
  bool isFocused;
  std::string content;

public:
  virtual ~GUINodeBase() = default;
  GUINodeBase(bool isFocused, std::string content)
      : isFocused(isFocused), content(content) {}

  virtual void Activate() = 0;

  void Focus() { isFocused = true; }
  void Unfocus() { isFocused = false; }

  void SetContent(std::string str) { content = str; }
  std::string GetContent() { return content; }
  bool IsFocused() { return isFocused; }
};

template <typename T> class GUINode : public GUINodeBase {
  std::function<T()> boundFunction;

public:
  GUINode(bool isFocused = false, std::string content = "Placeholder")
      : GUINodeBase(isFocused, content) {}

  template <typename Func, typename... Args>
  void SetActivatedFunction(Func &&func, Args &&...args) {
    boundFunction = [=]() { return func(args...); };
  }

  void Activate() override {
    if (boundFunction) {
      boundFunction();
    }
  }

  template <typename... CallArgs> T Activate(CallArgs &&...args) {
    if (boundFunction) {
      return boundFunction(args...);
    }
    return T();
  }
};

#endif
