#
# CMAKELISTS.TXT FOR LAUNCHER PROJECT
#

project(launcher)

set(LAUNCHER_NAME "uranium")

# Source code
set(SOURCES
    main.c
    main.h
)

add_executable(${LAUNCHER_NAME} ${SOURCES})

# Include directories:
target_include_directories(${LAUNCHER_NAME} 
                            PRIVATE
                        
                            ${CMAKE_SOURCE_DIR}/include/
                            ${CMAKE_SOURCE_DIR}/filesystem/
                            ${CMAKE_SOURCE_DIR}/stdlib/
)

if(ARCH_BITNESS STREQUAL "32")
    set(SDL_LIB_PATH "${CMAKE_SOURCE_DIR}/lib/x32/libSDL2.a")
else()
    set(SDL_LIB_PATH "${CMAKE_SOURCE_DIR}/lib/x64/libSDL2.a")
endif()

# Linking libraries:
target_link_libraries(${LAUNCHER_NAME}
                      PRIVATE

                      stdlib
                      filesystem
                      ${SDL_LIB_PATH}
                      m
)

file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/../build)
set_target_properties(${LAUNCHER_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../build)

set_target_properties(${LAUNCHER_NAME} PROPERTIES PREFIX "")

if(ARCH_BITNESS STREQUAL "32")
    add_compile_definitions(_32BIT)
    target_compile_options(${LAUNCHER_NAME} PRIVATE -m32)
    target_link_options(${LAUNCHER_NAME} PRIVATE -m32)
else()
    add_compile_definitions(_64BIT)
    target_compile_options(${LAUNCHER_NAME} PRIVATE -m64)
    target_link_options(${LAUNCHER_NAME} PRIVATE -m64)
endif()

# Disable warning messages
add_definitions(-w)
