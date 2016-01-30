#include "MandelbrotDrawable.hpp"


namespace
{

const GLfloat width = 2.0f;
const GLfloat height = 1.0f;

const GLfloat w2 = width / 2.0f;
const GLfloat h2 = height / 2.0f;

const GLfloat points[] = {
    -w2, -h2, 0.0f,
     w2, -h2, 0.0f,
    -w2,  h2, 0.0f,
     w2,  h2, 0.0f
};

const GLfloat colors[] = {
    1.0f, 0.5f, 0.5f,
    0.5f, 1.0f, 0.5f,
    0.5f, 0.5f, 1.0f,
    1.0f, 1.0f, 1.0f,
};

}


namespace t3d
{

MandelbrotDrawable::MandelbrotDrawable()
: Drawable()
, vao_(0)
, M_(1.0f)
{
    vbo_[0] = 0;
    vbo_[1] = 0;
}


MandelbrotDrawable::~MandelbrotDrawable()
{
}


bool MandelbrotDrawable::init()
{
    if (!Drawable::init())
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
            glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), points, GL_STATIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
            glEnableVertexArrayAttrib(vao_, 0);
        }
        glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Location 1: Vertex color
	glBindBuffer(GL_ARRAY_BUFFER, vbo_[1]);
	{
            glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), colors, GL_STATIC_DRAW);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
            glEnableVertexArrayAttrib(vao_, 1);
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    glBindVertexArray(0);

    return true;
}


void MandelbrotDrawable::terminate()
{
    // TODO: Term vao
}


bool MandelbrotDrawable::update(const float dt)
{
    return false;
}


void MandelbrotDrawable::setPosition(const glm::vec3& pos)
{
    M_[3] = glm::vec4(pos, 1.0f);
    setModelMatrix(glm::value_ptr(M_));
}


bool MandelbrotDrawable::addShaders()
{
    return addShader(GL_VERTEX_SHADER, "shaders/Mandelbrot.vert")
        && addShader(GL_FRAGMENT_SHADER, "shaders/Mandelbrot.frag");
}


void MandelbrotDrawable::drawWithShader()
{
    glBindVertexArray(vao_);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);
    glBindVertexArray(0);
}

} // namespace
