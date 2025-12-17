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
    engine_messages.c
    engine_messages.h
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

if(ARCH_BITNESS STREQUAL "32")
    set(SDL_LIB_PATH "${CMAKE_SOURCE_DIR}/lib/x32/libSDL2.a")
else()
    set(SDL_LIB_PATH "${CMAKE_SOURCE_DIR}/lib/x64/libSDL2.a")
endif()

# Linking libraries:
target_link_libraries(${PROJECT_NAME} 
                      PRIVATE

                      stdlib
                      filesystem
                      ${SDL_LIB_PATH}
                      m
)

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
