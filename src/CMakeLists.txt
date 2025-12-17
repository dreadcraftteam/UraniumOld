#
# CMAKELISTS.TXT FOR URANIUM ENGINE
#

cmake_minimum_required(VERSION 3.10)

project(Uranium LANGUAGES C)

# The projects are in the order of building
add_subdirectory(stdlib)
add_subdirectory(filesystem)
add_subdirectory(launcher)
add_subdirectory(engine)
add_subdirectory(game/client)
add_subdirectory(game/server)

# Disable warning messages
add_definitions(-w)
