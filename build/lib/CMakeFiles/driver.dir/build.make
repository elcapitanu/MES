# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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
CMAKE_COMMAND = "C:/Program Files/Cmake/bin/cmake.exe"

# The command to remove a file.
RM = "C:/Program Files/Cmake/bin/cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:/Users/berna/Documents/INFI/MES

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:/Users/berna/Documents/INFI/MES/build

# Include any dependencies generated for this target.
include lib/CMakeFiles/driver.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include lib/CMakeFiles/driver.dir/compiler_depend.make

# Include the progress variables for this target.
include lib/CMakeFiles/driver.dir/progress.make

# Include the compile flags for this target's objects.
include lib/CMakeFiles/driver.dir/flags.make

lib/CMakeFiles/driver.dir/driver.cpp.obj: lib/CMakeFiles/driver.dir/flags.make
lib/CMakeFiles/driver.dir/driver.cpp.obj: C:/Users/berna/Documents/INFI/MES/lib/driver.cpp
lib/CMakeFiles/driver.dir/driver.cpp.obj: lib/CMakeFiles/driver.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:/Users/berna/Documents/INFI/MES/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lib/CMakeFiles/driver.dir/driver.cpp.obj"
	cd C:/Users/berna/Documents/INFI/MES/build/lib && C:/MinGW/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/CMakeFiles/driver.dir/driver.cpp.obj -MF CMakeFiles/driver.dir/driver.cpp.obj.d -o CMakeFiles/driver.dir/driver.cpp.obj -c C:/Users/berna/Documents/INFI/MES/lib/driver.cpp

lib/CMakeFiles/driver.dir/driver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/driver.dir/driver.cpp.i"
	cd C:/Users/berna/Documents/INFI/MES/build/lib && C:/MinGW/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:/Users/berna/Documents/INFI/MES/lib/driver.cpp > CMakeFiles/driver.dir/driver.cpp.i

lib/CMakeFiles/driver.dir/driver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/driver.dir/driver.cpp.s"
	cd C:/Users/berna/Documents/INFI/MES/build/lib && C:/MinGW/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:/Users/berna/Documents/INFI/MES/lib/driver.cpp -o CMakeFiles/driver.dir/driver.cpp.s

# Object files for target driver
driver_OBJECTS = \
"CMakeFiles/driver.dir/driver.cpp.obj"

# External object files for target driver
driver_EXTERNAL_OBJECTS =

lib/libdriver.a: lib/CMakeFiles/driver.dir/driver.cpp.obj
lib/libdriver.a: lib/CMakeFiles/driver.dir/build.make
lib/libdriver.a: lib/CMakeFiles/driver.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:/Users/berna/Documents/INFI/MES/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libdriver.a"
	cd C:/Users/berna/Documents/INFI/MES/build/lib && $(CMAKE_COMMAND) -P CMakeFiles/driver.dir/cmake_clean_target.cmake
	cd C:/Users/berna/Documents/INFI/MES/build/lib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/driver.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/CMakeFiles/driver.dir/build: lib/libdriver.a
.PHONY : lib/CMakeFiles/driver.dir/build

lib/CMakeFiles/driver.dir/clean:
	cd C:/Users/berna/Documents/INFI/MES/build/lib && $(CMAKE_COMMAND) -P CMakeFiles/driver.dir/cmake_clean.cmake
.PHONY : lib/CMakeFiles/driver.dir/clean

lib/CMakeFiles/driver.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" C:/Users/berna/Documents/INFI/MES C:/Users/berna/Documents/INFI/MES/lib C:/Users/berna/Documents/INFI/MES/build C:/Users/berna/Documents/INFI/MES/build/lib C:/Users/berna/Documents/INFI/MES/build/lib/CMakeFiles/driver.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/CMakeFiles/driver.dir/depend
