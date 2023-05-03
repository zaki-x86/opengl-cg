cmake_minimum_required(VERSION 3.15)

project(cg-tutorial)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror")

file(GLOB_RECURSE EXT_SOURCES ${CMAKE_SOURCE_DIR}/ext/*cpp)
file(GLOB_RECURSE TEST_SOURCES ${CMAKE_SOURCE_DIR}/test/*.cpp)

add_executable(cg-tutorial
        ${TEST_SOURCES}
        ${EXT_SOURCES}
)

target_include_directories(${PROJECT_NAME} PRIVATE
        ${OPENGL_INCLUDE_DIRS}
        ${GLEW_INCLUDE_DIRS}
        ${GLFW_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}/ext
)

target_link_libraries(${PROJECT_NAME}
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        glfw
)

# Store the executable in bin/ folder
set_target_properties(${PROJECT_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Tell CMake to copy all shaders and assets to the build directory
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR}/bin)

# If debug, send -DDEBUG to the compiler
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE _DEBUG ggdb3 EXCEPTIONS_ENABLED)
endif()