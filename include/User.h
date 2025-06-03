#ifndef USER_H
#define USER_H

#include "DatabaseEntry.h"
#include <ctime>

class User : public DatabaseEntry<User> {
  std::string name;
  std::string surname;
  std::string email;
  size_t bikeRentedId;
  
  public:
    User(std::string name, std::string surname, std::string email, size_t bikeRentedId = 0)
        : name(name), surname(surname), email(email) {}

    std::string GetName() const { return name; }
    std::string GetSurname() const { return surname; }
    std::string GetEmail() const { return email; }
    size_t GetBikeRentedId() const { return bikeRentedId; }

    std::ostream &GetDatabaseEntryToStream(std::ostream &os) override;
    std::istream &ParseObjectFromStream(std::istream &is) override;
    bool isEqual(const DatabaseEntry &other) const override;
};

#endif
