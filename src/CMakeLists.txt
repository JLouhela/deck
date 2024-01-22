add_library(deck INTERFACE)

target_include_directories(deck
  INTERFACE
    include
)

# Hacky way to show interface target in Visual Studio
add_custom_target(deck_interface SOURCES ${CMAKE_CURRENT_LIST_DIR}/include/deck/deck.h)
