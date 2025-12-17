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

set(ARCH_BITNESS ${BIT_ARCH} CACHE INTERNAL "Architecture bitness")

# The projects are in the order of building
add_subdirectory(stdlib)
add_subdirectory(filesystem)
add_subdirectory(launcher)
add_subdirectory(engine)
add_subdirectory(game/client)
add_subdirectory(game/server)

# Disable warning messages
add_definitions(-w)
