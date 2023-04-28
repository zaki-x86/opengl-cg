#ifndef _SHADER_H_
#define _SHADER_H_

#include <string>
#include <iostream>
#include <fstream>

#include <GL/glew.h>
#include <glm/vec3.hpp>

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
};


class Shader {
public:
    Shader();
    
    Shader(
        const std::string& vertexShaderPath,
        const std::string& fragmentShaderPath,
        bool debug = true);
    
    ~Shader();

    void SetShader(const std::string& filePath, uint8_t shaderType);

    inline std::string GetVertexShaderCode() const { return m_vertexShaderCode; }
    inline constexpr unsigned int GetVertexShaderID() const { return m_vertexShaderID;}
    inline std::string GetFragmentShaderCode() const { return m_fragmentShaderCode;}
    inline constexpr unsigned int GetFragmentShaderID() const { return m_fragmentShaderID;}
    inline constexpr unsigned int GetProgramID() const { return m_programID;}
    ShaderDebugInfo& GetDebugInfo() const { return *m_debugInfo; }

    void Compile();
    void DisableDebug() { m_debug = false;}
    void Use() { glUseProgram(m_programID); }

private:
    GLuint m_programID;
    GLuint m_vertexShaderID;
    GLuint m_fragmentShaderID;
    std::string m_vertexShaderCode;
    std::string m_fragmentShaderCode;
    ShaderDebugInfo* m_debugInfo;
    bool m_debug;

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

    void CompileVertexShader() {
        
        
        const char* shaderCode = m_vertexShaderCode.c_str();
        m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(m_vertexShaderID, 1, &shaderCode, NULL);
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
            m_debugInfo->status = SHADER_COMPILE_SUCCESS || VERTEX_SHADER_COMPILE_SUCCESS;
            m_debugInfo->VertexShaderCompileInfo = std::string("Vertex shader compiled successfully");
        }

        return;
    }

    void CompileFragmentShader() {
        const char* shaderCode = m_fragmentShaderCode.c_str();
        m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(m_fragmentShaderID, 1, &shaderCode, NULL);
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
            m_debugInfo->status = SHADER_COMPILE_SUCCESS || FRAGMENT_SHADER_COMPILE_SUCCESS;
            m_debugInfo->FragmentShaderCompileInfo = "Fragment shader compiled successfully";
        }
    }
};


#endif // !_SHADER_H_