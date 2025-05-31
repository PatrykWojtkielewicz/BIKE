#ifndef BIKE_H
#define BIKE_H

#include <cstdint>
#include <ctime>

class Bike {
  size_t id;
  size_t currentStationId;
  size_t currentOwnerId;
  bool isTaken;
  static size_t nextId;

  public:
    Bike(size_t currentStationId) : id(nextId++), currentStationId(currentStationId), currentOwnerId(SIZE_MAX), isTaken(false) {} // moze lepiej currentOwnerId dac = 0?

    void RentBike(size_t userId);
    void ReturnBike(size_t userId);

};

#endif
