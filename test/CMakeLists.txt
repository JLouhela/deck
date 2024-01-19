include(FetchContent)
FetchContent_Declare(
  googletest
  DOWNLOAD_EXTRACT_TIMESTAMP ON
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(deck_test
  src/deck_test.cpp
)
target_link_libraries(deck_test  
  GTest::gtest_main
  deck
)

include(GoogleTest)
gtest_discover_tests(deck_test)