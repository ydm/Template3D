#ifndef __SHADERS_HPP__
#define __SHADERS_HPP__

#include <string>
#include <GL/glew.h>

// Notes:
//   1. Should I use glReleaseShaderCompiler()?


namespace shaders
{

class Program;


class Shader
{
public:
        Shader(const GLenum type, const std::string& source);
        ~Shader();

        bool create();
        bool release();

        // Shader& operator=(const Shader& other) = delete;
        // Shader& operator=(Shader&& other) = delete;

private:
        const GLenum type_;
        const std::string source_;

        GLuint id_;
        Shader *next_; // Linked list of shaders

        friend class Program;
};


class Program
{
public:
        Program();
        ~Program();

        bool create();
        bool release();
        
        bool attachShader(const GLenum type, const std::string& source);
        bool detachShader(const GLuint shader);
        
        bool link();
        bool use() const;
    
        // Attributes and uniforms
        bool umat3(const GLchar *const name, const GLfloat *const M, const GLboolean transpose = GL_FALSE);
        bool umat4(const GLchar *const name, const GLfloat *const M, const GLboolean transpose = GL_FALSE);
	bool uvec2(const GLchar *const name, const GLfloat *const v);
        bool uvec3(const GLchar *const name, const GLfloat *const v);
        bool uvec4(const GLchar *const name, const GLfloat *const v);
	bool ufloat(const GLchar *const name, const GLfloat value);
    
private:
        enum UniformType { MATRIX3, MATRIX4, VECTOR2, VECTOR3, VECTOR4, FLOAT };
        bool setUniform(const GLchar *const name, const GLfloat *u, const enum UniformType t, const GLboolean transpose = GL_FALSE);
        GLint uniformLocation(const GLchar *const name);

        Shader *head_;
        Shader *tail_;
        GLuint id_;
};

} // namespace

#endif // __SHADERS_HPP__
