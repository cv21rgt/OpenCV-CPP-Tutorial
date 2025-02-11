cmake_minimum_required(VERSION 3.25)

project(
    SATURATION_CASTING
    VERSION 0.1
    DESCRIPTION "Project for handling underflow and overflow of values of different data types in OpenCV"
    LANGUAGES CXX
    )

# Add subdirectory which contains user written source code other than 'main.cpp' which our
# executable will depend on to run properly
add_subdirectory(src)

# This sub-directory is where the 'main.cpp' file is
add_subdirectory(Saturation_Casting-app)