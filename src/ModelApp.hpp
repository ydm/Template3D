#ifndef __T3D_MODEL_APP_HPP__
#define __T3D_MODEL_APP_HPP__

#include "BaseApp.hpp"


namespace t3d
{

class ModelApp : public BaseApp
{
public:
    ModelApp();
    virtual ~ModelApp();

    virtual bool init() override;
};

} // namespace

#endif // __T3D_MODEL_APP_HPP__
