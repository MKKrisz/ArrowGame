# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_SOURCE_DIR = /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/build

# Include any dependencies generated for this target.
include CMakeFiles/ArrowGame.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/ArrowGame.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/ArrowGame.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ArrowGame.dir/flags.make

CMakeFiles/ArrowGame.dir/main.c.o: CMakeFiles/ArrowGame.dir/flags.make
CMakeFiles/ArrowGame.dir/main.c.o: /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/main.c
CMakeFiles/ArrowGame.dir/main.c.o: CMakeFiles/ArrowGame.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/ArrowGame.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/ArrowGame.dir/main.c.o -MF CMakeFiles/ArrowGame.dir/main.c.o.d -o CMakeFiles/ArrowGame.dir/main.c.o -c /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/main.c

CMakeFiles/ArrowGame.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/ArrowGame.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/main.c > CMakeFiles/ArrowGame.dir/main.c.i

CMakeFiles/ArrowGame.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/ArrowGame.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/main.c -o CMakeFiles/ArrowGame.dir/main.c.s

CMakeFiles/ArrowGame.dir/src/graphics/color.c.o: CMakeFiles/ArrowGame.dir/flags.make
CMakeFiles/ArrowGame.dir/src/graphics/color.c.o: /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/src/graphics/color.c
CMakeFiles/ArrowGame.dir/src/graphics/color.c.o: CMakeFiles/ArrowGame.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/ArrowGame.dir/src/graphics/color.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/ArrowGame.dir/src/graphics/color.c.o -MF CMakeFiles/ArrowGame.dir/src/graphics/color.c.o.d -o CMakeFiles/ArrowGame.dir/src/graphics/color.c.o -c /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/src/graphics/color.c

CMakeFiles/ArrowGame.dir/src/graphics/color.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/ArrowGame.dir/src/graphics/color.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/src/graphics/color.c > CMakeFiles/ArrowGame.dir/src/graphics/color.c.i

CMakeFiles/ArrowGame.dir/src/graphics/color.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/ArrowGame.dir/src/graphics/color.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/src/graphics/color.c -o CMakeFiles/ArrowGame.dir/src/graphics/color.c.s

CMakeFiles/ArrowGame.dir/src/game.c.o: CMakeFiles/ArrowGame.dir/flags.make
CMakeFiles/ArrowGame.dir/src/game.c.o: /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/src/game.c
CMakeFiles/ArrowGame.dir/src/game.c.o: CMakeFiles/ArrowGame.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/ArrowGame.dir/src/game.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/ArrowGame.dir/src/game.c.o -MF CMakeFiles/ArrowGame.dir/src/game.c.o.d -o CMakeFiles/ArrowGame.dir/src/game.c.o -c /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/src/game.c

CMakeFiles/ArrowGame.dir/src/game.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/ArrowGame.dir/src/game.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/src/game.c > CMakeFiles/ArrowGame.dir/src/game.c.i

CMakeFiles/ArrowGame.dir/src/game.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/ArrowGame.dir/src/game.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/src/game.c -o CMakeFiles/ArrowGame.dir/src/game.c.s

CMakeFiles/ArrowGame.dir/src/particle.c.o: CMakeFiles/ArrowGame.dir/flags.make
CMakeFiles/ArrowGame.dir/src/particle.c.o: /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/src/particle.c
CMakeFiles/ArrowGame.dir/src/particle.c.o: CMakeFiles/ArrowGame.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/ArrowGame.dir/src/particle.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/ArrowGame.dir/src/particle.c.o -MF CMakeFiles/ArrowGame.dir/src/particle.c.o.d -o CMakeFiles/ArrowGame.dir/src/particle.c.o -c /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/src/particle.c

CMakeFiles/ArrowGame.dir/src/particle.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/ArrowGame.dir/src/particle.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/src/particle.c > CMakeFiles/ArrowGame.dir/src/particle.c.i

CMakeFiles/ArrowGame.dir/src/particle.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/ArrowGame.dir/src/particle.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/src/particle.c -o CMakeFiles/ArrowGame.dir/src/particle.c.s

