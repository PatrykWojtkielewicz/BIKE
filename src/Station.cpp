#include "../include/Station.h"
#include <stdexcept>

void Station::addBikeId(size_t bikeId) {
  if (fill >= capacity) {
    throw std::runtime_error("Stacja jest pelna");
  }

  bikeIds[fill++] = bikeId;
}