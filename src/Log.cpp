#include "../include/Log.h"
#include "DatabaseEntry.h"
#include <cctype>
#include <istream>
#include <sstream>
#include <stdexcept>

std::string Log::GetLogString() {
  std::ostringstream iss;
  iss << "id: " << id;
  iss << " userId: " << userId;
  iss << " bikeId: " << bikeId;
  iss << " timestamp: " << timestamp;
  return iss.str();
}

std::istream &Log::ParseObjectFromStream(std::istream &iss) {
  char separator;

  if (!(iss >> id >> separator) || separator != ';')
    throw std::runtime_error("Failed to parse id from string");

  if (!(iss >> bikeId >> separator) || separator != ';')
    throw std::runtime_error("Failed to parse bikeId from string");

  if (!(iss >> userId >> separator) || separator != ';')
    throw std::runtime_error("Failed to parse userId from string");

  if (!(iss >> timestamp))
    throw std::runtime_error("Failed to parse timestamp from string");

  iss >> std::ws;

  return iss;
}

std::ostream &Log::GetDatabaseEntryToStream(std::ostream &os) {
  os << id << ";" << bikeId << ";" << userId << ";" << timestamp;
  return os;
}

bool Log::isEqual(const DatabaseEntry<Log> &a) const {
  const Log *otherLog = dynamic_cast<const Log *>(&a);
  if (!otherLog)
    return false;
  return ((otherLog->bikeId == bikeId) && (otherLog->userId == userId) &&
          (otherLog->timestamp == timestamp) && (otherLog->id == id));
}
