cmake_minimum_required(VERSION 3.15)

project(HandIsomorphism VERSION 2.0 LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)
FetchContent_Declare(
  pybind11
  GIT_REPOSITORY https://github.com/pybind/pybind11
)
FetchContent_MakeAvailable(pybind11)

set(SRC_FILES
    src/deck.c
    src/hand_index.c
)

add_library(hand_isomorphism_c ${SRC_FILES})
add_library(hand_isomorphism_cxx src/hand_isomorphism_cxx.cpp)
target_link_libraries(hand_isomorphism_cxx PUBLIC hand_isomorphism_c)
target_include_directories(hand_isomorphism_cxx PUBLIC include/)

add_executable(test_hand_isomorphism src/check-main.c)
target_link_libraries(test_hand_isomorphism hand_isomorphism_c)
target_include_directories(test_hand_isomorphism PRIVATE src/)

add_executable(test_hand_isomorphism_cxx src/check-main.cpp)
target_link_libraries(test_hand_isomorphism_cxx hand_isomorphism_cxx)

enable_testing()
add_test(NAME HandIsomorphismTest COMMAND test_hand_isomorphism)

install(TARGETS hand_isomorphism_c hand_isomorphism_cxx
    ARCHIVE DESTINATION lib               
    LIBRARY DESTINATION lib  
    CONFIGURATIONS Release         
)

install(FILES include/hand_isomorphism.h include/hand_isomorphism_cxx.h DESTINATION include/hand-isomorphism/)

# --- PYBIND11 INTEGRATION ---
pybind11_add_module(hand_isomorphism src/hand_isomorphism_py.cpp)
target_link_libraries(hand_isomorphism PRIVATE hand_isomorphism_cxx)
target_include_directories(hand_isomorphism PRIVATE include/)
install(TARGETS hand_isomorphism
    LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/hand_isomorphism
)