#
# CMAKELISTS.TXT FOR ENGINE PROJECT
#

project(engine)

set(SOURCES
    cl_main.c
    cl_main.h
    engine.c
    engine.h
    engine_main.c
    engine_main.h
    engine_window.c
    engine_window.h
    glad.c
    sv_main.c
    sv_main.h
    variables.h
)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

# PCH file :well:
target_precompile_headers(engine PRIVATE "engine_pch.h")

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
                      ${CMAKE_SOURCE_DIR}/lib/x64/libSDL2.a
                      m
)

file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/../build/bin/)
set_target_properties(${PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../build/bin/)

set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")

# Disable warning messages
add_definitions(-w)
