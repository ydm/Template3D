#include "EulerAnglesApp.hpp"
#include "AxisRotator.hpp"
#include "EulerRotator.hpp"
#include "TripodDrawable.hpp"


namespace t3d
{

// ========================
// EulerAnglesApp
// ========================

EulerAnglesApp::EulerAnglesApp()
: BaseApp()
{
}


EulerAnglesApp::~EulerAnglesApp()
{
}


bool EulerAnglesApp::init()
{
    if (!BaseApp::init())
    {
        return false;
    }

    {
        // Euler rotation: black tripod
        TripodDrawable *const b = new TripodDrawable();
        drawables_.addDrawable(b);
        b->setColors(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
        b->setPosition(glm::vec3(-1.5f, 0.0f, 0.0f));

        // Euler rotation: colored tripod
        TripodDrawable *const d = new TripodDrawable(1.0f, new EulerRotator());
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
        TripodDrawable *const d = new TripodDrawable(1.0f, new AxisRotator());
        drawables_.addDrawable(d);
        d->setPosition(glm::vec3(1.5f, 0.0f, 0.0f));
    }

    drawables_.setViewMatrix(glm::value_ptr(camera_.getViewMatrix()));

    return true;
}

} // namespace
