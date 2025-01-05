add_executable(HandIsomorphismTests indexing.cpp round_size.cpp)
target_link_libraries(HandIsomorphismTests PRIVATE gtest gtest_main ${PROJECT_NAME})
add_test(NAME HandIsomorphismTests COMMAND HandIsomorphismTests)