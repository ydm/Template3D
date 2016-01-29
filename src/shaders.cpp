#include "shaders.hpp"
#include <iostream>
#include <sstream>
#include <utils/file.hpp>


namespace
{

// ========================
// Helpers
// ========================

std::string infoLog(const GLuint id)
{
        GLint len;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);

        GLchar *log = new GLchar[len + 1];
        glGetShaderInfoLog(id, len, nullptr, log);

        std::stringstream logStream;
        logStream << log;
        delete [] log;

        return logStream.str();
}

} //namespace


namespace shaders
{

// ========================
// Shader
// ========================

Shader::Shader(const GLenum type, const std::string& source)
: type_(type)
, source_(source)
, id_(0)
, next_(nullptr)
{
}


Shader::~Shader()
{
}

    
bool Shader::create()
{
        GLenum err = GL_NO_ERROR;

        // Crerate shader object.
        id_ = glCreateShader(type_);
        if (id_ == 0)
        {
		std::cerr << "[E] Shader::create: glCreateShader: Error while creating shader object." << std::endl;
		return false;
        }
        
        err = glGetError();
        if (err != GL_NO_ERROR)
        {
		switch (err)
		{
		case GL_INVALID_ENUM: std::cerr << "[E] Shader::create: glCreateShader: `type` is not an accepted value." << std::endl; break;
		}
		return false;
        }

        // Assign source.
        const std::string& src = utils::file::read(source_);
        if (src.length() == 0)
        {
		std::cerr << "[E] Shader::create: Error while reading file '" << source_ << "'." << std::endl;
		release();
		return false;
        }
        const char *ary[1] = { src.c_str() };
        glShaderSource(id_, 1, ary, NULL);

        // Check for errors.
        err = glGetError();
        if (err != GL_NO_ERROR)
        {
		switch (err)
		{
		case GL_INVALID_VALUE: std::cerr << "[E] Shader::create: glShaderSource: `shader` is not a value generated by OpenGL." << std::endl; break;
		case GL_INVALID_OPERATION: std::cerr << "[E] Shader::create: glShaderSource: `shader` is not a shader object." << std::endl; break;
		}
		release();
		return false;
        }

        // Check if shader compilation is supported.
        GLboolean supported = GL_FALSE;
        glGetBooleanv(GL_SHADER_COMPILER, &supported);
        if (supported == GL_FALSE)
        {
		std::cout << "[I] Shader: Compilation is not supported." << std::endl;
		return true;
        }

        // Compile shader.
        glCompileShader(id_);

        // Check status.
        GLint status = GL_FALSE;
        glGetShaderiv(id_, GL_COMPILE_STATUS, &status);
        if (status != GL_TRUE)
        {
		std::cerr << "[E] Shader::create: '" << source_ << "' failed to compile." << std::endl;
		std::cerr << infoLog(id_) << std::endl;
		release();
		return false;
        }
        return true;
}


bool Shader::release()
{
        // If id_ is 0, it will be silently ignored.
        if (id_ == 0)
        {
		return false;
        }
        
        glDeleteShader(id_);
        id_ = 0;

        const GLenum err = glGetError();
        if (err != GL_NO_ERROR)
        {
		switch (err)
		{
		case GL_INVALID_VALUE: std::cerr << "[E] Shader::release: glDeleteShader: `shader` is not a value generated by OpenGL." << std::endl; break;
		}
		return false;
        }
        return true;
}


// ========================
// Program
// ========================

Program::Program()
: head_(nullptr)
, tail_(nullptr)
, id_(0)
{
}


Program::~Program()
{
}


// Create and release
// ==================

bool Program::create()
{
        id_ = glCreateProgram();
        if (id_ == 0)
        {
		std::cerr << "[E] Program::create: glCreateProgram failed." << std::endl;
		return false;
        }
        return true;
}


bool Program::release()
{
        // Detach and release shaders.
        Shader *p = head_;
        while (p != nullptr)
        {
		Shader *const del = p;
		p = p->next_;

		if (detachShader(del->id_))
		{
			std::cout << "[I] Program: '" << del->source_ << "' detached." << std::endl;
		}
		del->release();
		delete del;
        }
        head_ = tail_ = nullptr;

        // Delete program.
        if (id_ == 0)
        {
		return false;
        }

        glDeleteProgram(id_);
        id_ = 0;

        const GLenum err = glGetError();
        if (err != GL_NO_ERROR)
        {
		switch (err)
		{
		case GL_INVALID_VALUE: std::cerr << "[E] Program::release: program is not a value generated by OpenGL" << std::endl; break;
		}
		return false;
        }
        return true;
}

    
// Attach and detach shaders
// =========================

bool Program::attachShader(const GLenum type, const std::string& source)
{
        Shader *const shader = new Shader(type, source);
        if (!shader->create())
        {
		// ydm TODO: Log error?
		delete shader;
		return false;
        }

        glAttachShader(id_, shader->id_);
        const GLenum err = glGetError();
        if (err != GL_NO_ERROR)
        {
		switch(err)
		{
		case GL_INVALID_VALUE: std::cerr << "[E] Program::attachShader: glAttachShader: either program or shader is not a value generated by OpenGL." << std::endl; break;
		case GL_INVALID_OPERATION: std::cerr << "[E] Program::attachShader: glAttachShader: program/shader is not a valid object OR shader is already attached to program." << std::endl; break;
		}

		shader->release();
		delete shader;
		return false;
        }

        // Add to linked list
        if (head_ == nullptr)
        {
		head_ = tail_ = shader;
        }
        else
        {
		tail_->next_ = shader;
		tail_ = shader;
        }
        std::cout << "[I] Program: '" << source << "' attached." << std::endl;
        return true;
}


bool Program::detachShader(const GLuint shader)
{
        glDetachShader(id_, shader);
        const GLenum err = glGetError();
        if (err != GL_NO_ERROR)
        {
		switch (err)
		{
		case GL_INVALID_VALUE: std::cerr << "[E] Program::detachShader: either `program` or `shader` is a value that was not generated by OpenGL" << std::endl; break;
		case GL_INVALID_OPERATION: std::cerr << "[E] Program::detachShader: `program` OR `shader` is invalid object OR `shader` is not attached to `program`" << std::endl; break;
		}
		return false;
        }
        return true;
}


// Link and use
// ============

bool Program::link()
{
        glLinkProgram(id_);
        const GLenum err = glGetError();
        if (err != GL_NO_ERROR)
        {
		std::cerr << "[E] Program::link: glLinkProgram: ";
		switch (err)
		{
		case GL_INVALID_VALUE: std::cerr << "`program` is not a value generated by OpenGL";
		case GL_INVALID_OPERATION: std::cerr << "`program` is not a program object OR it is the currently active program and transform feedback mode is active"; break;
		}
		std::cerr << std::endl;
		return false;
        }
        return true;
}


bool Program::use() const
{
        glUseProgram(id_);
        const GLenum err = glGetError();
        if (err != GL_NO_ERROR)
        {
		switch (err)
		{
		case GL_INVALID_VALUE: std::cerr << "[E] Program::use: glUseProgram: `program` is neither 0 nor a value generated by OpenGL" << std::endl; break;
		case GL_INVALID_OPERATION: std::cerr << "[E] Program::use: glUseProgram: `program` is not a program object OR could not be used OR feedback mode is active" << std::endl; break;
		}
		return false;
        }
        return true;
}


// Attributes and uniforms
// =======================

bool Program::umat3(const GLchar *const name, const GLfloat *const M, const GLboolean transpose)
{
        return setUniform(name, M, MATRIX3, transpose);
}


bool Program::umat4(const GLchar *const name, const GLfloat *const M, const GLboolean transpose)
{
        return setUniform(name, M, MATRIX4, transpose);
}


bool Program::uvec2(const GLchar *const name, const GLfloat *const v)
{
        return setUniform(name, v, VECTOR2);
}
    
    
bool Program::uvec3(const GLchar *const name, const GLfloat *const v)
{
        return setUniform(name, v, VECTOR3);
}


bool Program::uvec4(const GLchar *const name, const GLfloat *const v)
{
        return setUniform(name, v, VECTOR4);
}


bool Program::ufloat(const GLchar *const name, const GLfloat value)
{
        return setUniform(name, &value, FLOAT);
}


bool Program::setUniform(const GLchar *const name, const GLfloat *u, const enum UniformType t, const GLboolean transpose)
{
        const GLint loc = uniformLocation(name);
        if (loc == -1)
        {
		return false;
        }
        use();
        switch (t)
        {
        case MATRIX3: glUniformMatrix3fv(loc, 1, transpose, u); break;
        case MATRIX4: glUniformMatrix4fv(loc, 1, transpose, u); break;
        case VECTOR2: glUniform2fv(loc, 1, u);                  break;
        case VECTOR3: glUniform3fv(loc, 1, u);                  break;
        case VECTOR4: glUniform4fv(loc, 1, u);                  break;
	case FLOAT:   glUniform1f(loc, *u);                     break;
        }
        const GLenum err = glGetError();
        if (err != GL_NO_ERROR)
        {
		switch (err)
		{
		case GL_INVALID_OPERATION: std::cerr << "[E] Program::setUniform: Invalid operation" << std::endl; break;
		case GL_INVALID_VALUE: std::cerr << "[E] Program::setUniform: Invalid value" << std::endl; break;
		}
		return false;
        }
        return true;
}

    
GLint Program::uniformLocation(const GLchar *const name)
{
        const GLint location = glGetUniformLocation(id_, name);
        if (location == -1)
        {
		std::cerr << "[E] Program::uniform: '" << name << "' does not correspond to an active uniform variable in program"
			  << ", OR name starts with the reserved prefix 'gl_'"
			  << ", OR name is associated with an atomic counter or a named uniform block"
			  << std::endl;
        }
        const GLenum err = glGetError();
        if (err != GL_NO_ERROR)
        {
		switch (err)
		{
		case GL_INVALID_VALUE: std::cerr << "[E] Program::uniform: `program` is not a value generated by OpenGL" << std::endl; break;
		case GL_INVALID_OPERATION: std::cerr << "[E] Program::uniform: `program` is not a program object OR has not been successfully linked" << std::endl; break;
		}
		return -1;
        }
        return location;
}

} // namespace
