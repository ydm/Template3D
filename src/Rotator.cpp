#include "Rotator.hpp"
#include "glm/ext.hpp"


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
