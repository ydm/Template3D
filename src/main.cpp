#include "common.hpp"
#include <iostream>
#include <AntTweakBar.h>


// ========================
// Callbacks
// ========================

namespace
{
    double yCursorPosition = 0.0;


    /**
     *  @param[in] window The window that received the event.
     *  @param[in] codepoint The Unicode code point of the character.
     */
    void charCallback(GLFWwindow *const window, const unsigned int codepoint)
    {
        // std::cout << "char: codepoint=" << codepoint << "\n";
        TwEventCharGLFW(codepoint, GLFW_PRESS);
    }


    /**
     *  @param[in] window The window that received the event.
     *  @param[in] xpos The new x-coordinate, in screen coordinates, of the cursor.
     *  @param[in] ypos The new y-coordinate, in screen coordinates, of the cursor.
     */
    void cursorPositionCallback(GLFWwindow *const window, const double xpos, const double ypos)
    {
        yCursorPosition = ypos;
        TwEventMousePosGLFW(static_cast<int>(xpos), static_cast<int>(ypos));
    }


    void display()
    {
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        TwDraw();
    }


    /**
     *  @param[in] window The window that received the event.
     *  @param[in] key The [keyboard key](@ref keys) that was pressed or released.
     *  @param[in] scancode The system-specific scancode of the key.
     *  @param[in] action `GLFW_PRESS`, `GLFW_RELEASE` or `GLFW_REPEAT`.
     *  @param[in] mods Bit field describing which [modifier keys](@ref mods) were
     *  held down.
     */
    void keyCallback(GLFWwindow *const window, const int key, const int scancode, const int action, const int mods)
    {
        // std::cout << "key: key=" << key << ", action=" << action << "\n";
        TwEventKeyGLFW(key, action);
    }


    /**
     *
     *  @param[in] window The window that received the event.
     *  @param[in] button The [mouse button](@ref buttons) that was pressed or
     *  released.
     *  @param[in] action One of `GLFW_PRESS` or `GLFW_RELEASE`.
     *  @param[in] mods Bit field describing which [modifier keys](@ref mods) were
     *  held down.
     */
    void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
    {
        TwEventMouseButtonGLFW(button, action);
    }


    void resizeCallback(GLFWwindow *const window, const int width, const int height)
    {
        TwWindowSize(width, height);
    }


    /*! @brief The function signature for scroll callbacks.
     *
     *  This is the function signature for scroll callback functions.
     *
     *  @param[in] window The window that received the event.
     *  @param[in] xoffset The scroll offset along the x-axis.
     *  @param[in] yoffset The scroll offset along the y-axis.
     *
     *  @sa glfwSetScrollCallback
     *
     *  @ingroup input
     */
    void scrollCallback(GLFWwindow *const window, const double xoffset, const double yoffset)
    {
        TwEventMouseWheelGLFW(static_cast<int>(yCursorPosition));
    }
}


// ========================
// Main
// ========================

int main(int argc, char *argv[])
{
    static const int WIDTH = 800;
    static const int HEIGHT = 800;
    static const char *TITLE = "Template";
    
    GLFWwindow *window = nullptr;
    TwBar *bar = nullptr;

    // Init GLFW and create the main window
    if (!glfwInit())
    {
        std::cerr << "Error: glfwInit() failed" << std::endl;
        return 1;
    }

    window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Error: glfwCreateWindow() failed" << std::endl;
        return 1;
    }
    glfwMakeContextCurrent(window);

    // Init GLEW
    const GLenum ret = glewInit();
    if (ret != GLEW_OK)
    {
        std::cerr << "Error: " << glewGetErrorString(ret) << std::endl;
    }

    // Init AntTweakBar
    TwInit(TW_OPENGL, nullptr);
    bar = TwNewBar("Settings");
    TwDefine(" GLOBAL help='This example shows how to integrate AntTweakBar with GLFW and OpenGL.' "); // Message added to the help bar.
    double speed = 0.3;
    TwAddVarRW(bar, "speed", TW_TYPE_DOUBLE, &speed, " label='Rot speed' min=0 max=2 step=0.01 keyIncr=s keyDecr=S help='Rotation speed (turns/second)' ");

    // Setup callbacks
    glfwSetCharCallback(window, charCallback);
    glfwSetCursorPosCallback(window, cursorPositionCallback);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetFramebufferSizeCallback(window, resizeCallback);
    glfwSetScrollCallback(window, scrollCallback);

    // Call the resize callback function initially.
    do
    {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        resizeCallback(window, width, height);
    }
    while (0);
    
    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        display();
        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    // Exit
    glfwTerminate();
	return 0;
}
