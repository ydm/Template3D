#ifndef __SHADERS_HPP__
#define __SHADERS_HPP__

#include <iostream>
#include <string>

#ifdef _WIN32
 #include <Windows.h>
#endif
#include <GL/glew.h>
// #include <GL/GLU.h>

// Notes:
//   1. Should I use glReleaseShaderCompiler()?


namespace shaders
{
    class Shader
    {
    public:
        Shader(const GLenum type, const std::string& source);
        ~Shader();

        bool create();
        bool free();

        Shader& operator=(const Shader& other);

    private:
        const GLenum type_;
        const std::string source_;

        GLuint id_;
    };

    class Program
    {
    public:
        Program();
        ~Program();

        bool use() const;
        GLuint attr(const char *const name);
        // GLuint attr(const std::string& name);

    private:

    };
};

#endif // __SHADERS_HPP__
