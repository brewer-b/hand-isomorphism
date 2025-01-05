cmake_minimum_required(VERSION 3.10)
project(HandIsomorphism)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(${PROJECT_NAME} src/deck.c src/hand_index.c src/hand_isomorphism.cpp src/hand_isomorphism_c.cpp)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
  DOWNLOAD_EXTRACT_TIMESTAMP true
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_subdirectory(tests)