# Find the OpenCV package

# Set path to directory with OpenCVConfig.cmake file
# Instead of installing OpenCV to the usual path /usr/local/include ( on Linux O/S) I have installed
# mine in a different directory /home/gy08rgt/Third_Party_Libraries/OpenCV_4.8.0/release/installed 
# I do this for every version of OpenCV I install.
set(OpenCV_DIR "/home/gy08rgt/Third_Party_Libraries/OpenCV_4.8.0/release/installed/lib/cmake/opencv4")

find_package(OpenCV REQUIRED core)

if(OpenCV_FOUND)
    # Additional Include Directories
    include_directories(${OpenCV_INCLUDE_DIRS})

    # Additional Library Directories
    link_directories(${OpenCV_LIB_DIR})

    # Create an executable file from our Main.cpp source file
    add_executable(Mat-app Main.cpp)

    # We want to use C++17 standard
    target_compile_features(Mat-app PRIVATE cxx_std_17)

    # Additional dependencies
    # Our executable is dependend on OpenCV libs and our utility_functions_library
    target_link_libraries(Mat-app ${OpenCV_LIBS} utility_functions_library)

endif(OpenCV_FOUND)