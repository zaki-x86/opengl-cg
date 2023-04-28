cmake_minimum_required(VERSION 3.16)

project(cg-opengl)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(cg-opengl
        src/main.cpp
)

target_include_directories(cg-opengl PRIVATE
        ${OPENGL_INCLUDE_DIRS}
        ${GLEW_INCLUDE_DIRS}
        ${GLFW_INCLUDE_DIRS}
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

# Tell CMake to copy all shaders to the build directory
file(COPY shaders DESTINATION ${CMAKE_BINARY_DIR}/bin)