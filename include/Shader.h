#ifndef _SHADER_H_
#define _SHADER_H_

#include <string>
#include <iostream>
#include <fstream>

#include <GL/glew.h>
#include <glm/vec3.hpp>

class Shader {
public:
    Shader();
    ~Shader();

    bool CompileVertexShader(const std::string& filePath);
    bool CompileFragmentShader(const std::string& filePath);
    std::string GetCompileInfo();
    bool Link();
    std::string GetLinkInfo();

    void Use();

    inline constexpr uint32_t GetProgramID() const noexcept { return m_programID; }
    inline constexpr uint32_t GetVertexShaderID() const noexcept { return m_vertexShaderID; }
    inline constexpr uint32_t GetFragmentShaderID() const noexcept { return m_fragmentShaderID; }

private:
    GLuint m_programID;
    GLuint m_vertexShaderID;
    GLuint m_fragmentShaderID;
    std::string m_vertexShaderCode;
    std::string m_fragmentShaderCode;

    enum {
        VERTEX_SHADER,
        FRAGMENT_SHADER
    };

    void _readShaderFile(const std::string& filePath, uint8_t shaderType) {
        std::ifstream shaderFile(filePath);
        if (!shaderFile.is_open()) {
            #ifdef EXCEPTIONS_ENABLED
            throw std::runtime_error("Failed to open shader file: " + filePath);
            #endif // EXCEPTIONS_ENABLED
        }

        if (shaderType == VERTEX_SHADER)
            m_vertexShaderCode = std::string((std::istreambuf_iterator<char>(shaderFile)), std::istreambuf_iterator<char>());
        else if (shaderType == FRAGMENT_SHADER)
            m_fragmentShaderCode = std::string((std::istreambuf_iterator<char>(shaderFile)), std::istreambuf_iterator<char>());

        if (m_vertexShaderCode.empty() || m_fragmentShaderCode.empty()) {
            #ifdef EXCEPTIONS_ENABLED
            throw std::runtime_error("Shader file is empty: " + filePath);
            #endif // EXCEPTIONS_ENABLED
        }
    }
};


#endif // !_SHADER_H_