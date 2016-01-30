#ifndef __T3D_EMBREE_APP_HPP__
#define __T3D_EMBREE_APP_HPP__

#include "../BaseApp.hpp"


namespace t3d
{

class EmbreeApp : public BaseApp
{
public:
    EmbreeApp();
    virtual ~EmbreeApp();
    virtual bool init() override;
    virtual void onCursorPosition(const double x, const double y) override;
};

} // namespace

#endif // __T3D_EMBREE_APP_HPP__
