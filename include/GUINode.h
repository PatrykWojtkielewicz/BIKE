#ifndef GUI_NODE_H
#define GUI_NODE_H
#include <cstdlib>
#include <functional>
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

  bool IsFocused() { return isFocused; }
  virtual void Activate() = 0;

  void Focus() { isFocused = true; }
  void Unfocus() { isFocused = false; }

  void SetContent(std::string str) { content = str; }
  std::string GetContent() { return content; }
};

template <typename T, typename... Args> class GUINode : public GUINodeBase {
  std::function<T(Args...)> activatedFunction;
  std::tuple<Args...> storedArgs;
  bool argsSet = false;

public:
  GUINode(bool isFocused = false, std::string content = "Placeholder",
          std::function<T(Args...)> fn = nullptr)
      : GUINodeBase(isFocused, content), activatedFunction(std::move(fn)) {}

  void SetActivatedFunction(std::function<T(Args...)> fn) {
    activatedFunction = std::move(fn);
  }

  void SetArguments(Args... args) {
    storedArgs = std::make_tuple(args...);
    argsSet = true;
  }

  void Activate() override {
    this->Activate(Args()...);
    if (activatedFunction) {
      if (argsSet) {
        ActivateWithStoredArgs(make_index_sequence<sizeof...(Args)>{});
      } else {
        ActivateWithDefaultArgs(make_index_sequence<sizeof...(Args)>{});
      }
    }
  }

  template <typename... CallArgs>
  auto Activate(CallArgs &&...args) ->
      typename std::enable_if<std::is_convertible<std::tuple<CallArgs...>,
                                                  std::tuple<Args...>>::value,
                              T>::type {
    if (activatedFunction) {
      return activatedFunction(std::forward<CallArgs>(args)...);
    }
    return T();
  }

private:
  template <size_t... Is> void ActivateWithStoredArgs(index_sequence<Is...>) {
    activatedFunction(std::get<Is>(storedArgs)...);
  }

  template <size_t... Is> void ActivateWithDefaultArgs(index_sequence<Is...>) {
    activatedFunction(Args()...);
  }
};

#endif
