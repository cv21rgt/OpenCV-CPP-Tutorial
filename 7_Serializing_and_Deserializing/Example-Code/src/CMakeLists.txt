# Note that headers are optional, and do not affect add_library, but they will not
# show up in IDEs unless they are listed in add_library.

# Optionally glob, but only for CMake 3.12 or later:
# file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${ModernCMakeExample_SOURCE_DIR}/include/modern/*.hpp")
set(HEADER_LIST "${PROJECT_SOURCE_DIR}/include/UtilityFunctions/utility_functions.h")
set(SOURCE_LIST "${PROJECT_SOURCE_DIR}/src/UtilityFunctions/utility_functions.cpp")

# Make an automatic library - will be static or dynamic based on user setting
add_library(utility_functions_library STATIC ${SOURCE_LIST} ${HEADER_LIST})

# We need this directory, and users of our library will need it too
target_include_directories(utility_functions_library PUBLIC ../include)

# All users of this library will need at least C++17
target_compile_features(utility_functions_library PUBLIC cxx_std_17)


# IDEs should put the headers in a nice place
source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST})

# Our 'utility_functions_library' needs access to the OpenCV package

# Set path to directory with OpenCVConfig.cmake file
set(OpenCV_DIR "$ENV{HOME}/Third_Party_Libraries/OpenCV_4.8.0/release/installed/lib/cmake/opencv4")

# We only want access to the `core` module
find_package(OpenCV REQUIRED core)

if(OpenCV_FOUND)
    # Additional Include Directories
    include_directories(${OpenCV_INCLUDE_DIRS})

    # Additional Library Directories
    link_directories(${OpenCV_LIB_DIR})

    # Additional dependencies
    target_link_libraries(utility_functions_library ${OpenCV_LIBS})

endif(OpenCV_FOUND)