#include "../include/Log.h"
#include "DatabaseEntry.h"
#include "util.h"
#include <boost/token_iterator.hpp>
#include <boost/tokenizer.hpp>
#include <cctype>
#include <iomanip>
#include <istream>
#include <sstream>
#include <stdexcept>

std::string Log::GetLogString() {
  std::ostringstream iss;
  iss << "userId: " << userId;
  iss << " bikeId: " << bikeId;
  iss << " time: "
      << std::put_time(std::localtime(&timestamp), "%Y-%m-%d %H:%M:%S");
  return iss.str();
}

std::istream &Log::ParseObjectFromStream(std::istream &is) {

  std::string inputStr;
  std::getline(is, inputStr);

  boost::char_separator<char> sep(";");
  boost::tokenizer<boost::char_separator<char>> tokens(inputStr, sep);

  std::vector<std::string> vec = {tokens.begin(), tokens.end()};

  if (vec.size() < 5) { // not enough args provided
    std::ostringstream oss;
    oss << "Cannot create log object from string, not enough arguments"
        << vec.size();
    throw std::runtime_error(oss.str());
  }

  id = util::stringTosize_t(vec[0]);
  bikeId = util::stringTosize_t(vec[1]);
  userId = util::stringTosize_t(vec[2]);
  LogStr = vec[3];
  timestamp = static_cast<time_t>(std::stoll(vec[4]));

  return is;
}
// TODO: Consider adding a full string to the database or something, database
// itself isn't enough

std::ostream &Log::GetDatabaseEntryToStream(std::ostream &os) {
  os << id << ";" << bikeId << ";" << userId << ";" << GetLogString() << ";"
     << timestamp;
  return os;
}

bool Log::isEqual(const DatabaseEntry<Log> &a) const {
  const Log *otherLog = dynamic_cast<const Log *>(&a);
  if (!otherLog)
    return false;
  return ((otherLog->bikeId == bikeId) && (otherLog->userId == userId) &&
          (otherLog->timestamp == timestamp) && (otherLog->id == id));
}
