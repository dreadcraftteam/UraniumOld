#
# CMAKELISTS.TXT FOR URANIUM ENGINE
#

cmake_minimum_required(VERSION 3.10)

project(Uranium, LANGUAGES C)

# The projects are in the order of building
add_subdirectory(stdlib)
add_subdirectory(filesystem)
add_subdirectory(inputsystem)
add_subdirectory(materialsystem)
add_subdirectory(gameui)
add_subdirectory(launcher)
add_subdirectory(engine)
add_subdirectory(game)

# Disable warning messages
add_definitions(-w)
