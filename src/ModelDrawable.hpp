#ifndef __MODEL_DRAWABLE_HPP__
#define __MODEL_DRAWABLE_HPP__

#include <string>
#include <assimp/scene.h>
#include "Drawable.hpp"


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

#endif // __MODEL_DRAWABLE_HPP__