CMakeFiles/ArrowGame.dir/src/arrow.c.o: CMakeFiles/ArrowGame.dir/flags.make
CMakeFiles/ArrowGame.dir/src/arrow.c.o: /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/src/arrow.c
CMakeFiles/ArrowGame.dir/src/arrow.c.o: CMakeFiles/ArrowGame.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/ArrowGame.dir/src/arrow.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/ArrowGame.dir/src/arrow.c.o -MF CMakeFiles/ArrowGame.dir/src/arrow.c.o.d -o CMakeFiles/ArrowGame.dir/src/arrow.c.o -c /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/src/arrow.c

CMakeFiles/ArrowGame.dir/src/arrow.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/ArrowGame.dir/src/arrow.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/src/arrow.c > CMakeFiles/ArrowGame.dir/src/arrow.c.i

CMakeFiles/ArrowGame.dir/src/arrow.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/ArrowGame.dir/src/arrow.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/src/arrow.c -o CMakeFiles/ArrowGame.dir/src/arrow.c.s

CMakeFiles/ArrowGame.dir/src/bullet.c.o: CMakeFiles/ArrowGame.dir/flags.make
CMakeFiles/ArrowGame.dir/src/bullet.c.o: /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/src/bullet.c
CMakeFiles/ArrowGame.dir/src/bullet.c.o: CMakeFiles/ArrowGame.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/ArrowGame.dir/src/bullet.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/ArrowGame.dir/src/bullet.c.o -MF CMakeFiles/ArrowGame.dir/src/bullet.c.o.d -o CMakeFiles/ArrowGame.dir/src/bullet.c.o -c /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/src/bullet.c

CMakeFiles/ArrowGame.dir/src/bullet.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/ArrowGame.dir/src/bullet.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/src/bullet.c > CMakeFiles/ArrowGame.dir/src/bullet.c.i

CMakeFiles/ArrowGame.dir/src/bullet.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/ArrowGame.dir/src/bullet.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/src/bullet.c -o CMakeFiles/ArrowGame.dir/src/bullet.c.s

CMakeFiles/ArrowGame.dir/src/weapon.c.o: CMakeFiles/ArrowGame.dir/flags.make
CMakeFiles/ArrowGame.dir/src/weapon.c.o: /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/src/weapon.c
CMakeFiles/ArrowGame.dir/src/weapon.c.o: CMakeFiles/ArrowGame.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/ArrowGame.dir/src/weapon.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/ArrowGame.dir/src/weapon.c.o -MF CMakeFiles/ArrowGame.dir/src/weapon.c.o.d -o CMakeFiles/ArrowGame.dir/src/weapon.c.o -c /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/src/weapon.c

CMakeFiles/ArrowGame.dir/src/weapon.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/ArrowGame.dir/src/weapon.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/src/weapon.c > CMakeFiles/ArrowGame.dir/src/weapon.c.i

CMakeFiles/ArrowGame.dir/src/weapon.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/ArrowGame.dir/src/weapon.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/src/weapon.c -o CMakeFiles/ArrowGame.dir/src/weapon.c.s

CMakeFiles/ArrowGame.dir/src/graphics/graphics.c.o: CMakeFiles/ArrowGame.dir/flags.make
CMakeFiles/ArrowGame.dir/src/graphics/graphics.c.o: /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/src/graphics/graphics.c
CMakeFiles/ArrowGame.dir/src/graphics/graphics.c.o: CMakeFiles/ArrowGame.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/ArrowGame.dir/src/graphics/graphics.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/ArrowGame.dir/src/graphics/graphics.c.o -MF CMakeFiles/ArrowGame.dir/src/graphics/graphics.c.o.d -o CMakeFiles/ArrowGame.dir/src/graphics/graphics.c.o -c /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/src/graphics/graphics.c

CMakeFiles/ArrowGame.dir/src/graphics/graphics.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/ArrowGame.dir/src/graphics/graphics.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/src/graphics/graphics.c > CMakeFiles/ArrowGame.dir/src/graphics/graphics.c.i

