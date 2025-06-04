#ifndef STATE_H
#define STATE_H

#include "Bike.h"
#include "Database.h"
#include "Log.h"
#include "Station.h"
#include "User.h"
#include <array>

enum class StationsEnum { ST1, ST2, COUNT };
constexpr size_t stationsSize = static_cast<size_t>(StationsEnum::COUNT);

StationsEnum &operator++(StationsEnum &st);
StationsEnum &operator--(StationsEnum &st);
StationsEnum operator++(StationsEnum &st, int);
StationsEnum operator--(StationsEnum &st, int);

class State {
  Database<Bike> BikeDB;
  Database<User> UserDB;
  Database<Log> LogDB;
  std::array<Station, stationsSize> Stations;

public:
  State(std::string logDBPath, std::string userDBPath, std::string bikeDBPath)
      : LogDB(logDBPath), UserDB(userDBPath), BikeDB(bikeDBPath) {
    SynchronizeStations();
  };

  std::string GetUserEmail(size_t);
  std::string GetUserName(size_t);
  std::string GetUserSurname(size_t);
  size_t GetUserBikeRented(size_t);
  size_t GetBikeCurrentStationId(size_t);
  bool GetBikeIsTaken(size_t);
  size_t GetBikeCurrentOwnerId(size_t);
  Station GetStationById(size_t);

  void AddToDatabase(User &);
  void AddToDatabase(Log &);
  void AddToDatabase(Bike &);

  template <typename T> T GetObjectById(size_t);

  void RentBike(size_t, size_t);
  void ReturnBike(size_t, size_t);

  void SynchronizeStations();
  size_t CheckUserCredentials(std::string, std::string);
};

template <> User State::GetObjectById<User>(size_t);
template <> Log State::GetObjectById<Log>(size_t);
template <> Bike State::GetObjectById<Bike>(size_t);

#endif
