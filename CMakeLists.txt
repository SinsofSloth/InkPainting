# CMakeList.txt : CMake project for InkPainting, include source and define
# project specific logic here.
cmake_minimum_required (VERSION 3.8)

project ("InkPainting")

# Add source to this project's executable.
add_executable (InkPainting "InkPainting.cpp" "InkPainting.h" "include/lodepng.h" "include/cxxopts.h" "src/lodepng.cpp")
include_directories(include/)

set_target_properties(InkPainting PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)