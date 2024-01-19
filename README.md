# C++ deck container

Practice implementation for c++ container mimicking a deck.

Requirements:
    - Must be able to contain elements of any one type
    - Fulfills standard C++ container requirements: https://en.cppreference.com/w/cpp/named_req/Container
    - Contains methods for peeking top and bottom values of the deck
    - Contains method for drawing the top value from the deck
    - Contains method for adding new value on top of the deck
    - Contains method for shuffling the deck

## Limitations

Targeted for C++14 version
- Support for movable types
- Uses random number generation for shuffle
- GoogleTest requires C++14

Not trying to make this compatible with C++03, although technically possible.

## Building

Uses standard CMake solution for building.

### Instructions for Linux

    mkdir build
    cmake -S . -B build
    cmake --build build
    cd build && ctest

CMake will download GoogleTest when generating the solution.
