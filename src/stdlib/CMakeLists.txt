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

if(ARCH_BITNESS STREQUAL "32")
    add_compile_definitions(BIT32)
    target_compile_options(${PROJECT_NAME} PRIVATE -m32)
    target_link_options(${PROJECT_NAME} PRIVATE -m32)
else()
    add_compile_definitions(BIT64)
    target_compile_options(${PROJECT_NAME} PRIVATE -m64)
    target_link_options(${PROJECT_NAME} PRIVATE -m64)
endif()

add_definitions(-fPIC)
add_definitions(-w)
