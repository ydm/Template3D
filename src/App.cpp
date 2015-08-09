#include "App.hpp"
#include <iostream>
#include <GLFW/glfw3.h>
#include "glm/ext.hpp"


namespace
{
    GLfloat points[] = {
        0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f
    };
}


// ========================
// App
// ========================

App::App()
: camera_()
, program_()
, speed_(0.0)
, twbar_(nullptr)
, vao_(0)
{
}


App::~App()
{
}


bool App::init()
{
    // Setup shader program
    if (!program_.create())
    {
        return false;
    }
    program_.attachShader(GL_VERTEX_SHADER, "shaders/Standard.vert");
    program_.attachShader(GL_FRAGMENT_SHADER, "shaders/Standard.frag");
    if (program_.link())
    {
        std::cout << "[I] App: Program linked!" << std::endl;
    }
    else
    {
        return false;
    }

    // Setup camera
    camera_.setPosition(glm::vec3(0.5f, 0.0f, 0.0f));
    program_.umat4("u_viewMatrix", glm::value_ptr(camera_.getViewMatrix()));

    // Setup tweak bar
    twbar_ = TwNewBar("Settings");
    TwDefine(" GLOBAL help='This example shows how to integrate AntTweakBar with GLFW and OpenGL.' "); // Message added to the help bar.
    // TwAddVarRW(twbar_, "speed", TW_TYPE_DOUBLE, &speed_, " label='Rot speed' min=0 max=2 step=0.01 keyIncr=s keyDecr=S help='Rotation speed (turns/second)' ");

    // Setup drawable(s)
    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);
    {
        GLuint buf;
        glGenBuffers(1, &buf);
        glBindBuffer(GL_ARRAY_BUFFER, buf);
        {
            glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), points, GL_STATIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
            glEnableVertexArrayAttrib(vao_, 0);
        }
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    glBindVertexArray(0);

    return true;
}


void App::terminate()
{
    // TODO delete vaos

    TwDeleteBar(twbar_);
    twbar_ = nullptr;

    program_.release();
}


bool App::update(const float dt)
{
    if (camera_.update(dt))
    {
        program_.umat4("u_viewMatrix", glm::value_ptr(camera_.getViewMatrix()));
        return true;
    }
    return false;
}


// ========================
// Callbacks
// ========================

void App::onChar(const unsigned int codepoint)
{
}


void App::onCursorPosition(const double xpos, const double ypos)
{
    camera_.mouseMotion(static_cast<int>(xpos), static_cast<int>(ypos));
}


void App::onKey(const int key, const int scancode, const int action, const int mods)
{
    Camera::Direction dir;

    switch (key)
    {
        case GLFW_KEY_W:            dir = Camera::FORWARD;  break;
        case GLFW_KEY_A:            dir = Camera::LEFT;     break;
        case GLFW_KEY_S:            dir = Camera::BACKWARD; break;
        case GLFW_KEY_D:            dir = Camera::RIGHT;    break;
        case GLFW_KEY_LEFT_CONTROL: dir = Camera::DOWN;     break;
        case GLFW_KEY_SPACE:        dir = Camera::UP;       break;
        default: return;
    }

    if (action)
    {
        camera_.walk(dir);
    }
    else
    {
        camera_.stopWalking(dir);
    }
}


void App::onMouseButton(int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_RIGHT)
    {
        if (action == GLFW_PRESS)
        {
            camera_.enableMouse();
        }
        else
        {
            camera_.disableMouse();
        }
    }
}


void App::onResize(const int width, const int height)
{
    camera_.setViewportSize(width, height);
    program_.umat4("u_projectionMatrix", glm::value_ptr(camera_.getProjectionMatrix()));
}


void App::onScroll(const double xoffset, const double yoffset)
{
}


// ========================
// Draw routine
// ========================

void App::draw()
{
    program_.use();

    glBindVertexArray(vao_);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}
