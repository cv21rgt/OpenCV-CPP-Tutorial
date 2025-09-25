cmake_minimum_required(VERSION 3.25)

project(
    GEOMETRIC_TRANSFORMATIONS
    VERSION 0.1 
    DESCRIPTION "Project to show how to carry out geometrical transformations of image data" 
    LANGUAGES CXX 
)

# Add subdirectory to compiled library code
add_subdirectory(src)

# Add subdirectory where the source files are found
add_subdirectory(Geometric-Transformations-app)