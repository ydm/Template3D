#include "TripodDrawable.hpp"
#include "glm/ext.hpp"
#include <iostream>


namespace
{
	const GLfloat tripodPoints[] = {
		// X
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,

		// Y
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,

		// Z
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
	};

	const GLfloat tripodColors[] = {
		// X
		1.0f, 0.5f, 0.5f,
		1.0f, 0.5f, 0.5f,

		// Y
		0.5f, 1.0f, 0.5f,
		0.5f, 1.0f, 0.5f,

		// Z
		0.5f, 0.5f, 1.0f,
		0.5f, 0.5f, 1.0f,
	};
}


TripodDrawable::TripodDrawable(const float scale, Rotator *const rotator)
: Drawable()
, rotator_(rotator)
, scale_(scale)
, vao_(0)
, M_(1.0f)
{
    M_[0][0] = M_[1][1] = M_[2][2] = scale;
    vbo_[0] = 0;
    vbo_[1] = 0;
}


TripodDrawable::~TripodDrawable()
{
	delete rotator_;
}


bool TripodDrawable::init()
{
    if (!Drawable::init())
    {
	    return false;
    }

    if (rotator_ != nullptr && !rotator_->init())
    {
        return false;
    }

    // Setup drawable(s)
    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);
    {
        glGenBuffers(2, vbo_);
        
	// Location 0 --> vertex position
	glBindBuffer(GL_ARRAY_BUFFER, vbo_[0]);
        {
            glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), tripodPoints, GL_STATIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
            glEnableVertexArrayAttrib(vao_, 0);
        }
        glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Location 1: Vertex color
	glBindBuffer(GL_ARRAY_BUFFER, vbo_[1]);
	{
		glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), tripodColors, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
		glEnableVertexArrayAttrib(vao_, 1);
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    glBindVertexArray(0);

    // Setup model matrix initially
    // setModelMatrix(glm::value_ptr(M_ * glm::scale(glm::vec3(scale_))));
    setModelMatrix(glm::value_ptr(M_));
    return true;
}


void TripodDrawable::terminate()
{
    if (rotator_ != nullptr)
    {
        rotator_->terminate();
    }
    // TODO: Term vao
    Drawable::terminate();
}


bool TripodDrawable::update(const float dt)
{
    // TODO
    if (rotator_ == nullptr)
    {
        return false;
    }

    const glm::mat4 R = rotator_->rotate();
    for (int i = 0; i < 3; i++)
    {
	// Change in position
        if (M_[i] != R[i]) 
        {
            // Save position
            const glm::vec4 t(M_[3]);
            M_ = R * scale_;
            M_[3] = t;
            // Update uniform model matrix
            setModelMatrix(glm::value_ptr(M_));
            // Notify of change
	    return true;
        }
    }
    return false;
}


void TripodDrawable::setColors(float xr, float xg, float xb,
                               float yr, float yg, float yb,
                               float zr, float zg, float zb)
{
    glBindBuffer(GL_ARRAY_BUFFER, vbo_[1]);
    const GLfloat ary[18] = {
        xr, xg, xb, xr, xg, xb,
        yr, yg, yb, yr, yg, yb,
        zr, zg, zb, zr, zg, zb,
    };
    glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), ary, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void TripodDrawable::setPosition(const glm::vec3& pos)
{
    M_[3] = glm::vec4(pos, 1.0f);
    setModelMatrix(glm::value_ptr(M_));
}


bool TripodDrawable::addShaders()
{
    return addShader(GL_VERTEX_SHADER, "shaders/Standard.vert") && addShader(GL_FRAGMENT_SHADER, "shaders/Standard.frag");
}


void TripodDrawable::drawWithShader()
{
    glBindVertexArray(vao_);
    // glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glDrawArrays(GL_LINES, 0, 6);
    glBindVertexArray(0);
}
