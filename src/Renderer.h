#pragma once

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <memory>
#include "Gui.h"

#include "Shader.h"

#define SCREEN_WIDTH 1400
#define SCREEN_HEIGHT 900

class Renderer {
public:
    Renderer();

    void Render() const;

    GLFWwindow *getWindow() const;

    static const char *getGLSLVersion();

    template<typename T, auto Method>
    struct GLFWCallback {
        template<typename... Args>
        static void Invoke(Args... args) {
            // First parameter is always GLFWwindow*
            GLFWwindow *window = std::get<0>(std::tuple<Args...>(args...));

            if (T *self = static_cast<T *>(glfwGetWindowUserPointer(window))) {
                (self->*Method)(args...);
            }
        }
    };

    ~Renderer();

private:
    GLFWwindow *window = nullptr;
    std::unique_ptr<Gui> gui;
    std::unique_ptr<Shader> shader;
    int framebufferWidth, framebufferHeight;
    float windowContentXScale, windowContentYScale = 0;

    float vertices[8] = {
        1.0f, 1.0f, // top right
        1.0f, -1.0f, // bottom right
        -1.0f, -1.0f, // bottom left
        -1.0f, 1.0f // top left
    };
    unsigned int indices[6] = {
        // note that we start from 0!
        0, 1, 3, // first triangle
        1, 2, 3 // second triangle
    };


    void processInput(GLFWwindow *window) const;

    void onWindowSizeChange(GLFWwindow *window, int width, int height) const;

    void onFrameBufferSizeChange(GLFWwindow *window, int width, int height);

    void onWindowFocusChanged(GLFWwindow *window, int focused) const;

    void onMouseCallback(GLFWwindow *window, double xpos, double ypos) const;

    void onScrollCallback(GLFWwindow *window, double xoffset, double yoffset) const;
};
