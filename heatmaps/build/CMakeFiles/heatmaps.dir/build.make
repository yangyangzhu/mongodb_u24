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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/yzhu/project/mongodb_u24/heatmaps

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yzhu/project/mongodb_u24/heatmaps/build

# Include any dependencies generated for this target.
include CMakeFiles/heatmaps.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/heatmaps.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/heatmaps.dir/flags.make

CMakeFiles/heatmaps.dir/heatmaps.cpp.o: CMakeFiles/heatmaps.dir/flags.make
CMakeFiles/heatmaps.dir/heatmaps.cpp.o: ../heatmaps.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/yzhu/project/mongodb_u24/heatmaps/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/heatmaps.dir/heatmaps.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/heatmaps.dir/heatmaps.cpp.o -c /home/yzhu/project/mongodb_u24/heatmaps/heatmaps.cpp

CMakeFiles/heatmaps.dir/heatmaps.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/heatmaps.dir/heatmaps.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/yzhu/project/mongodb_u24/heatmaps/heatmaps.cpp > CMakeFiles/heatmaps.dir/heatmaps.cpp.i

CMakeFiles/heatmaps.dir/heatmaps.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/heatmaps.dir/heatmaps.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/yzhu/project/mongodb_u24/heatmaps/heatmaps.cpp -o CMakeFiles/heatmaps.dir/heatmaps.cpp.s

CMakeFiles/heatmaps.dir/heatmaps.cpp.o.requires:
.PHONY : CMakeFiles/heatmaps.dir/heatmaps.cpp.o.requires

CMakeFiles/heatmaps.dir/heatmaps.cpp.o.provides: CMakeFiles/heatmaps.dir/heatmaps.cpp.o.requires
	$(MAKE) -f CMakeFiles/heatmaps.dir/build.make CMakeFiles/heatmaps.dir/heatmaps.cpp.o.provides.build
.PHONY : CMakeFiles/heatmaps.dir/heatmaps.cpp.o.provides

CMakeFiles/heatmaps.dir/heatmaps.cpp.o.provides.build: CMakeFiles/heatmaps.dir/heatmaps.cpp.o

# Object files for target heatmaps
heatmaps_OBJECTS = \
"CMakeFiles/heatmaps.dir/heatmaps.cpp.o"

# External object files for target heatmaps
heatmaps_EXTERNAL_OBJECTS =

heatmaps: CMakeFiles/heatmaps.dir/heatmaps.cpp.o
heatmaps: CMakeFiles/heatmaps.dir/build.make
heatmaps: /usr/local/lib/libopencv_videostab.so.2.4.8
heatmaps: /usr/local/lib/libopencv_video.so.2.4.8
heatmaps: /usr/local/lib/libopencv_ts.a
heatmaps: /usr/local/lib/libopencv_superres.so.2.4.8
heatmaps: /usr/local/lib/libopencv_stitching.so.2.4.8
heatmaps: /usr/local/lib/libopencv_photo.so.2.4.8
heatmaps: /usr/local/lib/libopencv_ocl.so.2.4.8
heatmaps: /usr/local/lib/libopencv_objdetect.so.2.4.8
heatmaps: /usr/local/lib/libopencv_nonfree.so.2.4.8
heatmaps: /usr/local/lib/libopencv_ml.so.2.4.8
heatmaps: /usr/local/lib/libopencv_legacy.so.2.4.8
heatmaps: /usr/local/lib/libopencv_imgproc.so.2.4.8
heatmaps: /usr/local/lib/libopencv_highgui.so.2.4.8
heatmaps: /usr/local/lib/libopencv_gpu.so.2.4.8
heatmaps: /usr/local/lib/libopencv_flann.so.2.4.8
heatmaps: /usr/local/lib/libopencv_features2d.so.2.4.8
heatmaps: /usr/local/lib/libopencv_core.so.2.4.8
heatmaps: /usr/local/lib/libopencv_contrib.so.2.4.8
heatmaps: /usr/local/lib/libopencv_calib3d.so.2.4.8
heatmaps: /usr/local/lib/libopencv_nonfree.so.2.4.8
heatmaps: /usr/local/lib/libopencv_ocl.so.2.4.8
heatmaps: /usr/local/lib/libopencv_gpu.so.2.4.8
heatmaps: /usr/local/lib/libopencv_photo.so.2.4.8
heatmaps: /usr/local/lib/libopencv_objdetect.so.2.4.8
heatmaps: /usr/local/lib/libopencv_legacy.so.2.4.8
heatmaps: /usr/local/lib/libopencv_video.so.2.4.8
heatmaps: /usr/local/lib/libopencv_ml.so.2.4.8
heatmaps: /usr/local/lib/libopencv_calib3d.so.2.4.8
heatmaps: /usr/local/lib/libopencv_features2d.so.2.4.8
heatmaps: /usr/local/lib/libopencv_highgui.so.2.4.8
heatmaps: /usr/local/lib/libopencv_imgproc.so.2.4.8
heatmaps: /usr/local/lib/libopencv_flann.so.2.4.8
heatmaps: /usr/local/lib/libopencv_core.so.2.4.8
heatmaps: CMakeFiles/heatmaps.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable heatmaps"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/heatmaps.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/heatmaps.dir/build: heatmaps
.PHONY : CMakeFiles/heatmaps.dir/build

CMakeFiles/heatmaps.dir/requires: CMakeFiles/heatmaps.dir/heatmaps.cpp.o.requires
.PHONY : CMakeFiles/heatmaps.dir/requires

CMakeFiles/heatmaps.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/heatmaps.dir/cmake_clean.cmake
.PHONY : CMakeFiles/heatmaps.dir/clean

CMakeFiles/heatmaps.dir/depend:
	cd /home/yzhu/project/mongodb_u24/heatmaps/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yzhu/project/mongodb_u24/heatmaps /home/yzhu/project/mongodb_u24/heatmaps /home/yzhu/project/mongodb_u24/heatmaps/build /home/yzhu/project/mongodb_u24/heatmaps/build /home/yzhu/project/mongodb_u24/heatmaps/build/CMakeFiles/heatmaps.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/heatmaps.dir/depend

