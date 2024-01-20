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

As this was not requested, I will not try to make this compatible with C++03, although technically possible.

## Building

Uses standard CMake solution for building.

### Instructions for Linux

    mkdir build
    cmake -S . -B build
    cmake --build build
    cd build && ctest

CMake will download GoogleTest when generating the solution.

## Remarks

Findings during development, notes for the assessment
- Peeking top and bottom requires size check or exceptions to allow well defined usage. Since requirements for Container specify size, I opt to follow stl way and undefined behavior when peeking empty container is by design.
- Shuffling is an API design question: do we want client to be able to specify the algorithm, or not? If not, seed is sufficient and deck can maintain the random number generator. I added both, but depending on the use case
this may not be required.