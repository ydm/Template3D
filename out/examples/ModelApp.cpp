#include "ModelApp.hpp"
#include "ModelDrawable.hpp"
#include "TripodDrawable.hpp"


namespace t3d
{

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

    drawables_.addDrawable(new TripodDrawable(20.0f));
    // drawables_.addDrawable(new ModelDrawable("models/glass.obj"));
    drawables_.addDrawable(new ModelDrawable("models/pumpkin.obj"));
    drawables_.setViewMatrix(glm::value_ptr(camera_.getViewMatrix()));
    return true;
}

} // namespace t3d
