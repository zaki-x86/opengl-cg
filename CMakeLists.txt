cmake_minimum_required(VERSION 3.16)

project(glrenderer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(assimp REQUIRED)

file(GLOB_RECURSE SOURCES Renderer/*.cpp)
file(GLOB_RECURSE EXT_SOURCES ext/*cpp)

add_executable(glrenderer
        ${SOURCES}
        ${EXT_SOURCES}
)


target_include_directories(glrenderer PRIVATE
        ${OPENGL_INCLUDE_DIRS}
        ${GLEW_INCLUDE_DIRS}
        ${GLFW_INCLUDE_DIRS}
        ext
        test
)

target_link_libraries(glrenderer
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        glfw
        assimp
)

# Store the executable in bin/ folder
set_target_properties(glrenderer PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Tell CMake to copy all shaders and assets to the build directory
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR}/bin)

# If debug, send -DDEBUG to the compiler
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(glrenderer 
    PRIVATE 
    _DEBUG ggdb3 EXCEPTIONS_ENABLED
    )
endif()

# Add aggressive compiler flags for target `glrenderer`
target_compile_options(glrenderer
    PRIVATE
    -Wall -Wextra -Wpedantic -Werror
)

message(STATUS "Building tutorials")
add_subdirectory(Tutorial)