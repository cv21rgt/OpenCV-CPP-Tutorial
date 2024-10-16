# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/gy08rgt/Documents/OpenCV/OpenCV_and_CPP_Repository/OpenCV-CPP-Tutorial/2_Large_Dense_Array_Mat

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gy08rgt/Documents/OpenCV/OpenCV_and_CPP_Repository/OpenCV-CPP-Tutorial/2_Large_Dense_Array_Mat/build

# Include any dependencies generated for this target.
include src/CMakeFiles/utility_functions_library.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/utility_functions_library.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/utility_functions_library.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/utility_functions_library.dir/flags.make

src/CMakeFiles/utility_functions_library.dir/UtilityFunctions/utility_functions.cpp.o: src/CMakeFiles/utility_functions_library.dir/flags.make
src/CMakeFiles/utility_functions_library.dir/UtilityFunctions/utility_functions.cpp.o: /home/gy08rgt/Documents/OpenCV/OpenCV_and_CPP_Repository/OpenCV-CPP-Tutorial/2_Large_Dense_Array_Mat/src/UtilityFunctions/utility_functions.cpp
src/CMakeFiles/utility_functions_library.dir/UtilityFunctions/utility_functions.cpp.o: src/CMakeFiles/utility_functions_library.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gy08rgt/Documents/OpenCV/OpenCV_and_CPP_Repository/OpenCV-CPP-Tutorial/2_Large_Dense_Array_Mat/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/utility_functions_library.dir/UtilityFunctions/utility_functions.cpp.o"
	cd /home/gy08rgt/Documents/OpenCV/OpenCV_and_CPP_Repository/OpenCV-CPP-Tutorial/2_Large_Dense_Array_Mat/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/utility_functions_library.dir/UtilityFunctions/utility_functions.cpp.o -MF CMakeFiles/utility_functions_library.dir/UtilityFunctions/utility_functions.cpp.o.d -o CMakeFiles/utility_functions_library.dir/UtilityFunctions/utility_functions.cpp.o -c /home/gy08rgt/Documents/OpenCV/OpenCV_and_CPP_Repository/OpenCV-CPP-Tutorial/2_Large_Dense_Array_Mat/src/UtilityFunctions/utility_functions.cpp

src/CMakeFiles/utility_functions_library.dir/UtilityFunctions/utility_functions.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/utility_functions_library.dir/UtilityFunctions/utility_functions.cpp.i"
	cd /home/gy08rgt/Documents/OpenCV/OpenCV_and_CPP_Repository/OpenCV-CPP-Tutorial/2_Large_Dense_Array_Mat/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gy08rgt/Documents/OpenCV/OpenCV_and_CPP_Repository/OpenCV-CPP-Tutorial/2_Large_Dense_Array_Mat/src/UtilityFunctions/utility_functions.cpp > CMakeFiles/utility_functions_library.dir/UtilityFunctions/utility_functions.cpp.i

src/CMakeFiles/utility_functions_library.dir/UtilityFunctions/utility_functions.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/utility_functions_library.dir/UtilityFunctions/utility_functions.cpp.s"
	cd /home/gy08rgt/Documents/OpenCV/OpenCV_and_CPP_Repository/OpenCV-CPP-Tutorial/2_Large_Dense_Array_Mat/build/src && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gy08rgt/Documents/OpenCV/OpenCV_and_CPP_Repository/OpenCV-CPP-Tutorial/2_Large_Dense_Array_Mat/src/UtilityFunctions/utility_functions.cpp -o CMakeFiles/utility_functions_library.dir/UtilityFunctions/utility_functions.cpp.s

# Object files for target utility_functions_library
utility_functions_library_OBJECTS = \
"CMakeFiles/utility_functions_library.dir/UtilityFunctions/utility_functions.cpp.o"

# External object files for target utility_functions_library
utility_functions_library_EXTERNAL_OBJECTS =

src/libutility_functions_library.a: src/CMakeFiles/utility_functions_library.dir/UtilityFunctions/utility_functions.cpp.o
src/libutility_functions_library.a: src/CMakeFiles/utility_functions_library.dir/build.make
src/libutility_functions_library.a: src/CMakeFiles/utility_functions_library.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/gy08rgt/Documents/OpenCV/OpenCV_and_CPP_Repository/OpenCV-CPP-Tutorial/2_Large_Dense_Array_Mat/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libutility_functions_library.a"
	cd /home/gy08rgt/Documents/OpenCV/OpenCV_and_CPP_Repository/OpenCV-CPP-Tutorial/2_Large_Dense_Array_Mat/build/src && $(CMAKE_COMMAND) -P CMakeFiles/utility_functions_library.dir/cmake_clean_target.cmake
	cd /home/gy08rgt/Documents/OpenCV/OpenCV_and_CPP_Repository/OpenCV-CPP-Tutorial/2_Large_Dense_Array_Mat/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/utility_functions_library.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/utility_functions_library.dir/build: src/libutility_functions_library.a
.PHONY : src/CMakeFiles/utility_functions_library.dir/build

src/CMakeFiles/utility_functions_library.dir/clean:
	cd /home/gy08rgt/Documents/OpenCV/OpenCV_and_CPP_Repository/OpenCV-CPP-Tutorial/2_Large_Dense_Array_Mat/build/src && $(CMAKE_COMMAND) -P CMakeFiles/utility_functions_library.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/utility_functions_library.dir/clean

src/CMakeFiles/utility_functions_library.dir/depend:
	cd /home/gy08rgt/Documents/OpenCV/OpenCV_and_CPP_Repository/OpenCV-CPP-Tutorial/2_Large_Dense_Array_Mat/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gy08rgt/Documents/OpenCV/OpenCV_and_CPP_Repository/OpenCV-CPP-Tutorial/2_Large_Dense_Array_Mat /home/gy08rgt/Documents/OpenCV/OpenCV_and_CPP_Repository/OpenCV-CPP-Tutorial/2_Large_Dense_Array_Mat/src /home/gy08rgt/Documents/OpenCV/OpenCV_and_CPP_Repository/OpenCV-CPP-Tutorial/2_Large_Dense_Array_Mat/build /home/gy08rgt/Documents/OpenCV/OpenCV_and_CPP_Repository/OpenCV-CPP-Tutorial/2_Large_Dense_Array_Mat/build/src /home/gy08rgt/Documents/OpenCV/OpenCV_and_CPP_Repository/OpenCV-CPP-Tutorial/2_Large_Dense_Array_Mat/build/src/CMakeFiles/utility_functions_library.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/utility_functions_library.dir/depend

