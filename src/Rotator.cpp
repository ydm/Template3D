#include "Rotator.hpp"


namespace t3d
{

Rotator::Rotator()
: angles_(0.0f)
, bar_(nullptr)
{
}


Rotator::~Rotator()
{
}


bool Rotator::init()
{
    return true;
}


void Rotator::terminate()
{
    if (bar_)
    {
        TwDeleteBar(bar_);
    }
}

} // namespace
