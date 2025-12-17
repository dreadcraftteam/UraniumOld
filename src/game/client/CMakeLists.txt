#
# CMAKELISTS.TXT FOR CLIENT PROJECT
#

project(client)

set(SOURCES
    client.c
    client.h
)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

# PCH file :well:
target_precompile_headers(client PRIVATE "client_pch.h")

# Include directories:
target_include_directories(${PROJECT_NAME}
                           PRIVATE

                           ${CMAKE_SOURCE_DIR}/include/
                           ${CMAKE_SOURCE_DIR}/stdlib/
                           ${CMAKE_SOURCE_DIR}/filesystem/
)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Linking libraries:
target_link_libraries(${PROJECT_NAME} 
                      PRIVATE

                      stdlib
                      filesystem
)

# Compile definitions:
add_compile_definitions(CLIENT_MODULE)

file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/../build/bin/)
set_target_properties(${PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../build/bin/)

set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")

if(ARCH_BITNESS STREQUAL "32")
    add_compile_definitions(_32BIT)
    target_compile_options(${PROJECT_NAME} PRIVATE -m32)
    target_link_options(${PROJECT_NAME} PRIVATE -m32)
else()
    add_compile_definitions(_64BIT)
    target_compile_options(${PROJECT_NAME} PRIVATE -m64)
    target_link_options(${PROJECT_NAME} PRIVATE -m64)
endif()

# Disable warning messages
add_definitions(-w)
