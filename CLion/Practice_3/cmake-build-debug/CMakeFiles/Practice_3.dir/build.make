# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.26

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2023.2.2\bin\cmake\win\x64\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2023.2.2\bin\cmake\win\x64\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\shilo\Documents\GitClones\SIAOD\CLion\Practice_3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\shilo\Documents\GitClones\SIAOD\CLion\Practice_3\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Practice_3.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Practice_3.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Practice_3.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Practice_3.dir/flags.make

CMakeFiles/Practice_3.dir/main.cpp.obj: CMakeFiles/Practice_3.dir/flags.make
CMakeFiles/Practice_3.dir/main.cpp.obj: C:/Users/shilo/Documents/GitClones/SIAOD/CLion/Practice_3/main.cpp
CMakeFiles/Practice_3.dir/main.cpp.obj: CMakeFiles/Practice_3.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\shilo\Documents\GitClones\SIAOD\CLion\Practice_3\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Practice_3.dir/main.cpp.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Practice_3.dir/main.cpp.obj -MF CMakeFiles\Practice_3.dir\main.cpp.obj.d -o CMakeFiles\Practice_3.dir\main.cpp.obj -c C:\Users\shilo\Documents\GitClones\SIAOD\CLion\Practice_3\main.cpp

CMakeFiles/Practice_3.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Practice_3.dir/main.cpp.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\shilo\Documents\GitClones\SIAOD\CLion\Practice_3\main.cpp > CMakeFiles\Practice_3.dir\main.cpp.i

CMakeFiles/Practice_3.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Practice_3.dir/main.cpp.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\shilo\Documents\GitClones\SIAOD\CLion\Practice_3\main.cpp -o CMakeFiles\Practice_3.dir\main.cpp.s

# Object files for target Practice_3
Practice_3_OBJECTS = \
"CMakeFiles/Practice_3.dir/main.cpp.obj"

# External object files for target Practice_3
Practice_3_EXTERNAL_OBJECTS =

Practice_3.exe: CMakeFiles/Practice_3.dir/main.cpp.obj
Practice_3.exe: CMakeFiles/Practice_3.dir/build.make
Practice_3.exe: CMakeFiles/Practice_3.dir/linkLibs.rsp
Practice_3.exe: CMakeFiles/Practice_3.dir/objects1.rsp
Practice_3.exe: CMakeFiles/Practice_3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\shilo\Documents\GitClones\SIAOD\CLion\Practice_3\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Practice_3.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Practice_3.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Practice_3.dir/build: Practice_3.exe
.PHONY : CMakeFiles/Practice_3.dir/build

CMakeFiles/Practice_3.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Practice_3.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Practice_3.dir/clean

CMakeFiles/Practice_3.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\shilo\Documents\GitClones\SIAOD\CLion\Practice_3 C:\Users\shilo\Documents\GitClones\SIAOD\CLion\Practice_3 C:\Users\shilo\Documents\GitClones\SIAOD\CLion\Practice_3\cmake-build-debug C:\Users\shilo\Documents\GitClones\SIAOD\CLion\Practice_3\cmake-build-debug C:\Users\shilo\Documents\GitClones\SIAOD\CLion\Practice_3\cmake-build-debug\CMakeFiles\Practice_3.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Practice_3.dir/depend

