cmake_minimum_required(VERSION 3.16)

project(opengl-tutorials
        VERSION 0.1
        DESCRIPTION "OpenGL tutorials"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")

# Find OpenGL, GLEW, GLFW and assimp
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(assimp REQUIRED)

file(GLOB_RECURSE SOURCES sources/*.cpp)
file(GLOB_RECURSE EXT_SOURCES ../ext/*cpp)

# Create an executable from each source
foreach(source ${SOURCES})
    # get base filename
    get_filename_component(name ${source} NAME)
    # remove .cpp
    string(REGEX REPLACE ".cpp$" "" TUTORIAL_EXE ${name})

    # create executable
    add_executable(${TUTORIAL_EXE} ${source} ${EXT_SOURCES})

    target_include_directories(${TUTORIAL_EXE} PRIVATE
        ${OPENGL_INCLUDE_DIRS}
        ${GLEW_INCLUDE_DIRS}
        ${GLFW_INCLUDE_DIRS}
        ../ext
    )

    target_link_libraries(${TUTORIAL_EXE}
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        glfw
        assimp
    )

    # Store the executable in tutorial/ folder
    set_target_properties(${TUTORIAL_EXE} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tutorial
    )
    
    # Tell CMake to copy all shaders and assets to the build directory
    file(COPY assets DESTINATION ${CMAKE_BINARY_DIR}/tutorial)

    # If debug, send -DDEBUG to the compiler
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${TUTORIAL_EXE} PRIVATE _DEBUG ggdb3 EXCEPTIONS_ENABLED)
    endif()
endforeach()
