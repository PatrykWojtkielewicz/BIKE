#ifndef LOG_H
#define LOG_H

#include <ctime>
#include <string>

class Log {
  size_t bikeId;
  size_t userId;
  time_t timestamp;

public:
  static size_t idCounter;
  size_t id;

  Log() : Log(0, 0) {}
  Log(size_t bikeId, size_t userId)
      : bikeId(bikeId), userId(userId), timestamp(std::time(nullptr)) {
    this->id = ++idCounter;
  }

  std::string GetLogString();
  void SaveToFile(std::string);
  friend std::ostream &operator<<(std::ostream &, const Log &);
  friend std::istream &operator>>(std::istream &os, Log &lg);
};

#endif
