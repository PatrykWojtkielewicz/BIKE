#include "../include/Bike.h"

void Bike::RentBike(size_t userId) {
  if(!isTaken) {
    isTaken = true;
    currentOwnerId = userId;
    currentStationId = SIZE_MAX;
    // TODO: przypisanie rowera uzytkownikowi
  }
}

std::ostream &Bike::GetDatabaseEntryToStream(std::ostream &os) {
  os << id << ";" << currentStationId << ";" << currentOwnerId << ";" << isTaken;
  return os;
}

std::istream &Bike::ParseObjectFromStream(std::istream &is) {
  char separator;

  if (!(is >> id >> separator) || separator != ';')
    throw std::runtime_error("Failed to parse id from string");

  if (!(is >> currentStationId >> separator) || separator != ';')
    throw std::runtime_error("Failed to parse currentStationId from string");

  if (!(is >> currentOwnerId >> separator) || separator != ';')
    throw std::runtime_error("Failed to parse currentOwnerId from string");

  if (!(is >> isTaken))
    throw std::runtime_error("Failed to parse isTaken from string");

  is >> std::ws;
  return is;
}
  
bool Bike::isEqual(const DatabaseEntry<Bike> &other) const {
  const Bike* bikePtr = dynamic_cast<const Bike*>(&other);
  if (!bikePtr) {
    return false; 
  }
  return id == bikePtr->id &&
         currentStationId == bikePtr->currentStationId &&
         currentOwnerId == bikePtr->currentOwnerId &&
         isTaken == bikePtr->isTaken;
}