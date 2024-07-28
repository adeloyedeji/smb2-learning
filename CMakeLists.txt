project(SMBL C)
cmake_minimum_required(VERSION 3.20.0)

if (NOT CMAKE_BUILD_TYPE)
	message(STATUS "No build type selected, defaulting to Debug")
	set(CMAKE_BUILD_TYPE "Debug")
endif ()

if (NOT CMAKE_INSTALL_PREFIX)
    set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)
endif()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wshadow -Wconversion -Wformat -g -std=gnu11")
set(SMBL_COMMON_LIBS smbl-static)

add_subdirectory(src/core)
add_subdirectory(src/tests)