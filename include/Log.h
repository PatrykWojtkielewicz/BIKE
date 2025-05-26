#ifndef LOG_H
#define LOG_H

#include <chrono>
#include <ctime>
#include <string>
class Log {
  size_t bikeId;
  size_t userId;
  time_t timestamp;

public:
  Log(size_t bikeId, size_t userId)
      : bikeId(bikeId), userId(userId), timestamp(std::time(nullptr)) {}

  std::string GetLogString();
  void SaveToFile(std::string);
};

#endif
