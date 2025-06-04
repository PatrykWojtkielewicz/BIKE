#ifndef STATION_H
#define STATION_H

#include <ctime>
#include <vector>

class Station {
  size_t capacity;
  size_t fill;
  std::vector<size_t> bikeIds; // te 3 pola mozna by dac public albo napisac
                               // gettery - do uzgodnienia
public:
  Station(size_t capacity) : capacity(capacity), fill(0), bikeIds(capacity) {}
  Station() : Station(10) {}

  void AddBikeId(size_t bikeId);
  void RemoveBikeId(size_t bikeId);
};

#endif