CMakeFiles/ArrowGame.dir/src/graphics/graphics.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/ArrowGame.dir/src/graphics/graphics.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/src/graphics/graphics.c -o CMakeFiles/ArrowGame.dir/src/graphics/graphics.c.s

CMakeFiles/ArrowGame.dir/src/control/input.c.o: CMakeFiles/ArrowGame.dir/flags.make
CMakeFiles/ArrowGame.dir/src/control/input.c.o: /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/src/control/input.c
CMakeFiles/ArrowGame.dir/src/control/input.c.o: CMakeFiles/ArrowGame.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object CMakeFiles/ArrowGame.dir/src/control/input.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/ArrowGame.dir/src/control/input.c.o -MF CMakeFiles/ArrowGame.dir/src/control/input.c.o.d -o CMakeFiles/ArrowGame.dir/src/control/input.c.o -c /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/src/control/input.c

CMakeFiles/ArrowGame.dir/src/control/input.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/ArrowGame.dir/src/control/input.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/src/control/input.c > CMakeFiles/ArrowGame.dir/src/control/input.c.i

CMakeFiles/ArrowGame.dir/src/control/input.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/ArrowGame.dir/src/control/input.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/src/control/input.c -o CMakeFiles/ArrowGame.dir/src/control/input.c.s

CMakeFiles/ArrowGame.dir/src/control/random.c.o: CMakeFiles/ArrowGame.dir/flags.make
CMakeFiles/ArrowGame.dir/src/control/random.c.o: /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/src/control/random.c
CMakeFiles/ArrowGame.dir/src/control/random.c.o: CMakeFiles/ArrowGame.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object CMakeFiles/ArrowGame.dir/src/control/random.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/ArrowGame.dir/src/control/random.c.o -MF CMakeFiles/ArrowGame.dir/src/control/random.c.o.d -o CMakeFiles/ArrowGame.dir/src/control/random.c.o -c /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/src/control/random.c

CMakeFiles/ArrowGame.dir/src/control/random.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/ArrowGame.dir/src/control/random.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/src/control/random.c > CMakeFiles/ArrowGame.dir/src/control/random.c.i

CMakeFiles/ArrowGame.dir/src/control/random.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/ArrowGame.dir/src/control/random.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/src/control/random.c -o CMakeFiles/ArrowGame.dir/src/control/random.c.s

CMakeFiles/ArrowGame.dir/src/math/vector.c.o: CMakeFiles/ArrowGame.dir/flags.make
CMakeFiles/ArrowGame.dir/src/math/vector.c.o: /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/src/math/vector.c
CMakeFiles/ArrowGame.dir/src/math/vector.c.o: CMakeFiles/ArrowGame.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building C object CMakeFiles/ArrowGame.dir/src/math/vector.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/ArrowGame.dir/src/math/vector.c.o -MF CMakeFiles/ArrowGame.dir/src/math/vector.c.o.d -o CMakeFiles/ArrowGame.dir/src/math/vector.c.o -c /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/src/math/vector.c

CMakeFiles/ArrowGame.dir/src/math/vector.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/ArrowGame.dir/src/math/vector.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/src/math/vector.c > CMakeFiles/ArrowGame.dir/src/math/vector.c.i

CMakeFiles/ArrowGame.dir/src/math/vector.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/ArrowGame.dir/src/math/vector.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/src/math/vector.c -o CMakeFiles/ArrowGame.dir/src/math/vector.c.s

CMakeFiles/ArrowGame.dir/src/math/lerp.c.o: CMakeFiles/ArrowGame.dir/flags.make
CMakeFiles/ArrowGame.dir/src/math/lerp.c.o: /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/src/math/lerp.c
CMakeFiles/ArrowGame.dir/src/math/lerp.c.o: CMakeFiles/ArrowGame.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building C object CMakeFiles/ArrowGame.dir/src/math/lerp.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/ArrowGame.dir/src/math/lerp.c.o -MF CMakeFiles/ArrowGame.dir/src/math/lerp.c.o.d -o CMakeFiles/ArrowGame.dir/src/math/lerp.c.o -c /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/src/math/lerp.c

