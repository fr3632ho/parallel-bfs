# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

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
CMAKE_SOURCE_DIR = /home/fredrik/workbench/parallel-bfs/test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/fredrik/workbench/parallel-bfs

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/fredrik/workbench/parallel-bfs/CMakeFiles /home/fredrik/workbench/parallel-bfs//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/fredrik/workbench/parallel-bfs/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named parallel-bfs_test

# Build rule for target.
parallel-bfs_test: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 parallel-bfs_test
.PHONY : parallel-bfs_test

# fast build rule for target.
parallel-bfs_test/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/parallel-bfs_test.dir/build.make CMakeFiles/parallel-bfs_test.dir/build
.PHONY : parallel-bfs_test/fast

#=============================================================================
# Target rules for targets named bag_test

# Build rule for target.
bag_test: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 bag_test
.PHONY : bag_test

# fast build rule for target.
bag_test/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/bag_test.dir/build.make CMakeFiles/bag_test.dir/build
.PHONY : bag_test/fast

# target to build an object file
source/bag_test.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/bag_test.dir/build.make CMakeFiles/bag_test.dir/source/bag_test.o
.PHONY : source/bag_test.o

# target to preprocess a source file
source/bag_test.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/bag_test.dir/build.make CMakeFiles/bag_test.dir/source/bag_test.i
.PHONY : source/bag_test.i

# target to generate assembly for a file
source/bag_test.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/bag_test.dir/build.make CMakeFiles/bag_test.dir/source/bag_test.s
.PHONY : source/bag_test.s

# target to build an object file
source/parallel-bfs_test.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/parallel-bfs_test.dir/build.make CMakeFiles/parallel-bfs_test.dir/source/parallel-bfs_test.o
.PHONY : source/parallel-bfs_test.o

# target to preprocess a source file
source/parallel-bfs_test.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/parallel-bfs_test.dir/build.make CMakeFiles/parallel-bfs_test.dir/source/parallel-bfs_test.i
.PHONY : source/parallel-bfs_test.i

# target to generate assembly for a file
source/parallel-bfs_test.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/parallel-bfs_test.dir/build.make CMakeFiles/parallel-bfs_test.dir/source/parallel-bfs_test.s
.PHONY : source/parallel-bfs_test.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... bag_test"
	@echo "... parallel-bfs_test"
	@echo "... source/bag_test.o"
	@echo "... source/bag_test.i"
	@echo "... source/bag_test.s"
	@echo "... source/parallel-bfs_test.o"
	@echo "... source/parallel-bfs_test.i"
	@echo "... source/parallel-bfs_test.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

