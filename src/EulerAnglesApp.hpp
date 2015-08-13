#ifndef __EULER_APP_HPP__
#define __EULER_APP_HPP__

#include "BaseApp.hpp"
#include <AntTweakBar.h>
#include "Camera.hpp"
#include "DrawableManager.hpp"


class EulerAnglesApp : public BaseApp
{
public:
    EulerAnglesApp();
    virtual ~EulerAnglesApp();

    virtual bool init() override;
};

#endif // __EULER_APP_HPP__
