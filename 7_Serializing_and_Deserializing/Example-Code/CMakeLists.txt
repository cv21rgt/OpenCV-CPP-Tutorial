cmake_minimum_required(VERSION 3.25)

project(
    SERIALIZING_AND_DESERIALIZING 
    VERSION 0.1 
    DESCRIPTION "Project to show how to read and write data from/to various file formats" 
    LANGUAGES CXX 
)

# Add subdirectory to compiled library code
add_subdirectory(src)

# Add subdirectory where the main.cpp file is found
add_subdirectory(Read-Write-Data-app)