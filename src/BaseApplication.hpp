#ifndef __BASEAPPLICATION_HPP__
#define __BASEAPPLICATION_HPP__

namespace t3d
{

class BaseApplication
{
public:
    BaseApplication() = default;
    virtual BaseApplication() = default;

    // Children are expected to provide:
    // init()
    // terminate()
    // update(float)

private:
};
  
}  // namespace

#endif  // __BASEAPPLICATION_HPP__
