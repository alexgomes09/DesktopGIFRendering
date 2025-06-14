#include "Renderer.h"

Renderer::Renderer() {
    if (!glfwInit()) {
        std::cout << "GLFW Init failed" << std::endl;
        return;
    }

#if __APPLE__
    // GL 3.2 + GLSL 150
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Required on Mac
#endif

    GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello World", nullptr, nullptr);

    if (!window) {
        std::cout << "Couldn't create window" << std::endl;
        return;
    }

    glfwSetWindowUserPointer(window, this);
    this->window = window;

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    gui = std::make_unique<Gui>(window, getGLSLVersion());

    if (gladLoadGL() == 0) {
        printf("Failed to initialize OpenGL loader!\n");
        return;
    }

    shader = std::make_unique<Shader>("../src/shader/vertexshader.glsl", "../src/shader/fragmentshader.glsl");

    printf("Gl Version %s\n", glGetString(GL_VERSION));

    glfwSetWindowSizeCallback(window, &GLFWCallback<Renderer, &Renderer::onWindowSizeChange>::Invoke);
    glfwSetFramebufferSizeCallback(window, &GLFWCallback<Renderer, &Renderer::onFrameBufferSizeChange>::Invoke);
    glfwSetWindowFocusCallback(window, &GLFWCallback<Renderer, &Renderer::onWindowFocusChanged>::Invoke);
    glfwSetCursorPosCallback(window, &GLFWCallback<Renderer, &Renderer::onMouseCallback>::Invoke);
    glfwSetScrollCallback(window, &GLFWCallback<Renderer, &Renderer::onScrollCallback>::Invoke);
    //    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glDisable(GL_DEPTH);
    glEnable(GL_PROGRAM_POINT_SIZE);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
    glfwGetWindowContentScale(window, &windowContentXScale, &windowContentYScale);

    while (!glfwWindowShouldClose(window)) {
        Render();
    }
}

void Renderer::Render() const {
    double currentFrame = glfwGetTime();
    // deltaTime = currentFrame - lastFrame;
    // lastFrame = currentFrame;

    processInput(window);

    glClearColor(0.8, 0.5, 0.5, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glViewport(0, 0, framebufferWidth - gui->GetSidebarWidth() * windowContentXScale, framebufferHeight);

    shader->use();

    // shader->setFloat("size", 30.5f);




    gui->Draw();

    glDrawElements(GL_TRIANGLES, IM_ARRAYSIZE(indices), GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
    // glfwWaitEvents();
}

void Renderer::onWindowSizeChange(GLFWwindow *window, int width, int height) const {
    std::cout << "Width: " << width << " Height: " << height << std::endl;
}

void Renderer::onFrameBufferSizeChange(GLFWwindow *window, int width, int height) {
    std::cout << "FrameBuffer Width: " << width << " FrameBuffer Height: " << height << std::endl;

    framebufferWidth = width;
    framebufferHeight = height;
    glViewport(0, 0, width - gui->GetSidebarWidth(), height);
}

void Renderer::processInput(GLFWwindow *window) const {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    //     camera.ProcessKeyboard(FORWARD, deltaTime);
    // if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    //     camera.ProcessKeyboard(BACKWARD, deltaTime);
    // if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    //     camera.ProcessKeyboard(LEFT, deltaTime);
    // if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    //     camera.ProcessKeyboard(RIGHT, deltaTime);
    // if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    //     camera.ProcessKeyboard(UP, deltaTime);
    // if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    //     camera.ProcessKeyboard(DOWN, deltaTime);
}

void Renderer::onMouseCallback(GLFWwindow *window, double xpos, double ypos) const {
    // if (firstMouse) {
    //     lastX = xpos;
    //     lastY = ypos;
    //     firstMouse = false;
    // }
    //
    // float xoffset = xpos - lastX;
    // float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    //
    // lastX = xpos;
    // lastY = ypos;
    //
    // camera.ProcessMouseMovement(xoffset, yoffset);
}


void Renderer::onScrollCallback(GLFWwindow *window, double xoffset, double yoffset) const {
    // camera.ProcessMouseScroll(yoffset);
}


void Renderer::onWindowFocusChanged(GLFWwindow *window, int focused) const {
    if (focused == GL_FALSE) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

GLFWwindow *Renderer::getWindow() const {
    return window;
}

const char *Renderer::getGLSLVersion() {
    return "#version 150";
}

Renderer::~Renderer() {
    shader->deleteShaderProgram();
    gui.reset();
    glfwDestroyWindow(window);
    glfwTerminate();
}
