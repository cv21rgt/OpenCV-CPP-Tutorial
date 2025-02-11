cmake_minimum_required(VERSION 3.25)

project(
    SPARSE_LARGE_ARRAYS 
    VERSION 0.1 
    DESCRIPTION "Project to show how to implement and use sparse large arrays" 
    LANGUAGES CXX 
)

# Add subdirectory to compiled library code
add_subdirectory(src)

# Add subdirectory where the main.cpp file is found
add_subdirectory(Sparse_Arrays-app)