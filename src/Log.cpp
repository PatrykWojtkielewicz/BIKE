#include "../include/Log.h"
#include "DatabaseEntry.h"
#include <cctype>
#include <fstream>
#include <iomanip>

#include <istream>
#include <sstream>
#include <stdexcept>

std::string Log::GetLogString() {
  std::ostringstream iss;
  iss << "userId: " << userId;
  iss << ";bikeId: " << bikeId;
  iss << ";timestamp: "
      << std::put_time(std::localtime(&timestamp), "%Y-%m-%d %H:%M:%S");
  return iss.str();
}

void Log::SaveToFile(std::string path) {
  try {
    std::ofstream outFile;
    outFile.exceptions(std::ofstream::failbit | std::ofstream::badbit);
    outFile.open(path, std::ios::app);
    outFile << GetLogString() << std::endl;
    outFile.close();
  } catch (const std::ofstream::failure &e) {
    throw std::runtime_error(std::string("File write fail at ") + path + ": " +
                             e.what());
  }
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
// TODO: Consider adding a full string to the database or something, database
// itself isn't enough

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
