# Our 'main.cpp' is dependent on two external libraries: 
#   1. OpenCV
#   2. utility_functions_library - contains our own user-defined commonly used functions

# We will first look at finding the OpenCV package on our local system, find the required libraries we need 
# in order to run our code 

# Where do you find the OpenCV package? How do we link to OpenCV project
# ======================================================================

# 1. Instead of installing OpenCV to the usual path /usr/local ( on Linux O/S). I have installed
#    mine in a different directory ../Third_Party_Libraries/OpenCV_4.8.0/release/installed 
#    I do this for every version of OpenCV I install so I can have multiple versions which don't conflict with each other
# 2. When installed properly OpenCV  provides a 'cmake' folder, which contains its cmake config file named 'OpenCVConfig.cmake'
#    You need the path to this folder. For most people on Linux the path would be '/usr/local/lib/cmake/opencv4'

# Set path to directory with OpenCVConfig.cmake file
set(OpenCV_DIR "$ENV{HOME}/Third_Party_Libraries/OpenCV_4.8.0/release/installed/lib/cmake/opencv4")



# OpenCV package comes with quite a lot of modules/libraries - which we don't usually need all at once
# For now, we only want access to the 'core' module which contains the 'core basic data types'
find_package(OpenCV REQUIRED core)

if(OpenCV_FOUND)
    # Additional Include Directories - these contain the header files e.g. 'core.hpp'
    # CMake will find these for us
    include_directories(${OpenCV_INCLUDE_DIRS})

    # Additional Library Directories - these contains the libraries e.g 'libopencv_core.so', 'libopencv_core.so.4.8.0' etc
    # CMake will find these for us
    link_directories(${OpenCV_LIB_DIR})

    # In this CMakeLists.txt file we want to achieve the following:
    #  1. Build a local library 'utility_functions_library' using our own source and header files
    #  2. Find the OpenCV package and make it available to our library

    # Set paths to header and source files we will use to build our local library.
    # If you have more than 1 file seperate them by a comma. Each list is enclosed in one pair of quotes e.g. "path1, path2, ...pathN"
    # The paths are set to variables 'HEADER_LIST' and 'SOURCE_LIST'
    set(HEADER_LIST "${PROJECT_SOURCE_DIR}/include/UtilityFunctions/utility_functions.h")
    set(SOURCE_LIST "${PROJECT_SOURCE_DIR}/src/UtilityFunctions/utility_functions.cpp")

    # Using the headers and source files from above we will build a STATIC library called 'utility_functions_library'

    # N.B: Including the HEADER_LIST' in the following command is optional, and does not affect add_library. 
    #      However, skipping it means they may not show up in some IDEs when cloning the repository 
    add_library(utility_functions_library STATIC ${SOURCE_LIST} ${HEADER_LIST})

    # We need access to the 'include' directory from our source files, and users of our library will need it too
    target_include_directories(utility_functions_library PUBLIC ../include)

    # All users of this library will need at least C++17
    target_compile_features(utility_functions_library PUBLIC cxx_std_17)

    # Additional dependencies
    # Our executable is dependent on OpenCV libraries
    target_link_libraries(utility_functions_library ${OpenCV_LIBS})

    # Create an executable file from our 'Main.cpp' source file
    # The executable will be called 'Mat-app'
    add_executable(Mat-app Main.cpp)

    # We want to use C++17 standard (minimum)
    target_compile_features(Mat-app PRIVATE cxx_std_17)

    # Additional dependencies
    # Our executable is dependend on OpenCV libraries and our 'utility_functions_library'
    target_link_libraries(Mat-app ${OpenCV_LIBS} utility_functions_library)

endif(OpenCV_FOUND)
