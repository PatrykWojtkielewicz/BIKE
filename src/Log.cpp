#include "../include/Log.h"
#include <cctype>
#include <istream>
#include <sstream>
#include <stdexcept>

size_t Log::idCounter = 0;

std::string Log::GetLogString() {
  std::ostringstream iss;
  iss << "id: " << id;
  iss << " userId: " << userId;
  iss << " bikeId: " << bikeId;
  iss << " timestamp: " << timestamp;
  return iss.str();
}

void Log::SaveToFile(std::string path) {}

std::ostream &operator<<(std::ostream &os, const Log &lg) {
  return os << lg.id << ";" << lg.bikeId << ";" << lg.userId << ";"
            << lg.timestamp;
}

std::istream &operator>>(std::istream &iss, Log &lg) {
  char separator;

  if (!(iss >> lg.id >> separator) || separator != ';')
    throw std::runtime_error("Failed to parse id from string");

  if (!(iss >> lg.bikeId >> separator) || separator != ';')
    throw std::runtime_error("Failed to parse bikeId from string");

  if (!(iss >> lg.userId >> separator) || separator != ';')
    throw std::runtime_error("Failed to parse userId from string");

  if (!(iss >> lg.timestamp))
    throw std::runtime_error("Failed to parse timestamp from string");

  iss >> std::ws;

  return iss;
}
