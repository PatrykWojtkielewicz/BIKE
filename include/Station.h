#ifndef STATION_H
#define STATION_H

#include <cstdlib>
#include <vector>

class Station {
  size_t capacity;
  size_t fill;

public:
  std::vector<size_t> bikeIds;

  Station(size_t capacity)
      : capacity(capacity), fill(0), bikeIds(capacity, 0) {}
  Station() : Station(10) {}

  void AddBikeId(size_t bikeId);
  void RemoveBikeId(size_t bikeId);
  size_t GetNonZeroFieldsSize() const { return fill; }
  size_t GetCapacity() const { return capacity; }
  bool IsFull() const { return fill == capacity; }
  bool IsEmpty() const { return fill == 0; }
};

#endif
