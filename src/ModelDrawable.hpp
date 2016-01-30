#ifndef __T3D_MODEL_DRAWABLE_HPP__
#define __T3D_MODEL_DRAWABLE_HPP__

#include "Drawable.hpp"
#include <assimp/scene.h>


namespace t3d
{

class ModelDrawable : public Drawable
{
public:
	ModelDrawable(const std::string& filename);
	virtual ~ModelDrawable();

	virtual bool init() override;
	virtual void terminate() override;

	virtual bool update(const float dt) override;

protected:
	virtual bool addShaders() override;
	virtual void drawWithShader() override;

private:
	std::string filename_;
	const aiScene *scene_;
	GLuint vao_;
	GLuint vbo_[3];
};

} // namespace

#endif // __T3D_MODEL_DRAWABLE_HPP__
