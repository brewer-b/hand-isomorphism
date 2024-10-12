cmake_minimum_required(VERSION 3.10)

project(HandIsomorphism VERSION 2.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

option(HANDISOMORPHISM_BUILD_SHARED_LIBS "Build shared libraries (.dll/.so) instead of static ones (.lib/.a)" ON)

set(SRC_FILES
    src/deck.c
    src/hand_index.c
)

if(HANDISOMORPHISM_BUILD_SHARED_LIBS)
    add_library(hand_isomorphism SHARED ${SRC_FILES})
else()
    add_library(hand_isomorphism STATIC ${SRC_FILES})
endif()

add_executable(test_hand_isomorphism src/check-main.c)
target_link_libraries(test_hand_isomorphism hand_isomorphism)
target_include_directories(test_hand_isomorphism PRIVATE src/)

enable_testing()
add_test(NAME HandIsomorphismTest COMMAND test_hand_isomorphism)

install(TARGETS hand_isomorphism
    ARCHIVE DESTINATION lib               
    LIBRARY DESTINATION lib           
)

install(FILES include/hand_isomorphism.h DESTINATION include)