CMakeFiles/ArrowGame.dir/src/math/lerp.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/ArrowGame.dir/src/math/lerp.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/src/math/lerp.c > CMakeFiles/ArrowGame.dir/src/math/lerp.c.i

CMakeFiles/ArrowGame.dir/src/math/lerp.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/ArrowGame.dir/src/math/lerp.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/src/math/lerp.c -o CMakeFiles/ArrowGame.dir/src/math/lerp.c.s

CMakeFiles/ArrowGame.dir/src/dataStructures/ParticlePasta.c.o: CMakeFiles/ArrowGame.dir/flags.make
CMakeFiles/ArrowGame.dir/src/dataStructures/ParticlePasta.c.o: /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/src/dataStructures/ParticlePasta.c
CMakeFiles/ArrowGame.dir/src/dataStructures/ParticlePasta.c.o: CMakeFiles/ArrowGame.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building C object CMakeFiles/ArrowGame.dir/src/dataStructures/ParticlePasta.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/ArrowGame.dir/src/dataStructures/ParticlePasta.c.o -MF CMakeFiles/ArrowGame.dir/src/dataStructures/ParticlePasta.c.o.d -o CMakeFiles/ArrowGame.dir/src/dataStructures/ParticlePasta.c.o -c /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/src/dataStructures/ParticlePasta.c

CMakeFiles/ArrowGame.dir/src/dataStructures/ParticlePasta.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/ArrowGame.dir/src/dataStructures/ParticlePasta.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/src/dataStructures/ParticlePasta.c > CMakeFiles/ArrowGame.dir/src/dataStructures/ParticlePasta.c.i

CMakeFiles/ArrowGame.dir/src/dataStructures/ParticlePasta.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/ArrowGame.dir/src/dataStructures/ParticlePasta.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/src/dataStructures/ParticlePasta.c -o CMakeFiles/ArrowGame.dir/src/dataStructures/ParticlePasta.c.s

CMakeFiles/ArrowGame.dir/src/dataStructures/BulletPasta.c.o: CMakeFiles/ArrowGame.dir/flags.make
CMakeFiles/ArrowGame.dir/src/dataStructures/BulletPasta.c.o: /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/src/dataStructures/BulletPasta.c
CMakeFiles/ArrowGame.dir/src/dataStructures/BulletPasta.c.o: CMakeFiles/ArrowGame.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building C object CMakeFiles/ArrowGame.dir/src/dataStructures/BulletPasta.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/ArrowGame.dir/src/dataStructures/BulletPasta.c.o -MF CMakeFiles/ArrowGame.dir/src/dataStructures/BulletPasta.c.o.d -o CMakeFiles/ArrowGame.dir/src/dataStructures/BulletPasta.c.o -c /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/src/dataStructures/BulletPasta.c

CMakeFiles/ArrowGame.dir/src/dataStructures/BulletPasta.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/ArrowGame.dir/src/dataStructures/BulletPasta.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/src/dataStructures/BulletPasta.c > CMakeFiles/ArrowGame.dir/src/dataStructures/BulletPasta.c.i

CMakeFiles/ArrowGame.dir/src/dataStructures/BulletPasta.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/ArrowGame.dir/src/dataStructures/BulletPasta.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/src/dataStructures/BulletPasta.c -o CMakeFiles/ArrowGame.dir/src/dataStructures/BulletPasta.c.s

CMakeFiles/ArrowGame.dir/src/menu/textrenderer.c.o: CMakeFiles/ArrowGame.dir/flags.make
CMakeFiles/ArrowGame.dir/src/menu/textrenderer.c.o: /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/src/menu/textrenderer.c
CMakeFiles/ArrowGame.dir/src/menu/textrenderer.c.o: CMakeFiles/ArrowGame.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building C object CMakeFiles/ArrowGame.dir/src/menu/textrenderer.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/ArrowGame.dir/src/menu/textrenderer.c.o -MF CMakeFiles/ArrowGame.dir/src/menu/textrenderer.c.o.d -o CMakeFiles/ArrowGame.dir/src/menu/textrenderer.c.o -c /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/src/menu/textrenderer.c

