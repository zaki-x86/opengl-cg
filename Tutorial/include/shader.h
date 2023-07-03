#ifndef _SHADER_H_
#define _SHADER_H_

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>

///TODO: Forward declare glm classes declarations
namespace glm {}


class Shader {
public:
    Shader();
    
    Shader(
        const std::string& vertexShaderPath,
        const std::string& fragmentShaderPath);
    
    ~Shader();

    void setShaders(
        const std::string& vertexShaderPath,
        const std::string& fragmentShaderPath) 
    {
        _setShaders(vertexShaderPath, fragmentShaderPath);
    }

    inline constexpr unsigned int id() const { return m_programID;}

    void use() { glUseProgram(m_programID); }

    /// Set uniforms
    void setUniform(const std::string& name, bool value) const;
    void setUniform(const std::string& name, int value) const;
    void setUniform(const std::string& name, float value) const;
    void setUniform(const std::string& name, const glm::vec3& value) const;
    void setUniform(const std::string& name, const glm::vec4& value) const;
    void setUniform(const std::string& name, const glm::mat3& value) const;
    void setUniform(const std::string& name, const glm::mat4& value) const;
    void setUniform(const std::string& name, const glm::vec2& value) const;
    void setUniform(const std::string& name, float x, float y) const;
    void setUniform(const std::string& name, float x, float y, float z) const;
    void setUniform(const std::string& name, float x, float y, float z, float w) const;
    void setUniform(const std::string& name, const glm::mat2& mat) const;

    /// Get uniforms
    GLint getUniformLocation(const std::string& name) const;

    /// Read uniform values
    bool getUniform(const std::string& name, bool& value) const;
    bool getUniform(const std::string& name, int& value) const;
    bool getUniform(const std::string& name, float& value) const;
    bool getUniform(const std::string& name, glm::vec3& value) const;
    bool getUniform(const std::string& name, glm::vec4& value) const;
    bool getUniform(const std::string& name, glm::mat3& value) const;
    bool getUniform(const std::string& name, glm::mat4& value) const;
    bool getUniform(const std::string& name, glm::vec2& value) const;
    bool getUniform(const std::string& name, glm::mat2& value) const;

    /// Get attributes
    GLint getAttributeLocation(const std::string& name) const;

private:
    GLuint m_programID;
    GLuint m_vertexShaderID;
    GLuint m_fragmentShaderID;

private:
    enum {
        VERTEX_SHADER,
        FRAGMENT_SHADER
    };

private:
    void _setShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
        // 1. retrieve the vertex/fragment source code from filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        // ensure ifstream objects can throw exceptions:
        vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        try 
        {
            // open files
            vShaderFile.open(vertexShaderPath);
            fShaderFile.open(fragmentShaderPath);
            std::stringstream vShaderStream, fShaderStream;
            // read file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();		
            // close file handlers
            vShaderFile.close();
            fShaderFile.close();
            // convert stream into string
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();			
        }
        catch (std::ifstream::failure& e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
        }
        const char* vShaderCode = vertexCode.c_str();
        const char * fShaderCode = fragmentCode.c_str();
        // 2. compile shaders

        // vertex shader
        m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(m_vertexShaderID, 1, &vShaderCode, NULL);
        glCompileShader(m_vertexShaderID);
        checkCompileErrors(m_vertexShaderID, "VERTEX");
        // fragment Shader
        m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(m_fragmentShaderID, 1, &fShaderCode, NULL);
        glCompileShader(m_fragmentShaderID);
        checkCompileErrors(m_fragmentShaderID, "FRAGMENT");
        // shader Program
        m_programID = glCreateProgram();
        glAttachShader(m_programID, m_vertexShaderID);
        glAttachShader(m_programID, m_fragmentShaderID);
        glLinkProgram(m_programID);
        checkCompileErrors(m_programID, "PROGRAM");
        // delete the shaders as they're linked into our program now and no longer necessary
        glDeleteShader(m_vertexShaderID);
        glDeleteShader(m_fragmentShaderID);
    }

    void checkCompileErrors(GLuint shader, std::string type)
    {
        GLint success;
        GLchar infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }
};


#endif // !_SHADER_H_