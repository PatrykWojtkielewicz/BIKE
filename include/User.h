#ifndef USER_H
#define USER_H

#include "DatabaseEntry.h"
#include <ctime>

class User : public DatabaseEntry<User> {
  std::string name;
  std::string surname;
  std::string email;
  std::string password;
  size_t bikeRentedId;

public:
  User(std::string name = "", std::string surname = "", std::string email = "",
       std::string password = "")
      : name(name), surname(surname), email(email), password(password),
        bikeRentedId(0) {}

  bool IsPasswordMatch(std::string str) { return str == password; }

  std::string GetName() const { return name; }
  std::string GetSurname() const { return surname; }
  std::string GetEmail() const { return email; }
  size_t GetBikeRentedId() const { return bikeRentedId; }

  void SetName(std::string name) { this->name = name; }
  void SetSurname(std::string surname) { this->surname = surname; }
  void SetEmail(std::string email) { this->email = email; }
  void SetBikeRentedId(size_t id) { bikeRentedId = id; }

  std::ostream &GetDatabaseEntryToStream(std::ostream &os) override;
  std::istream &ParseObjectFromStream(std::istream &is) override;
  bool isEqual(const DatabaseEntry &other) const override;
};

#endif
