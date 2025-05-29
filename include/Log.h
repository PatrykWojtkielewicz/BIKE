#ifndef LOG_H
#define LOG_H

#include <ctime>
#include <string>

class Log {
  protected:
    size_t bikeId;
    size_t userId;
    time_t timestamp;

public:
  Log(size_t bikeId, size_t userId) : bikeId(bikeId), userId(userId), timestamp(std::time(nullptr)) {}
  virtual ~Log() = default; // zeby usunac rowniez obiekty dziedziczace na zapas

  virtual std::string GetLogString(); // chyba virtual ma najwiecej sensu
  void SaveToFile(std::string);
};

#endif
