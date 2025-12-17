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

# Linking libraries:
target_link_libraries(${LAUNCHER_NAME}
                      PRIVATE

                      stdlib
                      filesystem
                      ${CMAKE_SOURCE_DIR}/lib/x64/libSDL2.a
                      m
)

file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/../build)
set_target_properties(${LAUNCHER_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../build)

set_target_properties(${LAUNCHER_NAME} PROPERTIES PREFIX "")

# Disable warning messages
add_definitions(-w)
