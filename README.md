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

Targeted for C++14 version, that is from my point of view lowest version that makes sense to use, unless explicitly requested. I did not try to make this compatible with C++03, even if it would be technically possible.

In practice, there are no C++14 features used and C++11 is enough.

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

1. Peeking top and bottom requires size check or exceptions to allow well defined usage. Since requirements for Container specify size, I opt to follow stl way and undefined behavior when peeking empty container is by design. While I'm not a big fan of undefined behavior, it's aligned with stl usage in general. Exceptions would be an option, but from my experiences these are not always enabled.
2. I'm a bit rusty with templates and move semantics in a sense that there are couple of use cases requiring std::move I would've missed if I didn't write tests. Hooray for testing!
3. I'm a bit more rusty with SFINAE (found out while thinking about what to do with shuffle).
4. Shuffling seems like either an API design- or a trick question to me. Since deck must fulfill container requirements, one can use shuffle from standard library. Therefore, if shuffle is implemented as a member function as requested, it should be either limiting the scope, hiding some details or doing something differently. Either way, there are two problems to solve that I got stuck with:
    - One aspect is to provide an API where two identical decks can provide different results when shuffled. This requires seed to be either randomized or given from the outside. Randomized seed is bad option for testing and making things deterministic when needed.
    - For best results, deck should also maintain the random number generator and only reset random number generator sequence when new seed is provided. Storing the rng with the underlying container violates single responsibility principle, and we already have a solution for that: shuffle in the standard library as a free function.

In this implementation, since there is no description of the use case for the shuffle, I opted to provide only one variant with random number generator as an argument. Having SFINAE resolution for shuffle with different outcome on integers (seed) or random number generator makes it inconvenient for the client to understand the usage. I did not bother to create own shuffle logic either, as I fail to see the need for that unless explicitly requested.

If this would be my pet project, I would rely on supporting std::shuffle instead of providing any member function to perform the shuffle.