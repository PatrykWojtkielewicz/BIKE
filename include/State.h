#ifndef STATE_H
#define STATE_H

#include "Database.h"
#include "Bike.h"
#include "Log.h"
#include "User.h"

class State {
  Database<Bike> BikeDB;
  Database<User> UserDB;
  Database<Log> LogDB;

  public:
    State() {};

    std::string GetUserEmail(size_t id) {
      try {
        User user = UserDB.GetById(id);
        return user.GetEmail();
      } catch (const std::runtime_error &e) {
        std::cerr << "Error retrieving user email: " << e.what() << std::endl;
        return "";
      }
    }

    std::string GetUserName(size_t id) {
      try {
        User user = UserDB.GetById(id);
        return user.GetName();
      } catch (const std::runtime_error &e) {
        std::cerr << "Error retrieving user name: " << e.what() << std::endl;
        return "";
      }
    }

    std::string GetUserSurname(size_t id) {
      try {
        User user = UserDB.GetById(id);
        return user.GetSurname();
      } catch (const std::runtime_error &e) {
        std::cerr << "Error retrieving user surname: " << e.what() << std::endl;
        return "";
      }
    }

    size_t GetUserBikeRented(size_t id) {
      try {
        User user = UserDB.GetById(id);
        return user.GetBikeRentedId();
      } catch (const std::runtime_error &e) {
        std::cerr << "Error retrieving user bike rented: " << e.what() << std::endl;
        return SIZE_MAX;
      }
    }

    size_t GetBikeCurrentStationId(size_t id) {
      try {
        Bike bike = BikeDB.GetById(id);
        return bike.GetCurrentStationId();
      } catch (const std::runtime_error &e) {
        std::cerr << "Error retrieving bike station: " << e.what() << std::endl;
        return SIZE_MAX;
      }
    }

    bool GetBikeIsTaken(size_t id) {
      try {
        Bike bike = BikeDB.GetById(id);
        return bike.IsTaken();
      } catch (const std::runtime_error &e) {
        std::cerr << "Error retrieving bike status: " << e.what() << std::endl;
        return false;
      }
    }

    size_t GetBikeCurrentOwnerId(size_t id) {
      try {
        Bike bike = BikeDB.GetById(id);
        return bike.GetCurrentOwnerId();
      } catch (const std::runtime_error &e) {
        std::cerr << "Error retrieving bike owner: " << e.what() << std::endl;
        return SIZE_MAX;
      }
    }
    
};

#endif