#include "../include/Bike.h"

void Bike::RentBike(size_t userId) {
  if(!isTaken) {
    isTaken = true;
    currentOwnerId = userId;
    currentStationId = SIZE_MAX;
    // TODO: przypisanie rowera uzytkownikowi
  }
}