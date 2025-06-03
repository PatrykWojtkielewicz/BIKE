#include "State.h"
#include "RentLog.h"
#include <stdexcept>
std::string State::GetUserEmail(size_t id) {
  try {
    User user = UserDB.GetById(id);
    return user.GetEmail();
  } catch (const std::runtime_error &e) {
    std::cerr << "Error retrieving user email: " << e.what() << std::endl;
    throw;
  }
}

std::string State::GetUserName(size_t id) {
  try {
    User user = UserDB.GetById(id);
    return user.GetName();
  } catch (const std::runtime_error &e) {
    std::cerr << "Error retrieving user name: " << e.what() << std::endl;
    throw;
  }
}

std::string State::GetUserSurname(size_t id) {
  try {
    User user = UserDB.GetById(id);
    return user.GetSurname();
  } catch (const std::runtime_error &e) {
    std::cerr << "Error retrieving user surname: " << e.what() << std::endl;
    throw;
  }
}

size_t State::GetUserBikeRented(size_t id) {
  try {
    User user = UserDB.GetById(id);
    return user.GetBikeRentedId();
  } catch (const std::runtime_error &e) {
    std::cerr << "Error retrieving user bike rented: " << e.what() << std::endl;
    throw;
  }
}

size_t State::GetBikeCurrentStationId(size_t id) {
  try {
    Bike bike = BikeDB.GetById(id);
    return bike.GetCurrentStationId();
  } catch (const std::runtime_error &e) {
    std::cerr << "Error retrieving bike station: " << e.what() << std::endl;
    throw;
  }
}

bool State::GetBikeIsTaken(size_t id) {
  try {
    Bike bike = BikeDB.GetById(id);
    return bike.IsTaken();
  } catch (const std::runtime_error &e) {
    std::cerr << "Error retrieving bike status: " << e.what() << std::endl;
    throw;
  }
}

size_t State::GetBikeCurrentOwnerId(size_t id) {
  try {
    Bike bike = BikeDB.GetById(id);
    return bike.GetCurrentOwnerId();
  } catch (const std::runtime_error &e) {
    std::cerr << "Error retrieving bike owner: " << e.what() << std::endl;
    throw;
  }
}

void State::AddToDatabase(User &obj) { UserDB.Create(obj); }

void State::AddToDatabase(Log &obj) { LogDB.Create(obj); }

void State::AddToDatabase(Bike &obj) { BikeDB.Create(obj); }

template <> User State::GetObjectById<User>(size_t id) {
  return UserDB.GetById(id);
}

template <> Log State::GetObjectById<Log>(size_t id) {
  return LogDB.GetById(id);
}

template <> Bike State::GetObjectById<Bike>(size_t id) {
  return BikeDB.GetById(id);
}

void State::RentBike(size_t bikeId, size_t userId) {
  try {
    Bike bike = BikeDB.GetById(bikeId);
    User usr = UserDB.GetById(userId);

    if (bike.IsTaken()) {
      throw std::runtime_error("Cannot rent a taken bike");
    }

    if (usr.GetBikeRentedId() != 0) {
      throw std::runtime_error("Cannot rent more than one bike at a time");
    }

    bike.SetIsTaken(true);
    bike.SetCurrentOwnerId(userId);

    usr.SetBikeRentedId(bikeId);

    RentLog rtLog(bikeId, userId);

    UserDB.SetById(userId, usr);
    BikeDB.SetById(bikeId, bike);
    LogDB.Create(rtLog);

    // TODO: add logging
  } catch (const Database<Bike>::NoRecordsFound &e) {
    std::cerr << e.what() << std::endl;
    throw;
  } catch (const Database<User>::NoRecordsFound &e) {
    std::cerr << e.what() << std::endl;
    throw;
  }
}
