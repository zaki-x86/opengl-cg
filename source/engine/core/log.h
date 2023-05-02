#ifndef _LOG_H_
#define _LOG_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GL_LOG_FILE "gl.log"

bool restart_gl_log();

bool gl_log(const char* message, ...);

bool gl_log_err(const char* message, ...);

void log_gl_params();

const char* glGetErrorString(GLenum error);


#endif // !_LOG_H_