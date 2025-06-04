#include "User.h"
#include "util.h"
#include <boost/token_iterator.hpp>
#include <boost/tokenizer.hpp>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>

std::ostream &User::GetDatabaseEntryToStream(std::ostream &os) {

  os << id << ";" << name << ";" << surname << ";" << email << ";"
     << bikeRentedId;

  return os;
}

std::istream &User::ParseObjectFromStream(std::istream &is) {

  std::string inputStr;
  is >> inputStr;

  boost::char_separator<char> sep(";");
  boost::tokenizer<boost::char_separator<char>> tokens(inputStr, sep);

  std::vector<std::string> vec = {tokens.begin(), tokens.end()};

  if (vec.size() < 5) { // not enough args provided
    throw std::runtime_error(
        "Cannot create user object from string, not enough arguments");
  }

  id = util::stringTosize_t(vec[0]);
  name = vec[1];
  surname = vec[2];
  email = vec[3];
  bikeRentedId = util::stringTosize_t(vec[4]);

  return is;
}

bool User::isEqual(const DatabaseEntry<User> &other) const {

  const User *otherUser = dynamic_cast<const User *>(&other);
  if (!otherUser) {
    return false;
  }

  return id == otherUser->id && name == otherUser->name &&
         surname == otherUser->surname && email == otherUser->email &&
         bikeRentedId == otherUser->bikeRentedId;
}
