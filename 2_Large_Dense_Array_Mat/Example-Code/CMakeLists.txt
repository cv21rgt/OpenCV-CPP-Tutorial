cmake_minimum_required(VERSION 3.25)

project(
    N-DIMENSIONAL-DENSE-ARRAYS 
    VERSION 0.1
    DESCRIPTION "Project for creating dense Mat data types"
    LANGUAGES CXX
    )

# Add subdirectory which contains user written source code other than 'main.cpp' which our
# executable will depend on to run properly
add_subdirectory(src)

# This directory is where the 'main.cpp' file is
add_subdirectory(Mat-app)