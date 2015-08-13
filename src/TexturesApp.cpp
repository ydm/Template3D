#include "TexturesApp.hpp"
#include <iostream>
#include <GLFW/glfw3.h>
#include "glm/ext.hpp"
#include "TexturedDrawable.hpp"


// ========================
// EulerAnglesApp
// ========================

TexturesApp::TexturesApp()
: BaseApp()
{
}


TexturesApp::~TexturesApp()
{
}


bool TexturesApp::init()
{
    if (!BaseApp::init())
    {
        return false;
    }

    drawables_.addDrawable(new TexturedDrawable());
    drawables_.setViewMatrix(glm::value_ptr(camera_.getViewMatrix()));
    return true;
}
