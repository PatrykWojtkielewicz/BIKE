#ifndef BIKE_H
#define BIKE_H

#include "DatabaseEntry.h"
#include <cstdint>
#include <ctime>

class Bike : public DatabaseEntry<Bike> {
  size_t currentStationId;
  size_t currentOwnerId;
  bool isTaken;

public:
  Bike(size_t currentStationId = SIZE_MAX)
      : currentStationId(currentStationId), currentOwnerId(SIZE_MAX),
        isTaken(false) {} // moze lepiej currentOwnerId dac = 0?

  void RentBike(size_t userId);
  void ReturnBike(size_t userId);

  size_t GetCurrentStationId() const { return currentStationId; }
  size_t GetCurrentOwnerId() const { return currentOwnerId; }
  bool IsTaken() const { return isTaken; }

  std::ostream &GetDatabaseEntryToStream(std::ostream &os) override;
  std::istream &ParseObjectFromStream(std::istream &is) override;
  bool isEqual(const DatabaseEntry &other) const override;
};

#endif
