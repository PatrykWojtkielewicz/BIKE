#include "../include/RentLog.h"

std::string RentLog::GetLogString() {
  LogStr = "rent " + Log::GetLogString();
  return "rent " + Log::GetLogString();
}
