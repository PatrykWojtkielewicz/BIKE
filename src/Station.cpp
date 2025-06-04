#include "../include/Station.h"
#include <algorithm>
#include <stdexcept>

void Station::AddBikeId(size_t id) {
  if (fill >= capacity) {
    throw std::runtime_error("Station is full");
  }

  bikeIds[fill++] = id;
}

void Station::RemoveBikeId(size_t id) {
  size_t vecSize = bikeIds.size();
  bikeIds.erase(std::remove_if(bikeIds.begin(), bikeIds.end(),
                               [=](size_t curId) { return curId == id; }));
  if (vecSize == bikeIds.size()) {
    throw std::runtime_error("BikeId not found in station");
  }
}
