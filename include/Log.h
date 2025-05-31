#ifndef LOG_H
#define LOG_H

#include "DatabaseEntry.h"
#include <ctime>
#include <string>

class Log : public DatabaseEntry<Log> {
  size_t bikeId;
  size_t userId;
  time_t timestamp;

public:
  Log() : Log(0, 0) {}
  Log(size_t bikeId, size_t userId)
      : bikeId(bikeId), userId(userId), timestamp(std::time(nullptr)) {}

  std::string GetLogString();

  bool isEqual(const DatabaseEntry<Log> &) const override;

  std::ostream &GetDatabaseEntryToStream(std::ostream &) override;

  std::istream &ParseObjectFromStream(std::istream &) override;
};

#endif
