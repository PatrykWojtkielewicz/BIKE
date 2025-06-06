#ifndef LOG_H
#define LOG_H

#include "DatabaseEntry.h"
#include <ctime>
#include <string>

class Log : public DatabaseEntry<Log> {
protected:
  size_t bikeId;
  size_t userId;
  time_t timestamp;

public:
  std::string LogStr;

  Log() : Log(0, 0) {}
  Log(size_t bikeId, size_t userId)
      : bikeId(bikeId), userId(userId), timestamp(std::time(nullptr)) {}

  virtual ~Log() = default; // zeby usunac rowniez obiekty dziedziczace na zapas

  virtual std::string GetLogString(); // chyba virtual ma najwiecej sensu

  bool isEqual(const DatabaseEntry<Log> &) const override;
  std::ostream &GetDatabaseEntryToStream(std::ostream &) override;
  std::istream &ParseObjectFromStream(std::istream &) override;
  size_t GetUserId() { return userId; }
  time_t GetTimestamp() { return timestamp; }
};

#endif
