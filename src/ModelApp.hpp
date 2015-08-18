#ifndef __MODEL_APP_HPP__
#define __MODEL_APP_HPP__

#include "BaseApp.hpp"
#include <AntTweakBar.h>
#include "Camera.hpp"
#include "DrawableManager.hpp"


class ModelApp : public BaseApp
{
public:
    ModelApp();
    virtual ~ModelApp();

    virtual bool init() override;
};

#endif // __MODEL_APP_HPP__
