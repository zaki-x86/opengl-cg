#ifndef _UTILS_H_
#define _UTILS_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>

#include "log.h"

#define GL_CHECK_ERRORS() _glCheckErrors(__FILE__, __LINE__)
#define GL_LOG(message, ...) gl_log(message, ##__VA_ARGS__)

void glfw_error_callback(int error, const char* description);


enum RGB
{
    RED = 0x01,
    GREEN = 0x10,
    BLUE = 0x11,
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow *window);

void gradualColorCycle(RGB rgb, glm::vec3* color);

void _update_fps_counter(GLFWwindow* window);

void _glCheckErrors(const char *filename, int line);

void _update_delta_time(float* deltaTime, float* lastFrame);

#endif // !_UTILS_H_