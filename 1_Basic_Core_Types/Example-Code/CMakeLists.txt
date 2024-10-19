# This is the main CMakeLists file

# CMake minimum version
cmake_minimum_required(VERSION 3.25)

# Project details
project(
    BASIC_CORE_TYPES  # Name of project
    VERSION 0.1       # Its version
    DESCRIPTION "Project for creating OpenCV basic core types"  # Project description
    LANGUAGES CXX # Project uses C++
)

# Our executable code will be in the following directory
add_subdirectory(BASIC_CORE_TYPES-app)