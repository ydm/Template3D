#include "TexturedDrawable.hpp"
#include "glm/ext.hpp"


namespace
{
	const GLfloat points[] = {
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f
	};

	const GLfloat colors[] = {
		1.0f, 0.5f, 0.5f,
		0.5f, 1.0f, 0.5f,
		0.5f, 0.5f, 1.0f,
		1.0f, 1.0f, 1.0f,
	};
}


TexturedDrawable::TexturedDrawable()
: Drawable()
, vao_(0)
, M_(1.0f)
{
    vbo_[0] = 0;
    vbo_[1] = 0;
}


TexturedDrawable::~TexturedDrawable()
{
}


bool TexturedDrawable::init()
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

    // Read and apply texture
    reader_.read("textures/wood.bmp");
    GLuint texid;
    glGenTextures(1, &texid);
    glBindTexture(GL_TEXTURE_2D, texid);
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGB,
                 reader_.width,
                 reader_.height,
                 0,
                 GL_BGR,
                 GL_UNSIGNED_BYTE,
                 reader_.data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
    return true;
}


void TexturedDrawable::terminate()
{
    // TODO: Term vao
}


bool TexturedDrawable::update(const float dt)
{
    return false;
}


void TexturedDrawable::setPosition(const glm::vec3& pos)
{
    M_[3] = glm::vec4(pos, 1.0f);
    setModelMatrix(glm::value_ptr(M_));
}


bool TexturedDrawable::addShaders()
{
    return addShader(GL_VERTEX_SHADER, "shaders/Textures.vert") && addShader(GL_FRAGMENT_SHADER, "shaders/Textures.frag");
}


void TexturedDrawable::drawWithShader()
{
    glBindVertexArray(vao_);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);
    glBindVertexArray(0);
}
