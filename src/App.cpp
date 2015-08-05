#include "App.hpp"
#include <iostream>


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
: speed_(0.0)
, twbar_(nullptr)
, vao_(0)
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
    glBindVertexArray(vao_);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}
