# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

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
CMAKE_COMMAND = /Applications/CMake.app/Contents/bin/cmake

# The command to remove a file.
RM = /Applications/CMake.app/Contents/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/joshuayoung/desktop/base4/Assignment_2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/joshuayoung/desktop/base4/Assignment_2/build

# Include any dependencies generated for this target.
include CMakeFiles/main_blending_bin.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/main_blending_bin.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/main_blending_bin.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/main_blending_bin.dir/flags.make

CMakeFiles/main_blending_bin.dir/extra/main_blending.cpp.o: CMakeFiles/main_blending_bin.dir/flags.make
CMakeFiles/main_blending_bin.dir/extra/main_blending.cpp.o: ../extra/main_blending.cpp
CMakeFiles/main_blending_bin.dir/extra/main_blending.cpp.o: CMakeFiles/main_blending_bin.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/joshuayoung/desktop/base4/Assignment_2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/main_blending_bin.dir/extra/main_blending.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main_blending_bin.dir/extra/main_blending.cpp.o -MF CMakeFiles/main_blending_bin.dir/extra/main_blending.cpp.o.d -o CMakeFiles/main_blending_bin.dir/extra/main_blending.cpp.o -c /Users/joshuayoung/desktop/base4/Assignment_2/extra/main_blending.cpp

CMakeFiles/main_blending_bin.dir/extra/main_blending.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main_blending_bin.dir/extra/main_blending.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/joshuayoung/desktop/base4/Assignment_2/extra/main_blending.cpp > CMakeFiles/main_blending_bin.dir/extra/main_blending.cpp.i

CMakeFiles/main_blending_bin.dir/extra/main_blending.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main_blending_bin.dir/extra/main_blending.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/joshuayoung/desktop/base4/Assignment_2/extra/main_blending.cpp -o CMakeFiles/main_blending_bin.dir/extra/main_blending.cpp.s

CMakeFiles/main_blending_bin.dir/src/Helpers.cpp.o: CMakeFiles/main_blending_bin.dir/flags.make
CMakeFiles/main_blending_bin.dir/src/Helpers.cpp.o: ../src/Helpers.cpp
CMakeFiles/main_blending_bin.dir/src/Helpers.cpp.o: CMakeFiles/main_blending_bin.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/joshuayoung/desktop/base4/Assignment_2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/main_blending_bin.dir/src/Helpers.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main_blending_bin.dir/src/Helpers.cpp.o -MF CMakeFiles/main_blending_bin.dir/src/Helpers.cpp.o.d -o CMakeFiles/main_blending_bin.dir/src/Helpers.cpp.o -c /Users/joshuayoung/desktop/base4/Assignment_2/src/Helpers.cpp

CMakeFiles/main_blending_bin.dir/src/Helpers.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main_blending_bin.dir/src/Helpers.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/joshuayoung/desktop/base4/Assignment_2/src/Helpers.cpp > CMakeFiles/main_blending_bin.dir/src/Helpers.cpp.i

CMakeFiles/main_blending_bin.dir/src/Helpers.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main_blending_bin.dir/src/Helpers.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/joshuayoung/desktop/base4/Assignment_2/src/Helpers.cpp -o CMakeFiles/main_blending_bin.dir/src/Helpers.cpp.s

# Object files for target main_blending_bin
main_blending_bin_OBJECTS = \
"CMakeFiles/main_blending_bin.dir/extra/main_blending.cpp.o" \
"CMakeFiles/main_blending_bin.dir/src/Helpers.cpp.o"

# External object files for target main_blending_bin
main_blending_bin_EXTERNAL_OBJECTS =

main_blending_bin: CMakeFiles/main_blending_bin.dir/extra/main_blending.cpp.o
main_blending_bin: CMakeFiles/main_blending_bin.dir/src/Helpers.cpp.o
main_blending_bin: CMakeFiles/main_blending_bin.dir/build.make
main_blending_bin: libglfw3.a
main_blending_bin: CMakeFiles/main_blending_bin.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/joshuayoung/desktop/base4/Assignment_2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable main_blending_bin"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/main_blending_bin.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/main_blending_bin.dir/build: main_blending_bin
.PHONY : CMakeFiles/main_blending_bin.dir/build

CMakeFiles/main_blending_bin.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/main_blending_bin.dir/cmake_clean.cmake
.PHONY : CMakeFiles/main_blending_bin.dir/clean

CMakeFiles/main_blending_bin.dir/depend:
	cd /Users/joshuayoung/desktop/base4/Assignment_2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/joshuayoung/desktop/base4/Assignment_2 /Users/joshuayoung/desktop/base4/Assignment_2 /Users/joshuayoung/desktop/base4/Assignment_2/build /Users/joshuayoung/desktop/base4/Assignment_2/build /Users/joshuayoung/desktop/base4/Assignment_2/build/CMakeFiles/main_blending_bin.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/main_blending_bin.dir/depend

