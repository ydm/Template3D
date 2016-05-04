#include "EmbreeApp.hpp"
#include "../ModelDrawable.hpp"
#include "../TripodDrawable.hpp"


namespace t3d
{

EmbreeApp::EmbreeApp()
: BaseApp()
{
}


EmbreeApp::~EmbreeApp()
{
}


bool EmbreeApp::init()
{
    if (!BaseApp::init())
    {
        return false;
    }

    drawables_.addDrawable(new ModelDrawable("models/sphere.obj"));
    drawables_.addDrawable(new TripodDrawable(2.0f));
    return BaseApp::postInit();
}

void EmbreeApp::onCursorPosition(const double x, const double y)
{
    BaseApp::onCursorPosition(x, y);
    const glm::vec3& mouseRay = camera_.getMouseRay(x, y);
    const glm::vec4& pos = camera_.getPosition();

    log::v << "mouseRay=[" << glm::to_string(pos) << ", "
           << glm::to_string(mouseRay) << log::endl;
}

} // namespace
