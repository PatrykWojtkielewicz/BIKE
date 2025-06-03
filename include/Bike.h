#ifndef BIKE_H
#define BIKE_H

#include "DatabaseEntry.h"
#include <ctime>

class Bike : public DatabaseEntry<Bike> {
  size_t currentStationId;
  size_t currentOwnerId;
  bool isTaken;

public:
  Bike(size_t currentStationId = 0)
      : currentStationId(currentStationId), currentOwnerId(0), isTaken(false) {
  } // moze lepiej currentOwnerId dac = 0?

  void RentBike(size_t userId);
  void ReturnBike(size_t userId);

  void SetCurrentOwnerId(size_t id) { currentOwnerId = id; }
  void SetCurrentStationId(size_t id) { currentStationId = id; }
  void SetIsTaken(bool state) { isTaken = state; }

  size_t GetCurrentStationId() const { return currentStationId; }
  size_t GetCurrentOwnerId() const { return currentOwnerId; }
  bool IsTaken() const { return isTaken; }

  std::ostream &GetDatabaseEntryToStream(std::ostream &os) override;
  std::istream &ParseObjectFromStream(std::istream &is) override;
  bool isEqual(const DatabaseEntry &other) const override;
};

#endif
