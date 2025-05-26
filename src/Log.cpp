#include "../include/Log.h"
#include <cctype>
#include <sstream>

std::string Log::GetLogString() {
  std::ostringstream iss;
  iss << "userId: " << userId;
  iss << " bikeId: " << bikeId;
  iss << " timestamp: " << timestamp;
  return iss.str();
}

void Log::SaveToFile(std::string path) {}
