#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "hand_isomorphism_cxx.h"  // Include your C++ header

namespace py = pybind11;

PYBIND11_MODULE(hand_isomorphism, m) {
    // Expose the HandIndexers class to Python
    py::class_<HandIndexers>(m, "HandIndexers")
        .def(py::init<const std::vector<std::vector<uint8_t>>&>())
        .def("roundSize", &HandIndexers::roundSize)
        .def("indexHand", &HandIndexers::indexHand)
        .def("unindexHand", &HandIndexers::unindexHand);
}