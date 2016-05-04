#include "BaseApp.hpp"
#include <AntTweakBar.h>


namespace t3d
{

// ========================
// BaseApp
// ========================

BaseApp::BaseApp()
: camera_()
, drawables_()
{
}


BaseApp::~BaseApp()
{
}


bool BaseApp::init()
{
    // Setup camera
    camera_.setPosition(glm::vec3(0.0f, 0.0f, 5.0f));
    return drawables_.init();
}


void BaseApp::terminate()
{
    drawables_.terminate();
}


bool BaseApp::update(const float dt)
{
    const bool c = camera_.update(dt);
    const bool d = drawables_.update(dt);
    if (c)
    {
        drawables_.setViewMatrix(glm::value_ptr(camera_.getViewMatrix()));
        return true;
    }
    return d;
}


// ========================
// Callbacks
// ========================

void BaseApp::onChar(const unsigned int codepoint)
{
}


void BaseApp::onCursorPosition(const double xpos, const double ypos)
{
    camera_.mouseMotion(static_cast<int>(xpos), static_cast<int>(ypos));
}


void BaseApp::onKey(const int key, const int scancode, const int action, const int mods)
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


void BaseApp::onMouseButton(int button, int action, int mods)
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


void BaseApp::onResize(const int width, const int height)
{
    camera_.setViewportSize(width, height);
    drawables_.setProjectionMatrix(glm::value_ptr(camera_.getProjectionMatrix()));
}


void BaseApp::onScroll(const double xoffset, const double yoffset)
{
}


// ========================
// Draw routine
// ========================

void BaseApp::draw()
{
    drawables_.draw();
}


// ========================
// Protected
// ========================

bool BaseApp::postInit()
{
    drawables_.setViewMatrix(glm::value_ptr(camera_.getViewMatrix()));
    return true;
}

} // namespace
