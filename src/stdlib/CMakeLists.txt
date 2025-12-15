#
# CMAKELISTS.TXT FOR STDLIB PROJECT
#

project(stdlib)

set(SOURCES
    messages.c
    messages.h
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/common/)
set_target_properties(${PROJECT_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/common/)

set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")

add_definitions(-fPIC)
add_definitions(-w)
