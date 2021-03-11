# CMakeList.txt : CMake project for InkPainting, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("InkPainting")

# Add source to this project's executable.
add_executable (InkPainting "InkPainting.cpp" "InkPainting.h" "include/lodepng.h" "include/cxxopts.h" "src/lodepng.cpp")

# TODO: Add tests and install targets if needed.
