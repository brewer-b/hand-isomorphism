cmake_minimum_required(VERSION 3.15)
project(hand_isomorphism VERSION 1.0.0 LANGUAGES C CXX)

add_library(hand_index_c STATIC
    src/hand_index.c
)

set_target_properties(hand_index_c PROPERTIES
    C_STANDARD 17
    C_STANDARD_REQUIRED ON
)

if(NOT MSVC)
    target_link_libraries(hand_index_c PRIVATE m)
endif()

add_library(hand_isomorphism
    src/hand_isomorphism.cpp
)

set_target_properties(hand_isomorphism PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(hand_isomorphism
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(hand_isomorphism
    PUBLIC
        hand_index_c
)