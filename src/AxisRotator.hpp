#ifndef __AXIS_ROTATOR_HPP__
#define __AXIS_ROTATOR_HPP__

#include "Rotator.hpp"
#include <AntTweakBar.h>


class AxisRotator : public Rotator
{
public:
	AxisRotator();
	virtual ~AxisRotator();

	virtual bool init() override;
	virtual glm::mat4 rotate() override;
};

#endif // __ROTATOR_HPP__