cmake_minimum_required(VERSION 3.25)

project(
    READ_WRITE_IMAGES
    VERSION 0.1 
    DESCRIPTION "Project to show how to read and write image files" 
    LANGUAGES CXX 
)

# Add subdirectory to compiled library code
add_subdirectory(src)

# Add subdirectory where the main.cpp file is found
add_subdirectory(Read-Write-Data-app)