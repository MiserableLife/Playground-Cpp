cmake_minimum_required (VERSION 2.6)
project (BinaryWatcher)
# The version number. 
set (BinaryWatcher_VERSION_MAJOR 1)
set (BinaryWatcher_VERSION_MINOR 0)

set(CMAKE_C_COMPILER "clang++") # set compiler

#build type configuration 
#Debug / Release / RelWithDebInfo / MinSizeRel
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS_DEBUG "")# compile options only for Debug build type


# configure a header file to pass some of CMake settings to the src code
configure_file(
	"config.h.in"
	"src/config.h"
	)


#setting source files
set(SOURCES src/main.cpp src/OptionChecker.cpp src/Printer.cpp)

#find header files here
include_directories("src")

#add the executable
set ( CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
add_executable(BinaryWatcher ${SOURCES})

# print version work? 
#add_test (Version BinaryWatcher --version)


#install (TARGETS BinaryWatcher DESTINATION bin)
