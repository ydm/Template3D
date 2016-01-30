#include "TexturesApp.hpp"
#include "TexturedDrawable.hpp"


// ========================
// EulerAnglesApp
// ========================

namespace t3d
{

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

} // namespace
