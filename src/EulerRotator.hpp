#ifndef __T3D_EULER_ROTATOR_HPP__
#define __T3D_EULER_ROTATOR_HPP__

#include "Rotator.hpp"


namespace t3d
{

class EulerRotator : public Rotator
{
public:
	EulerRotator();
	virtual ~EulerRotator();

	bool init() override;
	virtual glm::mat4 rotate() override;
};

} // namespace

#endif // __T3D_EULER_ROTATOR_HPP__
