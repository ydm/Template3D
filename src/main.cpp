#include "default.hpp"
#include <chrono>
#include <AntTweakBar.h>


// ========================
// Callbacks
// ========================

namespace
{

// ModelApp gApplication;
double gCursorPositionY = 0.0;


/**
 *  @param[in] window The window that received the event.
 *  @param[in] codepoint The Unicode code point of the character.
 */
void charCallback(GLFWwindow *const window, const unsigned int codepoint)
{
    if (!TwEventCharGLFW(codepoint, GLFW_PRESS))
    {
        // gApplication.onChar(codepoint);
    }
}


/**
 *  @param[in] window The window that received the event.
 *  @param[in] xpos The new x-coordinate, in screen coordinates, of the cursor.
 *  @param[in] ypos The new y-coordinate, in screen coordinates, of the cursor.
 */
void cursorPositionCallback(GLFWwindow *const window,
                            const double xpos, const double ypos)
{
    gCursorPositionY = ypos;
    if (!TwEventMousePosGLFW(static_cast<int>(xpos), static_cast<int>(ypos)))
    {
        // gApplication.onCursorPosition(xpos, ypos);
    }
}


void display(GLFWwindow *const window)
{
    glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    TwDraw();
    // if (updated)
    // {
    // gApplication.draw();
    // }
    glfwSwapBuffers(window);
}


bool initOpenGL()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    return glGetError() == GL_NO_ERROR;
}


/**
 *  @param[in] window The window that received the event.
 *  @param[in] key The [keyboard key](@ref keys) that was pressed or released.
 *  @param[in] scancode The system-specific scancode of the key.
 *  @param[in] action `GLFW_PRESS`, `GLFW_RELEASE` or `GLFW_REPEAT`.
 *  @param[in] mods Bit field describing which [modifier keys](@ref mods) were
 *  held down.
 */
void keyCallback(GLFWwindow *const window, const int key,
                 const int scancode, const int action, const int mods)
{
    if (TwEventKeyGLFW(key, action) == 0)
    {
        // gApplication.onKey(key, scancode, action, mods);
    }
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
        // gApplication.onMouseButton(button, action, mods);
    }
}


void resizeCallback(GLFWwindow *const window, const int width, const int height)
{
    glViewport(0, 0, width, height);
    TwWindowSize(width, height);
    // gApplication.onResize(width, height);
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
void scrollCallback(GLFWwindow *const window,
                    const double xoffset, const double yoffset)
{
    if (!TwEventMouseWheelGLFW(static_cast<int>(gCursorPositionY)))
    {
        // gApplication.onScroll(xoffset, yoffset);
    }
}

} // namespace


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
    namespace log = t3d::log;

    static const char *const TITLE  = "Template";
    static const int         WIDTH  = 800;
    static const int         HEIGHT = 800;

    GLFWwindow *window = nullptr;
    GLenum ret;
    std::chrono::system_clock::time_point lastUpdate;


    // 1. Init GLFW
    // ============
    if (!glfwInit())
    {
        log::e << "Error: glfwInit() failed" << log::endl;
        return 0;
    }


    // 2. Create window
    // ================
    window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, nullptr, nullptr);
    if (!window)
    {
        log::e << "Error: glfwCreateWindow() failed" << log::endl;
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


    // 3. Init GLEW and OpenGL
    // =======================
    ret = glewInit();
    if (ret != GLEW_OK)
    {
        log::e << "Error: " << glewGetErrorString(ret) << log::endl;
        goto termWin;
    }
    if (!initOpenGL())
    {
        log::e << "Error: initOpenGL() failed" << log::endl;
        return 0;
    }
    // Print OpenGL versions
    log::v << "OpenGL " << glGetString(GL_VERSION) << log::endl;
    log::v << "GLSL "<< glGetString(GL_SHADING_LANGUAGE_VERSION) << log::endl;


    // 4. Init AntTweakBar
    // ===================
    if (!TwInit(TW_OPENGL, nullptr))
    {
        log::e << "Error: TwInit() failed" << log::endl;
        goto termWin;
    }


    // 5. Initialize main application object and resize initially
    // ==========================================================
    // if (!gApplication.init())
    // {
    //     log::e << "Error: Application failed to initialize" << log::endl;
    //     goto termTw;
    // }

    do
    {
        int width = WIDTH, height = HEIGHT;
        glfwGetFramebufferSize(window, &width, &height);
        resizeCallback(window, width, height);
    }
    while (0);


    // Main loop
    // =========

    // Draw initially
    lastUpdate = std::chrono::system_clock::now();
    // gApplication.update(0.0f);
    display(window);

    // Loop
    while (!glfwWindowShouldClose(window))
    {
        // Invoke registered event callbacks.
        glfwPollEvents();

        // Update the application state.
        const auto now = std::chrono::system_clock::now();
        const std::chrono::duration<float> dt = now - lastUpdate;
        /* const bool updated = */
        // gApplication.update(dt.count());
        lastUpdate = now;

        // Draw
        display(window);
    }


    // Exit sequence
    // =============

    // 5. Terminate application
    // gApplication.terminate();

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
