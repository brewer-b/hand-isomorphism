cmake_minimum_required (VERSION 3.20)
project(hand-isomorphism)

add_library(hand-isomorphism-c src/hand_index.c src/deck.c)
#target_link_libraries(hand-isomorphism-c m)
target_compile_features(hand-isomorphism-c PUBLIC c_std_11)
set_target_properties(hand-isomorphism-c PROPERTIES C_STANDARD_REQUIRED ON)

add_library(hand-isomorphism src/hand_isomorphism.cpp)
target_link_libraries(hand-isomorphism hand-isomorphism-c)
target_compile_features(hand-isomorphism PUBLIC cxx_std_17)
set_target_properties(hand-isomorphism PROPERTIES CXX_STANDARD_REQUIRED ON)
target_include_directories(hand-isomorphism PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)

add_executable(test_hand_isomorphism src/check-main.cpp)
target_link_libraries(test_hand_isomorphism hand-isomorphism)
