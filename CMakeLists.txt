cmake_minimum_required(VERSION 3.10)

project(hand-isomorphism VERSION 1.0)

# Add the library target
add_library(hand-isomorphism SHARED src/hand_index.cpp src/isomorphism_c.cpp)

# Set the include directories
target_include_directories(hand-isomorphism PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Set the C++ standard to C++11
set_target_properties(hand-isomorphism PROPERTIES CXX_STANDARD 11)
set_target_properties(hand-isomorphism PROPERTIES CXX_STANDARD_REQUIRED ON)

# Add optimization, warning, position-independent code, and architecture-specific flags
target_compile_options(hand-isomorphism PRIVATE
    -O3
    -fPIC
    -march=native
    -funroll-loops
    -finline-functions
    -ffast-math
    -fomit-frame-pointer
    -ftree-vectorize
)