#ifndef DATABASE_ENTRY_H
#define DATABASE_ENTRY_H

#include <istream>
#include <ostream>

template <typename Derived> class DatabaseEntry {
public:
  size_t id;
  static size_t idCounter;

  DatabaseEntry() : id(++idCounter) {}

  ~DatabaseEntry() = default;

  virtual std::ostream &GetDatabaseEntryToStream(std::ostream &) = 0;

  virtual std::istream &ParseObjectFromStream(std::istream &) = 0;

  virtual bool isEqual(const DatabaseEntry &) const = 0;

  friend std::ostream &operator<<(std::ostream &os, DatabaseEntry &obj) {
    return obj.GetDatabaseEntryToStream(os);
  }

  friend std::istream &operator>>(std::istream &is, DatabaseEntry &obj) {
    return obj.ParseObjectFromStream(is);
  }

  friend bool operator==(const DatabaseEntry &lhs, const DatabaseEntry &rhs) {
    return lhs.isEqual(rhs);
  }
};

template <typename Derived> size_t DatabaseEntry<Derived>::idCounter = 0;

#endif
