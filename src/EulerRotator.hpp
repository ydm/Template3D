#ifndef __EULER_ROTATOR_HPP__
#define __EULER_ROTATOR_HPP__

#include "Rotator.hpp"
#include <AntTweakBar.h>


class EulerRotator : public Rotator
{
public:
	EulerRotator();
	virtual ~EulerRotator();

	bool init() override;
	virtual glm::mat4 rotate() override;
};

#endif // __EULER_ROTATOR_HPP__