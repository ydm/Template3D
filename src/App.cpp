#include "App.hpp"
#include <iostream>
#include <GLFW/glfw3.h>
#include "glm/ext.hpp"
#include "AxisRotator.hpp"
#include "EulerRotator.hpp"
#include "TripodDrawable.hpp"


// ========================
// App
// ========================

App::App()
: camera_()
, drawables_()
{
}


App::~App()
{
}


bool App::init()
{
    // Setup camera
    camera_.setPosition(glm::vec3(0.0f, 0.0f, 5.0f));

    // Init tripods
    drawables_.init();

    {
        // Euler rotation: black tripod
        TripodDrawable *const b = new TripodDrawable();
        drawables_.addDrawable(b);
        b->setColors(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
        b->setPosition(glm::vec3(-1.5f, 0.0f, 0.0f));

        // Euler rotation: colored tripod
        TripodDrawable *const d = new TripodDrawable(new EulerRotator());
        drawables_.addDrawable(d);
        d->setPosition(glm::vec3(-1.5f, 0.0f, 0.0f));
    }

    {
        // Axis rotation: black tripod
        TripodDrawable *const b = new TripodDrawable();
        drawables_.addDrawable(b);
        b->setColors(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
        b->setPosition(glm::vec3(1.5f, 0.0f, 0.0f));

        // Axis rotation: colored tripod
        TripodDrawable *const d = new TripodDrawable(new AxisRotator());
        drawables_.addDrawable(d);
        d->setPosition(glm::vec3(1.5f, 0.0f, 0.0f));
    }
    
    drawables_.setViewMatrix(glm::value_ptr(camera_.getViewMatrix()));

    return true;
}


void App::terminate()
{
    drawables_.terminate();
}


bool App::update(const float dt)
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
    drawables_.setProjectionMatrix(glm::value_ptr(camera_.getProjectionMatrix()));
}


void App::onScroll(const double xoffset, const double yoffset)
{
}


// ========================
// Draw routine
// ========================

void App::draw()
{
    drawables_.draw();
}