CMakeFiles/ArrowGame.dir/src/menu/textrenderer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/ArrowGame.dir/src/menu/textrenderer.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/src/menu/textrenderer.c > CMakeFiles/ArrowGame.dir/src/menu/textrenderer.c.i

CMakeFiles/ArrowGame.dir/src/menu/textrenderer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/ArrowGame.dir/src/menu/textrenderer.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/src/menu/textrenderer.c -o CMakeFiles/ArrowGame.dir/src/menu/textrenderer.c.s

# Object files for target ArrowGame
ArrowGame_OBJECTS = \
"CMakeFiles/ArrowGame.dir/main.c.o" \
"CMakeFiles/ArrowGame.dir/src/graphics/color.c.o" \
"CMakeFiles/ArrowGame.dir/src/game.c.o" \
"CMakeFiles/ArrowGame.dir/src/particle.c.o" \
"CMakeFiles/ArrowGame.dir/src/arrow.c.o" \
"CMakeFiles/ArrowGame.dir/src/bullet.c.o" \
"CMakeFiles/ArrowGame.dir/src/weapon.c.o" \
"CMakeFiles/ArrowGame.dir/src/graphics/graphics.c.o" \
"CMakeFiles/ArrowGame.dir/src/control/input.c.o" \
"CMakeFiles/ArrowGame.dir/src/control/random.c.o" \
"CMakeFiles/ArrowGame.dir/src/math/vector.c.o" \
"CMakeFiles/ArrowGame.dir/src/math/lerp.c.o" \
"CMakeFiles/ArrowGame.dir/src/dataStructures/ParticlePasta.c.o" \
"CMakeFiles/ArrowGame.dir/src/dataStructures/BulletPasta.c.o" \
"CMakeFiles/ArrowGame.dir/src/menu/textrenderer.c.o"

# External object files for target ArrowGame
ArrowGame_EXTERNAL_OBJECTS =

ArrowGame: CMakeFiles/ArrowGame.dir/main.c.o
ArrowGame: CMakeFiles/ArrowGame.dir/src/graphics/color.c.o
ArrowGame: CMakeFiles/ArrowGame.dir/src/game.c.o
ArrowGame: CMakeFiles/ArrowGame.dir/src/particle.c.o
ArrowGame: CMakeFiles/ArrowGame.dir/src/arrow.c.o
ArrowGame: CMakeFiles/ArrowGame.dir/src/bullet.c.o
ArrowGame: CMakeFiles/ArrowGame.dir/src/weapon.c.o
ArrowGame: CMakeFiles/ArrowGame.dir/src/graphics/graphics.c.o
ArrowGame: CMakeFiles/ArrowGame.dir/src/control/input.c.o
ArrowGame: CMakeFiles/ArrowGame.dir/src/control/random.c.o
ArrowGame: CMakeFiles/ArrowGame.dir/src/math/vector.c.o
ArrowGame: CMakeFiles/ArrowGame.dir/src/math/lerp.c.o
ArrowGame: CMakeFiles/ArrowGame.dir/src/dataStructures/ParticlePasta.c.o
ArrowGame: CMakeFiles/ArrowGame.dir/src/dataStructures/BulletPasta.c.o
ArrowGame: CMakeFiles/ArrowGame.dir/src/menu/textrenderer.c.o
ArrowGame: CMakeFiles/ArrowGame.dir/build.make
ArrowGame: /usr/lib/libSDL2-2.0.so.0.2800.4
ArrowGame: /usr/lib/libSDL2_image.so
ArrowGame: /usr/lib/libSDL2_ttf.so
ArrowGame: CMakeFiles/ArrowGame.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Linking C executable ArrowGame"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ArrowGame.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ArrowGame.dir/build: ArrowGame
.PHONY : CMakeFiles/ArrowGame.dir/build

CMakeFiles/ArrowGame.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ArrowGame.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ArrowGame.dir/clean

CMakeFiles/ArrowGame.dir/depend:
	cd /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/build /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/build /home/krisz/Dokumentumok/Repos/c_uni/ArrowGame/build/CMakeFiles/ArrowGame.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/ArrowGame.dir/depend
