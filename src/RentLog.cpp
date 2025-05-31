#include "../include/RentLog.h"

std::string RentLog::GetLogString() {
  return Log::GetLogString() + ";type: rent";
}