# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = "/home/elli/Documents/Dropbox/The Cooper Union/ArtificialIntelligence/NeuralNetworks/FeretFaceInputProcessor"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/elli/Documents/Dropbox/The Cooper Union/ArtificialIntelligence/NeuralNetworks/FeretFaceInputProcessor"

# Include any dependencies generated for this target.
include CMakeFiles/initialNetBuilder.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/initialNetBuilder.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/initialNetBuilder.dir/flags.make

CMakeFiles/initialNetBuilder.dir/InitialNetBuilder.cpp.o: CMakeFiles/initialNetBuilder.dir/flags.make
CMakeFiles/initialNetBuilder.dir/InitialNetBuilder.cpp.o: InitialNetBuilder.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report "/home/elli/Documents/Dropbox/The Cooper Union/ArtificialIntelligence/NeuralNetworks/FeretFaceInputProcessor/CMakeFiles" $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/initialNetBuilder.dir/InitialNetBuilder.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/initialNetBuilder.dir/InitialNetBuilder.cpp.o -c "/home/elli/Documents/Dropbox/The Cooper Union/ArtificialIntelligence/NeuralNetworks/FeretFaceInputProcessor/InitialNetBuilder.cpp"

CMakeFiles/initialNetBuilder.dir/InitialNetBuilder.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/initialNetBuilder.dir/InitialNetBuilder.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E "/home/elli/Documents/Dropbox/The Cooper Union/ArtificialIntelligence/NeuralNetworks/FeretFaceInputProcessor/InitialNetBuilder.cpp" > CMakeFiles/initialNetBuilder.dir/InitialNetBuilder.cpp.i

CMakeFiles/initialNetBuilder.dir/InitialNetBuilder.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/initialNetBuilder.dir/InitialNetBuilder.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S "/home/elli/Documents/Dropbox/The Cooper Union/ArtificialIntelligence/NeuralNetworks/FeretFaceInputProcessor/InitialNetBuilder.cpp" -o CMakeFiles/initialNetBuilder.dir/InitialNetBuilder.cpp.s

CMakeFiles/initialNetBuilder.dir/InitialNetBuilder.cpp.o.requires:
.PHONY : CMakeFiles/initialNetBuilder.dir/InitialNetBuilder.cpp.o.requires

CMakeFiles/initialNetBuilder.dir/InitialNetBuilder.cpp.o.provides: CMakeFiles/initialNetBuilder.dir/InitialNetBuilder.cpp.o.requires
	$(MAKE) -f CMakeFiles/initialNetBuilder.dir/build.make CMakeFiles/initialNetBuilder.dir/InitialNetBuilder.cpp.o.provides.build
.PHONY : CMakeFiles/initialNetBuilder.dir/InitialNetBuilder.cpp.o.provides

CMakeFiles/initialNetBuilder.dir/InitialNetBuilder.cpp.o.provides.build: CMakeFiles/initialNetBuilder.dir/InitialNetBuilder.cpp.o

# Object files for target initialNetBuilder
initialNetBuilder_OBJECTS = \
"CMakeFiles/initialNetBuilder.dir/InitialNetBuilder.cpp.o"

# External object files for target initialNetBuilder
initialNetBuilder_EXTERNAL_OBJECTS =

initialNetBuilder: CMakeFiles/initialNetBuilder.dir/InitialNetBuilder.cpp.o
initialNetBuilder: CMakeFiles/initialNetBuilder.dir/build.make
initialNetBuilder: CMakeFiles/initialNetBuilder.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable initialNetBuilder"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/initialNetBuilder.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/initialNetBuilder.dir/build: initialNetBuilder
.PHONY : CMakeFiles/initialNetBuilder.dir/build

CMakeFiles/initialNetBuilder.dir/requires: CMakeFiles/initialNetBuilder.dir/InitialNetBuilder.cpp.o.requires
.PHONY : CMakeFiles/initialNetBuilder.dir/requires

CMakeFiles/initialNetBuilder.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/initialNetBuilder.dir/cmake_clean.cmake
.PHONY : CMakeFiles/initialNetBuilder.dir/clean

CMakeFiles/initialNetBuilder.dir/depend:
	cd "/home/elli/Documents/Dropbox/The Cooper Union/ArtificialIntelligence/NeuralNetworks/FeretFaceInputProcessor" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/elli/Documents/Dropbox/The Cooper Union/ArtificialIntelligence/NeuralNetworks/FeretFaceInputProcessor" "/home/elli/Documents/Dropbox/The Cooper Union/ArtificialIntelligence/NeuralNetworks/FeretFaceInputProcessor" "/home/elli/Documents/Dropbox/The Cooper Union/ArtificialIntelligence/NeuralNetworks/FeretFaceInputProcessor" "/home/elli/Documents/Dropbox/The Cooper Union/ArtificialIntelligence/NeuralNetworks/FeretFaceInputProcessor" "/home/elli/Documents/Dropbox/The Cooper Union/ArtificialIntelligence/NeuralNetworks/FeretFaceInputProcessor/CMakeFiles/initialNetBuilder.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/initialNetBuilder.dir/depend

