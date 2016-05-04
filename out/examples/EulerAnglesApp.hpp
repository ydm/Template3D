#ifndef __T3D_EULER_APP_HPP__
#define __T3D_EULER_APP_HPP__

#include "BaseApp.hpp"


namespace t3d
{

class EulerAnglesApp : public BaseApp
{
public:
    EulerAnglesApp();
    virtual ~EulerAnglesApp();

    virtual bool init() override;
};

} // namespace

#endif // __T3D_EULER_APP_HPP__
