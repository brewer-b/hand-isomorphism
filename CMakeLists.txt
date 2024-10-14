cmake_minimum_required(VERSION 3.10)

project(HandIsomorphism VERSION 2.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

set(SRC_FILES
    src/deck.c
    src/hand_index.c
)

add_library(hand_isomorphism ${SRC_FILES})

add_executable(test_hand_isomorphism src/check-main.c)
target_link_libraries(test_hand_isomorphism hand_isomorphism)
target_include_directories(test_hand_isomorphism PRIVATE src/)

enable_testing()
add_test(NAME HandIsomorphismTest COMMAND test_hand_isomorphism)

install(TARGETS hand_isomorphism
    ARCHIVE DESTINATION lib               
    LIBRARY DESTINATION lib  
    CONFIGURATIONS Release         
)

install(FILES include/hand_isomorphism.h DESTINATION include/hand-isomorphism/)