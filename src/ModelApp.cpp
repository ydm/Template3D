#include "ModelApp.hpp"
#include <iostream>
#include <GLFW/glfw3.h>
#include "glm/ext.hpp"
#include "ModelDrawable.hpp"
#include "TexturedDrawable.hpp"


// ========================
// EulerAnglesApp
// ========================

ModelApp::ModelApp()
: BaseApp()
{
}


ModelApp::~ModelApp()
{
}


bool ModelApp::init()
{
    if (!BaseApp::init())
    {
        return false;
    }

    drawables_.addDrawable(new ModelDrawable("models/glass.obj"));
    // drawables_.addDrawable(new ModelDrawable("models/pumpkin.obj"));
    drawables_.addDrawable(new TexturedDrawable());
    drawables_.setViewMatrix(glm::value_ptr(camera_.getViewMatrix()));
    return true;
}