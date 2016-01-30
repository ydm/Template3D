#include "EmbreeApp.hpp"
#include "../ModelDrawable.hpp"
#include "../Tri


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
    return BaseApp::postInit();
}

} // namespace
