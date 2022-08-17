cmake_minimum_required(VERSION 3.4...3.18)
project(gen_colorline_data LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_definitions(-D_EXPORT)

AUX_SOURCE_DIRECTORY(. SRC_LIST)

add_subdirectory(pybind11)
pybind11_add_module(gen_colorline_data ${SRC_LIST})
#pybind11_add_module(gen_colorline_data main.cpp)
