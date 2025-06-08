cmake_minimum_required(VERSION 3.10)
project(hand-isomorphism)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

add_library(${PROJECT_NAME} src/deck.c src/hand_index.c)
target_link_libraries(${PROJECT_NAME} m)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME}-check-main src/check-main.c)
target_link_libraries(${PROJECT_NAME}-check-main ${PROJECT_NAME})