# BIKE

Program ten służy do wynajmowania rowerów miejskich. Po zalogowaniu się, można przeglądać liste stacji oraz liczbę rowerów na danej stacji dostępnych, wypożyczać i zwracać rower, sprawdzanie czasu wypożyczenia oraz wyświetlanie histori wypożyczeń.

## Struktura plików

- `bin/` - folder ten zawiera plik otwierający aplikację
- `include/` - folder ten zawiera wszystkie pliki nagłówkowe aplikacji
- `src/` - folder ten zawiera wszystkie pliki źródłowe aplikacji
- `CMakeLists.txt` - plik konfiguracyjny dla systemu CMake  

## Wymagania

- Kompilator C++ wspierający wersję 11 (np. Clang)
- CMake w wersji 3.8 lub nowszej

## Budowanie aplikacji

- `git clone https://github.com/PatrykWojtkielewicz/BIKE.git`

- `cd BIKE`

- `mkdir build`

- `cd build`

- `cmake ..`

- `cmake --build .`

- Dla systemu windows: `bin\BIKE.exe`

- Dla systemu Linux/macOS `./bin/BIKE`




