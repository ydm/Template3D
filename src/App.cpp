#include "App.hpp"
#include <iostream>


// ========================
// App
// ========================

App::App()
: speed_(0.0)
, twbar_(nullptr)
{
}


App::~App()
{
}


bool App::init()
{
    twbar_ = TwNewBar("Settings");
    TwDefine(" GLOBAL help='This example shows how to integrate AntTweakBar with GLFW and OpenGL.' "); // Message added to the help bar.
    TwAddVarRW(twbar_, "speed", TW_TYPE_DOUBLE, &speed_, " label='Rot speed' min=0 max=2 step=0.01 keyIncr=s keyDecr=S help='Rotation speed (turns/second)' ");
    return true;
}


void App::terminate()
{
}


// ========================
// Callbacks
// ========================

void App::onChar(const unsigned int codepoint)
{
}


void App::onCursorPosition(const double xpos, const double ypos)
{
}


void App::onKey(const int key, const int scancode, const int action, const int mods)
{
}


void App::onMouseButton(int button, int action, int mods)
{
}


void App::onResize(const int width, const int height)
{
}


void App::onScroll(const double xoffset, const double yoffset)
{
}


// ========================
// Draw routine
// ========================

void App::draw()
{
}
