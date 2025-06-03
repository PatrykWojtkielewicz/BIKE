#include "../include/Station.h"
#include <stdexcept>

void Station::addBikeId(size_t bikeId) {
  if (fill >= capacity) {
    throw std::runtime_error("Station is full");
  }

  bikeIds[fill++] = bikeId;
}