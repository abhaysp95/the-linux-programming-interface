cmake_minimum_required(VERSION 3.15...3.20)

project(The_Linux_Programming_Interface LANGUAGES C)

SET(CMAKE_C_STANDARD 99)
SET(CMAKE_C_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
	# don't know but after making the build as debug, you have to
	# clear those build files to make the project in release mode
	set(CMAKE_BUILD_TYPE Release)
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# ====================================================
# Uncomment below lines if you are going to use clang
# (you can also modify these flags as per your need)
# ====================================================
 set(CMAKE_C_COMPILER    "/usr/bin/clang")
 set(CMAKE_C_FLAGS       "-Wall -std=c99")


 set(CMAKE_C_FLAGS_DEBUG "-ggdb")
 set(CMAKE_C_FLAGS_RELEASE "-O3")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

set(LIB_SOURCES tlpi_lib/src/ename.c.inc tlpi_lib/src/error_functions.c tlpi_lib/src/get_num.c)
set(LIB_HEADERS tlpi_lib/include/tlpi/tlpi_hdr.h tlpi_lib/include/tlpi/error_functions.h tlpi_lib/include/tlpi/get_num.h)

add_library(tlpi_library STATIC "${LIB_SOURCES}" "${LIB_HEADERS}")

target_include_directories(tlpi_library PUBLIC tlpi_lib/include)

target_compile_features(tlpi_library PUBLIC c_std_99)

add_subdirectory(test_tlpi)
add_subdirectory(system_programming_concept)
add_subdirectory(file_io_the_universal_io_model)
add_subdirectory(file_io_further_details)
add_subdirectory(processes)
add_subdirectory(memory_allocation)
add_subdirectory(users_and_groups)
add_subdirectory(system_and_process_information)
add_subdirectory(./system_limits_and_options)
add_subdirectory(appendix_b)

if("${CMAKE_EXPORT_COMPILE_COMMANDS}")
	if(EXISTS "${CMAKE_BINARY_DIR}/compile_commands.json" AND NOT IS_DIRECTORY "${CMAKE_BINARY_DIR}/compile_commands.json")
		execute_process(COMMAND ln -f -s "${CMAKE_BINARY_DIR}/compile_commands.json" "${CMAKE_SOURCE_DIR}/compile_commands.json"
			RESULT_VARIABLE LN_RESULT)
		if(NOT LN_RESULT EQUAL "0")
			message(STATUS "Can't create symlink for compile_commands.json")
		endif()
	endif()
else()
	message(STATUS "CMAKE_EXPORT_COMPILE_COMPILE_COMMANDS is OFF")
endif()
