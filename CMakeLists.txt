cmake_minimum_required(VERSION 3.10)
project(HandIsomorphism LANGUAGES C CXX)

add_library(hand_isomorphism_c STATIC src/hand_index.c)
target_compile_features(hand_isomorphism_c PRIVATE c_std_99)

add_library(${PROJECT_NAME} STATIC src/hand_isomorphism.cpp)

# This is the key line. 'PUBLIC' ensures the dependency is transitive.
target_link_libraries(${PROJECT_NAME} PUBLIC hand_isomorphism_c)

target_include_directories(${PROJECT_NAME} PUBLIC include/)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

add_executable(check_hand_isomorphism src/check-main.cpp)
target_link_libraries(check_hand_isomorphism ${PROJECT_NAME})