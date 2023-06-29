#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

#include "../opengl/utils.h"

/**
 * @brief Generic window class
 * 
 * You will need to pass the window handler wrapper as a template parameter.
 * The window class will inherit from the window handler wrapper.
 * all methods from the window handler wrapper will be available in the window class.
 * 
 * @tparam WindowHandler 
 */
template <typename WindowHandler, typename WindowHandlerConfig>
class Window : public WindowHandler {
public:
    using WindowType = typename WindowHandler::WindowType;
    using WindowPtr = typename WindowHandler::WindowPtr;

    Window(WindowHandlerConfig config, int width, int height, const std::string& title) 
    : WindowHandler(config, width, height, title) {}

};

#endif // !_WINDOW_H_
