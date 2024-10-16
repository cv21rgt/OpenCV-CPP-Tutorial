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
include Mat-app/CMakeFiles/Mat-app.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include Mat-app/CMakeFiles/Mat-app.dir/compiler_depend.make

# Include the progress variables for this target.
include Mat-app/CMakeFiles/Mat-app.dir/progress.make

# Include the compile flags for this target's objects.
include Mat-app/CMakeFiles/Mat-app.dir/flags.make

Mat-app/CMakeFiles/Mat-app.dir/Main.cpp.o: Mat-app/CMakeFiles/Mat-app.dir/flags.make
Mat-app/CMakeFiles/Mat-app.dir/Main.cpp.o: /home/gy08rgt/Documents/OpenCV/OpenCV_and_CPP_Repository/OpenCV-CPP-Tutorial/2_Large_Dense_Array_Mat/Mat-app/Main.cpp
Mat-app/CMakeFiles/Mat-app.dir/Main.cpp.o: Mat-app/CMakeFiles/Mat-app.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gy08rgt/Documents/OpenCV/OpenCV_and_CPP_Repository/OpenCV-CPP-Tutorial/2_Large_Dense_Array_Mat/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Mat-app/CMakeFiles/Mat-app.dir/Main.cpp.o"
	cd /home/gy08rgt/Documents/OpenCV/OpenCV_and_CPP_Repository/OpenCV-CPP-Tutorial/2_Large_Dense_Array_Mat/build/Mat-app && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Mat-app/CMakeFiles/Mat-app.dir/Main.cpp.o -MF CMakeFiles/Mat-app.dir/Main.cpp.o.d -o CMakeFiles/Mat-app.dir/Main.cpp.o -c /home/gy08rgt/Documents/OpenCV/OpenCV_and_CPP_Repository/OpenCV-CPP-Tutorial/2_Large_Dense_Array_Mat/Mat-app/Main.cpp

Mat-app/CMakeFiles/Mat-app.dir/Main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Mat-app.dir/Main.cpp.i"
	cd /home/gy08rgt/Documents/OpenCV/OpenCV_and_CPP_Repository/OpenCV-CPP-Tutorial/2_Large_Dense_Array_Mat/build/Mat-app && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gy08rgt/Documents/OpenCV/OpenCV_and_CPP_Repository/OpenCV-CPP-Tutorial/2_Large_Dense_Array_Mat/Mat-app/Main.cpp > CMakeFiles/Mat-app.dir/Main.cpp.i

Mat-app/CMakeFiles/Mat-app.dir/Main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Mat-app.dir/Main.cpp.s"
	cd /home/gy08rgt/Documents/OpenCV/OpenCV_and_CPP_Repository/OpenCV-CPP-Tutorial/2_Large_Dense_Array_Mat/build/Mat-app && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gy08rgt/Documents/OpenCV/OpenCV_and_CPP_Repository/OpenCV-CPP-Tutorial/2_Large_Dense_Array_Mat/Mat-app/Main.cpp -o CMakeFiles/Mat-app.dir/Main.cpp.s

# Object files for target Mat-app
Mat__app_OBJECTS = \
"CMakeFiles/Mat-app.dir/Main.cpp.o"

# External object files for target Mat-app
Mat__app_EXTERNAL_OBJECTS =

Mat-app/Mat-app: Mat-app/CMakeFiles/Mat-app.dir/Main.cpp.o
Mat-app/Mat-app: Mat-app/CMakeFiles/Mat-app.dir/build.make
Mat-app/Mat-app: /home/gy08rgt/Third_Party_Libraries/OpenCV_4.8.0/release/installed/lib/libopencv_core.so.4.8.0
Mat-app/Mat-app: src/libutility_functions_library.a
Mat-app/Mat-app: /home/gy08rgt/Third_Party_Libraries/OpenCV_4.8.0/release/installed/lib/libopencv_core.so.4.8.0
Mat-app/Mat-app: Mat-app/CMakeFiles/Mat-app.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/gy08rgt/Documents/OpenCV/OpenCV_and_CPP_Repository/OpenCV-CPP-Tutorial/2_Large_Dense_Array_Mat/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Mat-app"
	cd /home/gy08rgt/Documents/OpenCV/OpenCV_and_CPP_Repository/OpenCV-CPP-Tutorial/2_Large_Dense_Array_Mat/build/Mat-app && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Mat-app.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Mat-app/CMakeFiles/Mat-app.dir/build: Mat-app/Mat-app
.PHONY : Mat-app/CMakeFiles/Mat-app.dir/build

Mat-app/CMakeFiles/Mat-app.dir/clean:
	cd /home/gy08rgt/Documents/OpenCV/OpenCV_and_CPP_Repository/OpenCV-CPP-Tutorial/2_Large_Dense_Array_Mat/build/Mat-app && $(CMAKE_COMMAND) -P CMakeFiles/Mat-app.dir/cmake_clean.cmake
.PHONY : Mat-app/CMakeFiles/Mat-app.dir/clean

Mat-app/CMakeFiles/Mat-app.dir/depend:
	cd /home/gy08rgt/Documents/OpenCV/OpenCV_and_CPP_Repository/OpenCV-CPP-Tutorial/2_Large_Dense_Array_Mat/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gy08rgt/Documents/OpenCV/OpenCV_and_CPP_Repository/OpenCV-CPP-Tutorial/2_Large_Dense_Array_Mat /home/gy08rgt/Documents/OpenCV/OpenCV_and_CPP_Repository/OpenCV-CPP-Tutorial/2_Large_Dense_Array_Mat/Mat-app /home/gy08rgt/Documents/OpenCV/OpenCV_and_CPP_Repository/OpenCV-CPP-Tutorial/2_Large_Dense_Array_Mat/build /home/gy08rgt/Documents/OpenCV/OpenCV_and_CPP_Repository/OpenCV-CPP-Tutorial/2_Large_Dense_Array_Mat/build/Mat-app /home/gy08rgt/Documents/OpenCV/OpenCV_and_CPP_Repository/OpenCV-CPP-Tutorial/2_Large_Dense_Array_Mat/build/Mat-app/CMakeFiles/Mat-app.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Mat-app/CMakeFiles/Mat-app.dir/depend

