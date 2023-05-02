cmake_minimum_required(VERSION 3.16)

project(cg-opengl)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

file(GLOB_RECURSE SOURCES source/*.cpp)

add_executable(cg-opengl
        source/main.cpp
        source/engine/wrapper/glfw-wrapper.cpp
        source/engine/opengl/OpenGLApp.cpp
        source/engine/core/Vertex.cpp
        source/engine/core/Mesh.cpp
)

target_include_directories(cg-opengl PRIVATE
        ${OPENGL_INCLUDE_DIRS}
        ${GLEW_INCLUDE_DIRS}
        ${GLFW_INCLUDE_DIRS}
        include
)

target_link_libraries(cg-opengl
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        glfw
)

# Store the executable in bin/ folder
set_target_properties(cg-opengl PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Tell CMake to copy all shaders and assets to the build directory
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR}/bin)

# If debug, send -DDEBUG to the compiler
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(cg-opengl PRIVATE _DEBUG ggdb3)
endif()