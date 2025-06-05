#ifndef RETURNLOG_H
#define RETURNLOG_H

#include "Log.h"

class ReturnLog : public Log {
public:
  ReturnLog(size_t bikeId, size_t userId) : Log(bikeId, userId) {}

  std::string GetLogString() override;
};

#endif
