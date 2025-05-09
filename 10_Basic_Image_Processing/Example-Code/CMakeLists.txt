cmake_minimum_required(VERSION 3.25)

project(
    BASIC_IMAGE_PROCESSING
    VERSION 0.1 
    DESCRIPTION "Project to show arithmetic, masking, color space conversions, and bitwise operations on images" 
    LANGUAGES CXX 
)

# Add subdirectory to compiled library code
add_subdirectory(src)

# Add subdirectory where the source files are found
add_subdirectory(Image-Processing-app)