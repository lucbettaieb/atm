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
CMAKE_SOURCE_DIR = /home/luc/atm

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/luc/atm/build

# Include any dependencies generated for this target.
include third_party/gtest/googletest-build/googlemock/gtest/CMakeFiles/gtest.dir/depend.make

# Include the progress variables for this target.
include third_party/gtest/googletest-build/googlemock/gtest/CMakeFiles/gtest.dir/progress.make

# Include the compile flags for this target's objects.
include third_party/gtest/googletest-build/googlemock/gtest/CMakeFiles/gtest.dir/flags.make

third_party/gtest/googletest-build/googlemock/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o: third_party/gtest/googletest-build/googlemock/gtest/CMakeFiles/gtest.dir/flags.make
third_party/gtest/googletest-build/googlemock/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o: third_party/gtest/googletest-src/googletest/src/gtest-all.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/luc/atm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object third_party/gtest/googletest-build/googlemock/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o"
	cd /home/luc/atm/build/third_party/gtest/googletest-build/googlemock/gtest && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gtest.dir/src/gtest-all.cc.o -c /home/luc/atm/build/third_party/gtest/googletest-src/googletest/src/gtest-all.cc

third_party/gtest/googletest-build/googlemock/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gtest.dir/src/gtest-all.cc.i"
	cd /home/luc/atm/build/third_party/gtest/googletest-build/googlemock/gtest && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/luc/atm/build/third_party/gtest/googletest-src/googletest/src/gtest-all.cc > CMakeFiles/gtest.dir/src/gtest-all.cc.i

third_party/gtest/googletest-build/googlemock/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gtest.dir/src/gtest-all.cc.s"
	cd /home/luc/atm/build/third_party/gtest/googletest-build/googlemock/gtest && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/luc/atm/build/third_party/gtest/googletest-src/googletest/src/gtest-all.cc -o CMakeFiles/gtest.dir/src/gtest-all.cc.s

third_party/gtest/googletest-build/googlemock/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o.requires:

.PHONY : third_party/gtest/googletest-build/googlemock/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o.requires

third_party/gtest/googletest-build/googlemock/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o.provides: third_party/gtest/googletest-build/googlemock/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o.requires
	$(MAKE) -f third_party/gtest/googletest-build/googlemock/gtest/CMakeFiles/gtest.dir/build.make third_party/gtest/googletest-build/googlemock/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o.provides.build
.PHONY : third_party/gtest/googletest-build/googlemock/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o.provides

third_party/gtest/googletest-build/googlemock/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o.provides.build: third_party/gtest/googletest-build/googlemock/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o


# Object files for target gtest
gtest_OBJECTS = \
"CMakeFiles/gtest.dir/src/gtest-all.cc.o"

# External object files for target gtest
gtest_EXTERNAL_OBJECTS =

third_party/gtest/googletest-build/googlemock/gtest/libgtest.a: third_party/gtest/googletest-build/googlemock/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o
third_party/gtest/googletest-build/googlemock/gtest/libgtest.a: third_party/gtest/googletest-build/googlemock/gtest/CMakeFiles/gtest.dir/build.make
third_party/gtest/googletest-build/googlemock/gtest/libgtest.a: third_party/gtest/googletest-build/googlemock/gtest/CMakeFiles/gtest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/luc/atm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libgtest.a"
	cd /home/luc/atm/build/third_party/gtest/googletest-build/googlemock/gtest && $(CMAKE_COMMAND) -P CMakeFiles/gtest.dir/cmake_clean_target.cmake
	cd /home/luc/atm/build/third_party/gtest/googletest-build/googlemock/gtest && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gtest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
third_party/gtest/googletest-build/googlemock/gtest/CMakeFiles/gtest.dir/build: third_party/gtest/googletest-build/googlemock/gtest/libgtest.a

.PHONY : third_party/gtest/googletest-build/googlemock/gtest/CMakeFiles/gtest.dir/build

third_party/gtest/googletest-build/googlemock/gtest/CMakeFiles/gtest.dir/requires: third_party/gtest/googletest-build/googlemock/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o.requires

.PHONY : third_party/gtest/googletest-build/googlemock/gtest/CMakeFiles/gtest.dir/requires

third_party/gtest/googletest-build/googlemock/gtest/CMakeFiles/gtest.dir/clean:
	cd /home/luc/atm/build/third_party/gtest/googletest-build/googlemock/gtest && $(CMAKE_COMMAND) -P CMakeFiles/gtest.dir/cmake_clean.cmake
.PHONY : third_party/gtest/googletest-build/googlemock/gtest/CMakeFiles/gtest.dir/clean

third_party/gtest/googletest-build/googlemock/gtest/CMakeFiles/gtest.dir/depend:
	cd /home/luc/atm/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/luc/atm /home/luc/atm/build/third_party/gtest/googletest-src/googletest /home/luc/atm/build /home/luc/atm/build/third_party/gtest/googletest-build/googlemock/gtest /home/luc/atm/build/third_party/gtest/googletest-build/googlemock/gtest/CMakeFiles/gtest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : third_party/gtest/googletest-build/googlemock/gtest/CMakeFiles/gtest.dir/depend

