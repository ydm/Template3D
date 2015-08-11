#include <chrono>
#include <iostream>
#include <thread>
#include <AntTweakBar.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "App.hpp"


// ========================
// Callbacks
// ========================

namespace
{
    App gApplication;
    double gCursorPositionY = 0.0;


    /**
     *  @param[in] window The window that received the event.
     *  @param[in] codepoint The Unicode code point of the character.
     */
    void charCallback(GLFWwindow *const window, const unsigned int codepoint)
    {
        if (!TwEventCharGLFW(codepoint, GLFW_PRESS))
        {
            gApplication.onChar(codepoint);
        }
    }


    /**
     *  @param[in] window The window that received the event.
     *  @param[in] xpos The new x-coordinate, in screen coordinates, of the cursor.
     *  @param[in] ypos The new y-coordinate, in screen coordinates, of the cursor.
     */
    void cursorPositionCallback(GLFWwindow *const window, const double xpos, const double ypos)
    {
        gCursorPositionY = ypos;
        if (!TwEventMousePosGLFW(static_cast<int>(xpos), static_cast<int>(ypos)))
        {
            gApplication.onCursorPosition(xpos, ypos);
        }
    }


    void display()
    {
        glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        TwDraw();
        gApplication.draw();
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
        // ydm: XXX There's a bug here: TwEventKey always returns 0.
        gApplication.onKey(key, scancode, action, mods);
        //if (!TwEventKeyGLFW(key, action))
        //{
        //    gApplication.onKey(key, scancode, action, mods);
        //}
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
        if (!TwEventMouseButtonGLFW(button, action))
        {
            gApplication.onMouseButton(button, action, mods);
        }
    }


    void resizeCallback(GLFWwindow *const window, const int width, const int height)
    {
        glViewport(0, 0, width, height);
        TwWindowSize(width, height);
        gApplication.onResize(width, height);
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
        if (!TwEventMouseWheelGLFW(static_cast<int>(gCursorPositionY)))
        {
            gApplication.onScroll(xoffset, yoffset);
        }
    }
}


// ========================
// Main
// ========================

// Init stack:
// 1. GLFW
// 2. Window
// 3. GLEW
// 4. AntTweakBar
// 5. Application
int main(int argc, char *argv[])
{
    static const char *TITLE = "Template";
    static const int WIDTH = 800;
    static const int HEIGHT = 800;

    static const int FPS = 60;
    static const std::chrono::nanoseconds STEPN(1000000000 / FPS);
    static const float STEPF = std::chrono::duration_cast<std::chrono::duration<float> >(STEPN).count();

    GLFWwindow *window = nullptr;


    // 1. Init GLFW
    // ============
    if (!glfwInit())
    {
        std::cerr << "Error: glfwInit() failed" << std::endl;
        return 0;
    }


    // 2. Create window
    // ================
    window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Error: glfwCreateWindow() failed" << std::endl;
        goto termGlfw;
    }
    
    // Set as default OpenGL context
    glfwMakeContextCurrent(window);

    // Setup callbacks
    glfwSetCharCallback(window, charCallback);
    glfwSetCursorPosCallback(window, cursorPositionCallback);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetFramebufferSizeCallback(window, resizeCallback);
    glfwSetScrollCallback(window, scrollCallback);


    // 3. Init GLEW
    // ============
    const GLenum ret = glewInit();
    if (ret != GLEW_OK)
    {
        std::cerr << "Error: " << glewGetErrorString(ret) << std::endl;
        goto termWin;
    }


    // 4. Init AntTweakBar
    // ===================
    if (!TwInit(TW_OPENGL, nullptr))
    {
        std::cerr << "Error: TwInit() failed" << std::endl;
        goto termWin;
    }


    // 5. Initialize main application object and resize initially
    // ==========================================================
    if (!gApplication.init())
    {
        std::cerr << "Error: Application failed to initialize" << std::endl;
        goto termTw;
    }

    do
    {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        resizeCallback(window, width, height);
    }
    while (0);


    // Main loop
    // =========
    
    // Draw initially
    display();
    glfwSwapBuffers(window);

    // Loop
    while (!glfwWindowShouldClose(window))
    {
        const std::chrono::system_clock::time_point begin = std::chrono::system_clock::now();

        // Invoke registered event callbacks.
        glfwPollEvents();

        // Update the application state.
        gApplication.update(STEPF); // XXX: Fixed step is OK for now.

        display();
        glfwSwapBuffers(window);

        // There's a fixed FPS count, so here we sleep for the time remaining for this frame.
        const std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
        const auto elapsed = end - begin;
        if (STEPN > elapsed)
        {
            const auto dur = STEPN - elapsed;
            std::this_thread::sleep_for(dur);
        }
    }


    // Exit sequence
    // =============

    // 5. Terminate application
    gApplication.terminate();

    // 4. Terminate ATB
termTw:
    TwTerminate();

    // 3. Terminate GLEW

    // 2. Terminate Window
termWin:
    glfwDestroyWindow(window);

    // 1. Terminate glfw
termGlfw:
    glfwTerminate();

	return 0;
}
