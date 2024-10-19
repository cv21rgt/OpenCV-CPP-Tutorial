# Our 'main.cpp' is dependent on an external library - OpenCV
# We need to find the OpenCV package on our local system, find the required libraries we need 
# in order to run our code 

# Where do you find the OpenCV package? How do we link to OpenCV project
# ======================================================================

# 1. Instead of installing OpenCV to the usual path /usr/local ( on Linux O/S). I have installed
#    mine in a different directory ../Third_Party_Libraries/OpenCV_4.8.0/release/installed 
#    I do this for every version of OpenCV I install so I can have multiple versions which don't conflict with each other
# 2. When installed properly OpenCV  provides a 'cmake' folder, which contains its cmake config file named 'OpenCVConfig.cmake'
#    You need the path to this folder. For most people on Linux the path would be '/usr/local/lib/cmake/opencv4'

# Set path to directory with OpenCVConfig.cmake file
set(OpenCV_DIR "$ENV{HOME}Third_Party_Libraries/OpenCV_4.8.0/release/installed/lib/cmake/opencv4")

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

    # Create an executable file from our 'Main.cpp' source file
    # The executable will be called 'Mat-app'
    add_executable(Mat-app Main.cpp)

    # We want to use C++17 standard (minimum)
    target_compile_features(Mat-app PRIVATE cxx_std_17)

    # Additional dependencies
    # Our executable is dependend on OpenCV libraries and our 'utility_functions_library'
    target_link_libraries(Mat-app ${OpenCV_LIBS} utility_functions_library)

endif(OpenCV_FOUND)
