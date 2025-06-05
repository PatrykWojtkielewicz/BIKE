#include "../include/ReturnLog.h"

std::string ReturnLog::GetLogString() {
  LogStr = "return " + Log::GetLogString();
  return "return " + Log::GetLogString();
}
