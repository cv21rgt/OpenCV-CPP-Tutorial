cmake_minimum_required(VERSION 3.25)

project(
    HELPER_OBJECTS 
    VERSION 0.1 
    DESCRIPTION "Project to show OpenCV objects we can use to run and write computer vision algorithms better" 
    LANGUAGES CXX 
)

# Add subdirectory to compiled library code
add_subdirectory(src)

# Add subdirectory where the main.cpp file is found
add_subdirectory(Helper-Objects-app)