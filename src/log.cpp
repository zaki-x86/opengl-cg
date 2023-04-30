#include "log.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GL_LOG_FILE "gl.log"

bool restart_gl_log() {
    FILE* file = fopen(GL_LOG_FILE, "w");
    if(!file) {
        fprintf(stderr,
            "ERROR: could not open GL_LOG_FILE log file %s for writing\n",
            GL_LOG_FILE);
        return false;
    }

    time_t now = time(NULL);
    char* date = ctime(&now);
    fprintf(file, "GL_LOG_FILE log. local time %s\n", date);
    fclose(file);

    return true;
}

bool gl_log(const char* message, ...) {
    va_list arg_ptr;
    FILE* file = fopen(GL_LOG_FILE, "a");

    if(!file) {
        fprintf(stderr,
            "ERROR: could not open GL_LOG_FILE %s file for appending\n",
            GL_LOG_FILE);
        return false;
    }

    va_start(arg_ptr, message);
    vfprintf(file, message, arg_ptr);
    va_end(arg_ptr);
    fclose(file);

    return true;
}

bool gl_log_err(const char* message, ...) {
    va_list arg_ptr;
    FILE* file = fopen(GL_LOG_FILE, "a");

    if(!file) {
        fprintf(stderr,
            "ERROR: could not open GL_LOG_FILE %s file for appending\n",
            GL_LOG_FILE);
        return false;
    }

    va_start(arg_ptr, message);
    vfprintf(file, message, arg_ptr);
    va_end(arg_ptr);
    va_start(arg_ptr, message);
    vfprintf(stderr, message, arg_ptr);
    va_end(arg_ptr);
    fclose(file);

    return true;
}

void log_gl_params() {
    GLenum params[] = {
        GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,
        GL_MAX_CUBE_MAP_TEXTURE_SIZE,
        GL_MAX_DRAW_BUFFERS,
        GL_MAX_FRAGMENT_UNIFORM_COMPONENTS,
        GL_MAX_TEXTURE_IMAGE_UNITS,
        GL_MAX_TEXTURE_SIZE,
        GL_MAX_VARYING_FLOATS,
        GL_MAX_VERTEX_ATTRIBS,
        GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS,
        GL_MAX_VERTEX_UNIFORM_COMPONENTS,
        GL_MAX_VIEWPORT_DIMS,
        GL_STEREO,
    };
    const char* names[] = {
        "GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS",
        "GL_MAX_CUBE_MAP_TEXTURE_SIZE",
        "GL_MAX_DRAW_BUFFERS",
        "GL_MAX_FRAGMENT_UNIFORM_COMPONENTS",
        "GL_MAX_TEXTURE_IMAGE_UNITS",
        "GL_MAX_TEXTURE_SIZE",
        "GL_MAX_VARYING_FLOATS",
        "GL_MAX_VERTEX_ATTRIBS",
        "GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS",
        "GL_MAX_VERTEX_UNIFORM_COMPONENTS",
        "GL_MAX_VIEWPORT_DIMS",
        "GL_STEREO",
    };

    gl_log("GL Context Params:\n");
    
    //char msg[256];

    // integers - only works if the order is 0-10 integer return types
    for (int i = 0; i < 10; i++) {
        int v = 0;
        glGetIntegerv(params[i], &v);
        gl_log("%s %i\n", names[i], v);
    }

    // others
    int v[2];
    v[0] = v[1] = 0;
    glGetIntegerv(params[10], v);
    gl_log("%s %i %i\n", names[10], v[0], v[1]);
    unsigned char s = 0;
    glGetBooleanv(params[11], &s);
    gl_log("%s %u\n", names[11], (unsigned int)s);
    gl_log("-----------------------------\n");
}

const char* glGetErrorString(GLenum error)
{
    switch (error)
    {
    case GL_NO_ERROR:          return "No Error";
    case GL_INVALID_ENUM:      return "Invalid Enum";
    case GL_INVALID_VALUE:     return "Invalid Value";
    case GL_INVALID_OPERATION: return "Invalid Operation";
    case GL_INVALID_FRAMEBUFFER_OPERATION: return "Invalid Framebuffer Operation";
    case GL_OUT_OF_MEMORY:     return "Out of Memory";
    case GL_STACK_UNDERFLOW:   return "Stack Underflow";
    case GL_STACK_OVERFLOW:    return "Stack Overflow";
    case GL_CONTEXT_LOST:      return "Context Lost";
    default:                   return "Unknown Error";
    }
}