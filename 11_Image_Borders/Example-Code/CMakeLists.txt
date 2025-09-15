cmake_minimum_required(VERSION 3.25)

project(
    IMAGE_BORDERS
    VERSION 0.1 
    DESCRIPTION "Project to show to handle pixels at image borders" 
    LANGUAGES CXX 
)

# Add subdirectory to compiled library code
add_subdirectory(src)

# Add subdirectory where the source files are found
add_subdirectory(Image-Border-app)