#ifndef __SHADERS_HPP__
#define __SHADERS_HPP__

#include <iostream>
#include <map> // ydm TODO: Replace map with something faster!
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
    class Program;


    class Shader
    {
    public:
        Shader(const GLenum type, const std::string& source);
        ~Shader();

        bool create();
        bool free();

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
        bool attachShader(const GLenum type, const std::string& source);
        bool link();

        bool detachShader(const GLuint shader);
        bool free();

        bool use() const;
    
        // Attributes and uniforms
        GLuint attr(const GLchar *const name);
        GLuint unif(const GLchar *const name);
    
    private:
        Shader *head_;
        Shader *tail_;
        GLuint id_;
    };
};

#endif // __SHADERS_HPP__
