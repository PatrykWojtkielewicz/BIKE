#include "State.h"
#include "RentLog.h"
#include "ReturnLog.h"
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

Station State::GetStationById(size_t id) {
  if (id >= stationsSize)
    throw std::runtime_error("invalid station id");
  return Stations[id];
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

    Stations[bike.GetCurrentStationId()].RemoveBikeId(bikeId);

    bike.SetIsTaken(true);
    bike.SetCurrentOwnerId(userId);

    usr.SetBikeRentedId(bikeId);

    RentLog rtLog(bikeId, userId);

    UserDB.SetById(userId, usr);
    BikeDB.SetById(bikeId, bike);

    LogDB.Create(rtLog);

  } catch (const Database<Bike>::NoRecordsFound &e) {
    std::cerr << e.what() << std::endl;
    throw;
  } catch (const Database<User>::NoRecordsFound &e) {
    std::cerr << e.what() << std::endl;
    throw;
  }
}

void State::ReturnBike(size_t bikeId, size_t stationId) {
  try {
    Bike bike = BikeDB.GetById(bikeId);
    size_t userId = bike.GetCurrentOwnerId();

    User usr = UserDB.GetById(userId);

    bike.SetIsTaken(false);
    bike.SetCurrentOwnerId(0);
    bike.SetCurrentStationId(0);

    Stations[stationId].AddBikeId(bikeId);

    usr.SetBikeRentedId(0);
    ReturnLog rtLog(bikeId, stationId);

    UserDB.SetById(userId, usr);
    BikeDB.SetById(bikeId, bike);

    LogDB.Create(rtLog);

  } catch (const Database<Bike>::NoRecordsFound &e) {
    std::cerr << e.what() << std::endl;
    throw;
  } catch (const Database<User>::NoRecordsFound &e) {
    std::cerr << e.what() << std::endl;
    throw;
  }
}

StationsEnum &operator++(StationsEnum &st) {
  st = static_cast<StationsEnum>((static_cast<int>(st) + 1) % stationsSize);
  return st;
}

StationsEnum &operator--(StationsEnum &st) {
  st = static_cast<StationsEnum>((static_cast<int>(st) - 1 + stationsSize) %
                                 stationsSize);
  return st;
}

StationsEnum operator++(StationsEnum &st, int) {
  StationsEnum old = st;
  ++st;
  return old;
}

StationsEnum operator--(StationsEnum &st, int) {
  StationsEnum old = st;
  --st;
  return old;
}
