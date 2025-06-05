#ifndef RENTLOG_H
#define RENTLOG_H

#include "Log.h"

class RentLog : public Log {
public:
  RentLog(size_t bikeId, size_t userId) : Log(bikeId, userId) {}

  std::string GetLogString() override;
};

#endif
