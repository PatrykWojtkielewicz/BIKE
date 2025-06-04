#include "../include/Station.h"
#include <algorithm>
#include <stdexcept>

void Station::AddBikeId(size_t id) {
  if (id == 0) {
    throw std::runtime_error("Cannot add bike ID 0");
  }

  if (fill >= capacity) {
    throw std::runtime_error("Station is full");
  }

  auto it = std::find(bikeIds.begin(), bikeIds.end(), 0);
  if (it != bikeIds.end()) {
    *it = id;
    fill++;
  }
}

void Station::RemoveBikeId(size_t id) {
  if (id == 0) {
    throw std::runtime_error("Cannot remove bike ID 0");
  }

  auto it = std::find(bikeIds.begin(), bikeIds.end(), id);
  if (it != bikeIds.end()) {
    *it = 0;
    fill--;
  } else {
    throw std::runtime_error("Bike ID not found in station");
  }
}
