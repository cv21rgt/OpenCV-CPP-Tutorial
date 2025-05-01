cmake_minimum_required(VERSION 3.25)

project(
    DRAWING_AND_ANNOTATION
    VERSION 0.1 
    DESCRIPTION "Project to show how to draw shapes and add text to images" 
    LANGUAGES CXX 
)

# Add subdirectory to compiled library code
add_subdirectory(src)

# Add subdirectory where the source files are found
add_subdirectory(Draw-Annotate-app)