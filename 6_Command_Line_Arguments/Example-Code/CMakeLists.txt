cmake_minimum_required(VERSION 3.25)

project(
    COMMAND_LINE_ARGUMENTS 
    VERSION 0.1 
    DESCRIPTION "Project to show how to provide input to a program from the command line" 
    LANGUAGES CXX 
)

# Add subdirectory to compiled library code
add_subdirectory(src)

# Add subdirectory where the main.cpp file is found
add_subdirectory(Command_Line_Args_app)