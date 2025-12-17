#
# CMAKELISTS.TXT FOR URANIUM ENGINE
#

cmake_minimum_required(VERSION 3.10)

project(Uranium LANGUAGES C)

set(BIT_ARCH "64" CACHE STRING "Architecture (32 or 64 bit)")
set_property(CACHE BIT_ARCH PROPERTY STRINGS "32" "64")

if(NOT BIT_ARCH STREQUAL "32" AND NOT BIT_ARCH STREQUAL "64")
    message(FATAL_ERROR "BIT_ARCH must be either '32' or '64'")
endif()

message(STATUS "Building for ${BIT_ARCH}-bit architecture")

set(ARCH_BITNESS ${BIT_ARCH} CACHE INTERNAL "Architecture bitness")

if(BIT_ARCH STREQUAL "32" AND CMAKE_SIZEOF_VOID_P EQUAL 8)
    message(STATUS "Cross-compiling: 32-bit target on 64-bit host")
elseif(BIT_ARCH STREQUAL "64" AND CMAKE_SIZEOF_VOID_P EQUAL 4)
    message(WARNING "Building 64-bit on 32-bit host might fail")
endif()

# The projects are in the order of building
add_subdirectory(stdlib)
add_subdirectory(filesystem)
add_subdirectory(launcher)
add_subdirectory(engine)
add_subdirectory(game/client)
add_subdirectory(game/server)

# Disable warning messages
add_definitions(-w)
