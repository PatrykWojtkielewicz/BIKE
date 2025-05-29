#include "../include/ReturnLog.h"

std::string ReturnLog::GetLogString() {
  return Log::GetLogString() + ";type: return";
}