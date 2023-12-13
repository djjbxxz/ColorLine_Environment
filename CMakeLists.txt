cmake_minimum_required(VERSION 3.4...3.18)
project(gen_colorline_data LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PYTHON_VERSION_STRING ${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR})

# ÃÌº”∫Í∂®“Â
add_definitions(-DPYVERSION="${PYTHON_VERSION_STRING}")

set(CMAKE_CXX_EXTENSIONS OFF)
add_definitions(-D_EXPORT)

AUX_SOURCE_DIRECTORY(. SRC_LIST)

add_subdirectory(extern/pybind11)
pybind11_add_module(gen_colorline_data ${SRC_LIST})
#pybind11_add_module(gen_colorline_data main.cpp)
