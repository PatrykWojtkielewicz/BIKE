#include "State.h"
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
