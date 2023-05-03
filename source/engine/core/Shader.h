#ifndef _SHADER_H_
#define _SHADER_H_

#include <string>
#include <iostream>
#include <fstream>

#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>

///TODO: Forward declare glm classes declarations
namespace glm {}


/**
 * decimals from 0 to 9 in hex:
 * 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 
 * 
 */
#define SHADER_COMPILE_SUCCESS 0b00000000
#define VERTEX_SHADER_COMPILE_SUCCESS 0b00000001
#define FRAGMENT_SHADER_COMPILE_SUCCESS 0b00000010
#define SHADER_LINK_SUCCESS 0b00000100

#define SHADER_COMPILE_FAILED 0b10000000
#define VERTEX_SHADER_COMPILE_FAILED 0b00000001
#define FRAGMENT_SHADER_COMPILE_FAILED 0b00000010
#define SHADER_LINK_FAILED 0b00000100
#define VERTEX_SHADER_FILE_READ_FAILED 0b00001000
#define FRAGMENT_SHADER_FILE_READ_FAILED 0b00010000
#define VERTEX_SHADER_FILE_EMPTY 0b00100000
#define FRAGMENT_SHADER_FILE_EMPTY 0b01000000

#define SHADER_VALID_PROGRAM 0b00001000
#define SHADER_INVALID_PROGRAM 0b01000000

struct ShaderDebugInfo {
    ShaderDebugInfo() : status(0), VertexShaderCompileInfo(""), FragmentShaderCompileInfo(""), LinkInfo("") {}
    ShaderDebugInfo(const ShaderDebugInfo& other) : status(other.status), VertexShaderCompileInfo(other.VertexShaderCompileInfo), FragmentShaderCompileInfo(other.FragmentShaderCompileInfo), LinkInfo(other.LinkInfo) {}
    ShaderDebugInfo(ShaderDebugInfo&& other) : status(other.status), VertexShaderCompileInfo(std::move(other.VertexShaderCompileInfo)), FragmentShaderCompileInfo(std::move(other.FragmentShaderCompileInfo)), LinkInfo(std::move(other.LinkInfo)) {}

    ShaderDebugInfo& operator= (const ShaderDebugInfo& other) {
        status = other.status;
        VertexShaderCompileInfo = other.VertexShaderCompileInfo;
        FragmentShaderCompileInfo = other.FragmentShaderCompileInfo;
        LinkInfo = other.LinkInfo;
        return *this;
    }

    ShaderDebugInfo& operator= (ShaderDebugInfo&& other) {
        status = other.status;
        VertexShaderCompileInfo = std::move(other.VertexShaderCompileInfo);
        FragmentShaderCompileInfo = std::move(other.FragmentShaderCompileInfo);
        LinkInfo = std::move(other.LinkInfo);
        return *this;
    }

    uint8_t status;
    std::string VertexShaderCompileInfo;
    std::string FragmentShaderCompileInfo;
    std::string LinkInfo;
    std::string ValidateInfo;
};


class Shader {
public:
    Shader(bool debug = true);
    
    Shader(
        const std::string& vertexShaderPath,
        const std::string& fragmentShaderPath,
        bool debug = true);
    
    ~Shader();

    void setShaders(
        const std::string& vertexShaderPath,
        const std::string& fragmentShaderPath) {
            _setShaders(vertexShaderPath, fragmentShaderPath);
        }

    inline constexpr unsigned int getID() const { return m_programID;}
    ShaderDebugInfo& getDebugInfo() const { return *m_debugInfo; }

    void compile();
    void disableDebug() { m_debug = false;}
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
    ShaderDebugInfo* m_debugInfo;
    bool m_debug;

    enum {
        VERTEX_SHADER,
        FRAGMENT_SHADER
    };

    std::string _readShaderFile(const std::string& filePath) {
        std::ifstream shaderFile(filePath);
        if (!shaderFile.is_open()) {
            #ifdef EXCEPTIONS_ENABLED
            throw std::runtime_error("Failed to open shader file: " + filePath);
            #endif // EXCEPTIONS_ENABLED
        }
        
        std::string res((std::istreambuf_iterator<char>(shaderFile)), std::istreambuf_iterator<char>());
        
        if (res.empty()) {
            #ifdef EXCEPTIONS_ENABLED
            throw std::runtime_error("Shader file is empty: " + filePath);
            #endif // EXCEPTIONS_ENABLED
        }

        return res;
    }

    void _setShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
        std::string m_vertexShaderCode = _readShaderFile(vertexShaderPath);
        if (m_vertexShaderCode.empty()) {
            if(m_debug) {
                m_debugInfo->status = SHADER_COMPILE_FAILED || VERTEX_SHADER_FILE_EMPTY;
                m_debugInfo->VertexShaderCompileInfo = std::string("Failed to read shader file: " + vertexShaderPath);
            }

            #ifdef EXCEPTIONS_ENABLED
            throw std::runtime_error("Failed to read shader file: " + vertexShaderPath);
            #endif // EXCEPTIONS_ENABLED
        }

        std::string m_fragmentShaderCode = _readShaderFile(fragmentShaderPath);
        if (m_fragmentShaderCode.empty()) {
            if(m_debug) {
                m_debugInfo->status = SHADER_COMPILE_FAILED || FRAGMENT_SHADER_FILE_EMPTY;
                m_debugInfo->FragmentShaderCompileInfo = "Failed to read shader file: " + fragmentShaderPath;
            }

            #ifdef EXCEPTIONS_ENABLED
            throw std::runtime_error("Failed to read shader file: " + fragmentShaderPath);
            #endif // EXCEPTIONS_ENABLED
        }

        // Compile shaders
        m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
        const char* vertexShaderCode = m_vertexShaderCode.c_str();
        glShaderSource(m_vertexShaderID, 1, &vertexShaderCode, NULL);
        glCompileShader(m_vertexShaderID);

        if(m_debug) {
            int success;
            glGetShaderiv(m_vertexShaderID, GL_COMPILE_STATUS, &success);
            if(!success) {
                m_debugInfo->status = SHADER_COMPILE_FAILED || VERTEX_SHADER_COMPILE_FAILED;
                char infoLog[512];
                glGetShaderInfoLog(m_vertexShaderID, 512, NULL, infoLog);
                m_debugInfo->VertexShaderCompileInfo = std::string(infoLog);
            }
        }

        m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
        const char* fragmentShaderCode = m_fragmentShaderCode.c_str();
        glShaderSource(m_fragmentShaderID, 1, &fragmentShaderCode, NULL);
        glCompileShader(m_fragmentShaderID);

        if(m_debug) {
            int success;
            glGetShaderiv(m_fragmentShaderID, GL_COMPILE_STATUS, &success);
            if(!success) {
                m_debugInfo->status = SHADER_COMPILE_FAILED || FRAGMENT_SHADER_COMPILE_FAILED;
                char infoLog[512];
                glGetShaderInfoLog(m_fragmentShaderID, 512, NULL, infoLog);
                m_debugInfo->FragmentShaderCompileInfo = std::string(infoLog);
            }
        }
    }
};


#endif // !_SHADER_H_