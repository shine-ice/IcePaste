# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = "D:\MyPrograms\JetBrains\CLion 2021.2.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\MyPrograms\JetBrains\CLion 2021.2.4\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = E:\CodeSpace\QtSpace\WorkSpace007\IcePaste

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = E:\CodeSpace\QtSpace\WorkSpace007\IcePaste\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/IcePaste.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/IcePaste.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/IcePaste.dir/flags.make

CMakeFiles/IcePaste.dir/IcePaste_autogen/mocs_compilation.cpp.obj: CMakeFiles/IcePaste.dir/flags.make
CMakeFiles/IcePaste.dir/IcePaste_autogen/mocs_compilation.cpp.obj: CMakeFiles/IcePaste.dir/includes_CXX.rsp
CMakeFiles/IcePaste.dir/IcePaste_autogen/mocs_compilation.cpp.obj: IcePaste_autogen/mocs_compilation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\CodeSpace\QtSpace\WorkSpace007\IcePaste\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/IcePaste.dir/IcePaste_autogen/mocs_compilation.cpp.obj"
	D:\MyPrograms\Qt\Tools\mingw810_32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\IcePaste.dir\IcePaste_autogen\mocs_compilation.cpp.obj -c E:\CodeSpace\QtSpace\WorkSpace007\IcePaste\cmake-build-debug\IcePaste_autogen\mocs_compilation.cpp

CMakeFiles/IcePaste.dir/IcePaste_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/IcePaste.dir/IcePaste_autogen/mocs_compilation.cpp.i"
	D:\MyPrograms\Qt\Tools\mingw810_32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\CodeSpace\QtSpace\WorkSpace007\IcePaste\cmake-build-debug\IcePaste_autogen\mocs_compilation.cpp > CMakeFiles\IcePaste.dir\IcePaste_autogen\mocs_compilation.cpp.i

CMakeFiles/IcePaste.dir/IcePaste_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/IcePaste.dir/IcePaste_autogen/mocs_compilation.cpp.s"
	D:\MyPrograms\Qt\Tools\mingw810_32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\CodeSpace\QtSpace\WorkSpace007\IcePaste\cmake-build-debug\IcePaste_autogen\mocs_compilation.cpp -o CMakeFiles\IcePaste.dir\IcePaste_autogen\mocs_compilation.cpp.s

CMakeFiles/IcePaste.dir/main.cpp.obj: CMakeFiles/IcePaste.dir/flags.make
CMakeFiles/IcePaste.dir/main.cpp.obj: CMakeFiles/IcePaste.dir/includes_CXX.rsp
CMakeFiles/IcePaste.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\CodeSpace\QtSpace\WorkSpace007\IcePaste\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/IcePaste.dir/main.cpp.obj"
	D:\MyPrograms\Qt\Tools\mingw810_32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\IcePaste.dir\main.cpp.obj -c E:\CodeSpace\QtSpace\WorkSpace007\IcePaste\main.cpp

CMakeFiles/IcePaste.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/IcePaste.dir/main.cpp.i"
	D:\MyPrograms\Qt\Tools\mingw810_32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\CodeSpace\QtSpace\WorkSpace007\IcePaste\main.cpp > CMakeFiles\IcePaste.dir\main.cpp.i

CMakeFiles/IcePaste.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/IcePaste.dir/main.cpp.s"
	D:\MyPrograms\Qt\Tools\mingw810_32\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\CodeSpace\QtSpace\WorkSpace007\IcePaste\main.cpp -o CMakeFiles\IcePaste.dir\main.cpp.s

# Object files for target IcePaste
IcePaste_OBJECTS = \
"CMakeFiles/IcePaste.dir/IcePaste_autogen/mocs_compilation.cpp.obj" \
"CMakeFiles/IcePaste.dir/main.cpp.obj"

# External object files for target IcePaste
IcePaste_EXTERNAL_OBJECTS =

IcePaste.exe: CMakeFiles/IcePaste.dir/IcePaste_autogen/mocs_compilation.cpp.obj
IcePaste.exe: CMakeFiles/IcePaste.dir/main.cpp.obj
IcePaste.exe: CMakeFiles/IcePaste.dir/build.make
IcePaste.exe: D:/MyPrograms/Qt/5.15.2/mingw81_32/lib/libQt5Widgets.a
IcePaste.exe: D:/MyPrograms/Qt/5.15.2/mingw81_32/lib/libQt5Gui.a
IcePaste.exe: D:/MyPrograms/Qt/5.15.2/mingw81_32/lib/libQt5Core.a
IcePaste.exe: CMakeFiles/IcePaste.dir/linklibs.rsp
IcePaste.exe: CMakeFiles/IcePaste.dir/objects1.rsp
IcePaste.exe: CMakeFiles/IcePaste.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=E:\CodeSpace\QtSpace\WorkSpace007\IcePaste\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable IcePaste.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\IcePaste.dir\link.txt --verbose=$(VERBOSE)
	"D:\MyPrograms\JetBrains\CLion 2021.2.4\bin\cmake\win\bin\cmake.exe" -E make_directory E:/CodeSpace/QtSpace/WorkSpace007/IcePaste/cmake-build-debug/plugins/platforms/
	"D:\MyPrograms\JetBrains\CLion 2021.2.4\bin\cmake\win\bin\cmake.exe" -E copy D:/MyPrograms/Qt/5.15.2/mingw81_32/plugins/platforms/qwindows.dll E:/CodeSpace/QtSpace/WorkSpace007/IcePaste/cmake-build-debug/plugins/platforms/
	"D:\MyPrograms\JetBrains\CLion 2021.2.4\bin\cmake\win\bin\cmake.exe" -E copy D:/MyPrograms/Qt/5.15.2/mingw81_32/bin/Qt5Core.dll E:/CodeSpace/QtSpace/WorkSpace007/IcePaste/cmake-build-debug
	"D:\MyPrograms\JetBrains\CLion 2021.2.4\bin\cmake\win\bin\cmake.exe" -E copy D:/MyPrograms/Qt/5.15.2/mingw81_32/bin/Qt5Gui.dll E:/CodeSpace/QtSpace/WorkSpace007/IcePaste/cmake-build-debug
	"D:\MyPrograms\JetBrains\CLion 2021.2.4\bin\cmake\win\bin\cmake.exe" -E copy D:/MyPrograms/Qt/5.15.2/mingw81_32/bin/Qt5Widgets.dll E:/CodeSpace/QtSpace/WorkSpace007/IcePaste/cmake-build-debug

# Rule to build all files generated by this target.
CMakeFiles/IcePaste.dir/build: IcePaste.exe
.PHONY : CMakeFiles/IcePaste.dir/build

CMakeFiles/IcePaste.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\IcePaste.dir\cmake_clean.cmake
.PHONY : CMakeFiles/IcePaste.dir/clean

CMakeFiles/IcePaste.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" E:\CodeSpace\QtSpace\WorkSpace007\IcePaste E:\CodeSpace\QtSpace\WorkSpace007\IcePaste E:\CodeSpace\QtSpace\WorkSpace007\IcePaste\cmake-build-debug E:\CodeSpace\QtSpace\WorkSpace007\IcePaste\cmake-build-debug E:\CodeSpace\QtSpace\WorkSpace007\IcePaste\cmake-build-debug\CMakeFiles\IcePaste.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/IcePaste.dir/depend

