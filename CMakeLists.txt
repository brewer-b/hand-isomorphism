cmake_minimum_required(VERSION 3.10)

project(hand-isomorphism VERSION 1.0)

add_library(hand-isomorphism SHARED src/deck.c src/hand_index.c)

target_include_directories(hand-isomorphism PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)