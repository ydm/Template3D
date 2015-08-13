#ifndef __TEXTURES_APP_HPP__
#define __TEXTURES_APP_HPP__

#include "BaseApp.hpp"
#include <AntTweakBar.h>
#include "Camera.hpp"
#include "DrawableManager.hpp"


class TexturesApp : public BaseApp
{
public:
    TexturesApp();
    virtual ~TexturesApp();

    virtual bool init() override;
};

#endif // __TEXTURES_APP_HPP__
