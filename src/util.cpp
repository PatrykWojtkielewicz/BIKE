#include "util.h"
#include <limits>
#include <stdexcept>

size_t util::stringTosize_t(const std::string &str) {
  unsigned long val = std::stoul(str);
  if (val > std::numeric_limits<size_t>::max()) {
    throw std::runtime_error("Cannot parse to size_t, number too large");
  }
  return static_cast<size_t>(val);
}
