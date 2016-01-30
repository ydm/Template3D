#ifndef __TEXTURES_APP_HPP__
#define __TEXTURES_APP_HPP__

#include "BaseApp.hpp"
// #include <AntTweakBar.h>
// #include "Camera.hpp"
// #include "DrawableManager.hpp"


namespace t3d
{

class TexturesApp : public BaseApp
{
public:
    TexturesApp();
    virtual ~TexturesApp();

    virtual bool init() override;
};

} // namespace

#endif // __TEXTURES_APP_HPP__
