add_executable(HandIsomorphismTests c_wrapper.cpp indexing.cpp round_size.cpp)
target_link_libraries(HandIsomorphismTests PRIVATE gtest gtest_main ${PROJECT_NAME})
add_test(NAME HandIsomorphismTests COMMAND HandIsomorphismTests)