#ifndef _GLFW_WRAPPER_H_
#define _GLFW_WRAPPER_H_

#include <iostream>
#include <string>

struct GLFWwindow;
typedef void (*GLFWerrorfun)(int error_code, const char *description);
typedef void (*GLFWframebuffersizefun)(GLFWwindow *window, int width, int height);


struct GLFWConfig {
    uint8_t majorVersion;
    uint8_t minorVersion;
    int profile;
    bool resizable;
    bool forwardCompat;
    GLFWerrorfun errorCallback;
    GLFWframebuffersizefun framebufferSizeCallback;
};

class GLFWWrapper  {
public:
    using WindowType = GLFWwindow;
    using WindowPtr = GLFWwindow*;
    using ConfigType = GLFWConfig;


    GLFWWrapper(const GLFWConfig& config, int width, int height, const std::string& title);

    GLFWWrapper(const GLFWWrapper& other) = delete;

    GLFWWrapper(GLFWWrapper&& other) = delete;

    ~GLFWWrapper() {
        destroy();
    }

    GLFWWrapper& operator=(const GLFWWrapper& other) = delete;

    GLFWWrapper& operator=(GLFWWrapper&& other) = delete;

    bool initialized() const;

    void destroy();

    bool shouldClose() const;

    void setShouldClose(bool value);

    void swapBuffers();

    void pollEvents();

    std::pair<int, int> getSize() const;

    void setSize(int width, int height);

    std::string getTitle() const;

    void setTitle(const std::string& title);

    GLFWwindow* getWindow() const;

    std::pair<int, int> getFramebufferSize() const;

    void makeContextCurrent();

private:
    GLFWwindow* m_window;
    bool m_initialized;
    std::string m_title;
};

#endif // !
