# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/obj/Desktop/faks/stl1a-gorlaligit

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/obj/Desktop/faks/stl1a-gorlaligit

# Include any dependencies generated for this target.
include test/CMakeFiles/test_zad.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/test_zad.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/test_zad.dir/flags.make

test/CMakeFiles/test_zad.dir/test-zad.cpp.o: test/CMakeFiles/test_zad.dir/flags.make
test/CMakeFiles/test_zad.dir/test-zad.cpp.o: test/test-zad.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/obj/Desktop/faks/stl1a-gorlaligit/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/test_zad.dir/test-zad.cpp.o"
	cd /home/obj/Desktop/faks/stl1a-gorlaligit/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_zad.dir/test-zad.cpp.o -c /home/obj/Desktop/faks/stl1a-gorlaligit/test/test-zad.cpp

test/CMakeFiles/test_zad.dir/test-zad.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_zad.dir/test-zad.cpp.i"
	cd /home/obj/Desktop/faks/stl1a-gorlaligit/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/obj/Desktop/faks/stl1a-gorlaligit/test/test-zad.cpp > CMakeFiles/test_zad.dir/test-zad.cpp.i

test/CMakeFiles/test_zad.dir/test-zad.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_zad.dir/test-zad.cpp.s"
	cd /home/obj/Desktop/faks/stl1a-gorlaligit/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/obj/Desktop/faks/stl1a-gorlaligit/test/test-zad.cpp -o CMakeFiles/test_zad.dir/test-zad.cpp.s

test/CMakeFiles/test_zad.dir/test-zad.cpp.o.requires:

.PHONY : test/CMakeFiles/test_zad.dir/test-zad.cpp.o.requires

test/CMakeFiles/test_zad.dir/test-zad.cpp.o.provides: test/CMakeFiles/test_zad.dir/test-zad.cpp.o.requires
	$(MAKE) -f test/CMakeFiles/test_zad.dir/build.make test/CMakeFiles/test_zad.dir/test-zad.cpp.o.provides.build
.PHONY : test/CMakeFiles/test_zad.dir/test-zad.cpp.o.provides

test/CMakeFiles/test_zad.dir/test-zad.cpp.o.provides.build: test/CMakeFiles/test_zad.dir/test-zad.cpp.o


# Object files for target test_zad
test_zad_OBJECTS = \
"CMakeFiles/test_zad.dir/test-zad.cpp.o"

# External object files for target test_zad
test_zad_EXTERNAL_OBJECTS =

test/test_zad: test/CMakeFiles/test_zad.dir/test-zad.cpp.o
test/test_zad: test/CMakeFiles/test_zad.dir/build.make
test/test_zad: src/libstl_lib.a
test/test_zad: libgoogletest.a
test/test_zad: test/CMakeFiles/test_zad.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/obj/Desktop/faks/stl1a-gorlaligit/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test_zad"
	cd /home/obj/Desktop/faks/stl1a-gorlaligit/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_zad.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/test_zad.dir/build: test/test_zad

.PHONY : test/CMakeFiles/test_zad.dir/build

test/CMakeFiles/test_zad.dir/requires: test/CMakeFiles/test_zad.dir/test-zad.cpp.o.requires

.PHONY : test/CMakeFiles/test_zad.dir/requires

test/CMakeFiles/test_zad.dir/clean:
	cd /home/obj/Desktop/faks/stl1a-gorlaligit/test && $(CMAKE_COMMAND) -P CMakeFiles/test_zad.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/test_zad.dir/clean

test/CMakeFiles/test_zad.dir/depend:
	cd /home/obj/Desktop/faks/stl1a-gorlaligit && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/obj/Desktop/faks/stl1a-gorlaligit /home/obj/Desktop/faks/stl1a-gorlaligit/test /home/obj/Desktop/faks/stl1a-gorlaligit /home/obj/Desktop/faks/stl1a-gorlaligit/test /home/obj/Desktop/faks/stl1a-gorlaligit/test/CMakeFiles/test_zad.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/test_zad.dir/depend

