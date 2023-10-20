# - set CMake requirements then declare project
cmake_minimum_required(VERSION 3.2)
project(MPAGSCipher VERSION 0.1.0)

# - when Makefiles are generated, output all command lines by default
# Do this to begin with so it is easy to see what the compiler command/flags
# are used. This can also be accomplished by removing the 'set' command and
# running make as 'make VERBOSE=1'.

set(CMAKE_VERBOSE_MAKEFILE ON)


# - Declare the build of mpags-cipher main program

add_executable(mpags-cipher 
	mpags-cipher.cpp
	MPAGSCipher/TransformChar.cpp
	MPAGSCipher/ProcessCmdLine.cpp
	)

target_include_directories(mpags-cipher
	PRIVATE MPAGSCipher
	)


set(CMAKE_CXX_EXTENSION OFF)

# - Use our standard set of flags
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Wfatal-errors -Wshadow -pedantic")

target_compile_features(mpags-cipher
	PRIVATE cxx_auto_type cxx_range_for cxx_uniform_initialization
)
