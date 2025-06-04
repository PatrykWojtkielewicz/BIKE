# Bike - dokumentacja dla programisty

## Wymagania

- Kompilator C++ wspierający wersję 11 (np. Clang)
- CMake w wersji 3.8 lub nowszej

# Struktura plików

- `bin/` – folder z plikiem binarnym tworzonym  przy użyciu komendy `cmake --build .`

- `include/` – folder ten zawiera wszystkie pliki nagłówkowe aplikacji:
  - `Bike.h` – definicja klasy reprezentującej pojedynczy rower.
  - `Database.h` – zarządza danymi aplikacji w pamięci (baza danych programu).
  - `DatabaseEntry.h` – struktura reprezentująca rekord w bazie danych.
  - `Log.h` – bazowa klasa logu operacji wypożyczeń i zwrotów.
  - `RentLog.h` – dziedziczy po `Log`, generuje log dotyczący wypożyczenia roweru.
  - `ReturnLog.h` – dziedziczy po `Log`; generuje log dotyczący zwrotu roweru.
  - `State.h` – przechowuje obecny stan aplikacji.
  - `Station.h` – definicja klasy reprezentującej stację.
  - `User.h` – definicja klasy użytkownika, w tym dane logowania i historia.
  - `util.h` – funkcje pomocnicze wykorzystywane w aplikacji.

- `src/` – folder ten zawiera wszystkie pliki źródłowe aplikacji:
  - `Bike.cpp` – implementacja klasy `Bike`.
  - `Log.cpp` – implementacja klasy bazowej `Log`.
  - `RentLog.cpp` – implementacja klasy `RentLog`.
  - `ReturnLog.cpp` – implementacja klasy `ReturnLog`.
  - `State.cpp` – logika sterująca aktualnym stanem aplikacji.
  - `Station.cpp` – implementacja klasy `Station`.
  - `User.cpp` – implementacja klasy `User`.
  - `main.cpp` – punkt wejścia programu.
  - `util.cpp` – implementacja funkcji pomocniczych

- `CMakeLists.txt` – plik konfiguracyjny dla systemu CMake

## Budowanie aplikacji

- `git clone https://github.com/PatrykWojtkielewicz/BIKE.git`

- `cd BIKE`

- `mkdir build`

- `cd build`

- `cmake ..`

- `cmake --build .`

- Dla systemu windows: `bin\BIKE.exe`

- Dla systemu Linux/macOS `./bin/BIKE`
