#include "Shader.h"
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(bool debug) 
: m_programID(0), m_vertexShaderID(0), m_fragmentShaderID(0), m_debugInfo(nullptr), m_debug(debug) {
    if (m_debug) {
        m_debugInfo = new ShaderDebugInfo();
    }
}

Shader::Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, bool debug)
    : m_programID(0), m_vertexShaderID(0), m_fragmentShaderID(0), m_debug(debug) {
    
    if (m_debug) {
        m_debugInfo = new ShaderDebugInfo();
    }
    
    _setShaders(vertexShaderPath, fragmentShaderPath);

}

Shader::~Shader() {
    glDeleteProgram(m_programID);
    glDeleteShader(m_vertexShaderID);
    glDeleteShader(m_fragmentShaderID);
}

void Shader::compile() {
    m_programID = glCreateProgram();
    glAttachShader(m_programID, m_vertexShaderID);
    glAttachShader(m_programID, m_fragmentShaderID);
    glLinkProgram(m_programID);

    if(m_debug) {
        int success;
        glGetShaderiv(m_programID, GL_LINK_STATUS, &success);
        if(!success) {
            m_debugInfo->status = SHADER_COMPILE_FAILED || SHADER_LINK_FAILED;
            char infoLog[512];
            glGetShaderInfoLog(m_programID, 512, NULL, infoLog);
            m_debugInfo->LinkInfo = std::string(infoLog);
        }
        else {
            m_debugInfo->status = SHADER_COMPILE_SUCCESS || SHADER_LINK_SUCCESS;
            m_debugInfo->LinkInfo = std::string("Shader program compiled and linked successfully");
        }

        glValidateProgram(m_programID);
        if(!success) {
            m_debugInfo->status = SHADER_INVALID_PROGRAM;
            char infoLog[512];
            glGetShaderInfoLog(m_programID, 512, NULL, infoLog);
            m_debugInfo->ValidateInfo = std::string(infoLog);
        }
        else {
            m_debugInfo->status = SHADER_VALID_PROGRAM;
            m_debugInfo->ValidateInfo = std::string("Shader program passed validation");
        }
    } 
}

// Set uniforms implementations

void Shader::setUniform(const std::string& name, bool value) const {
    glUniform1i(glGetUniformLocation(m_programID, name.c_str()), (int)value);
}

void Shader::setUniform(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(m_programID, name.c_str()), value);
}

void Shader::setUniform(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(m_programID, name.c_str()), value);
}

void Shader::setUniform(const std::string& name, const glm::vec2& value) const {
    glUniform2fv(glGetUniformLocation(m_programID, name.c_str()), 1, &value[0]);
}

void Shader::setUniform(const std::string& name, float x, float y) const {
    glUniform2f(glGetUniformLocation(m_programID, name.c_str()), x, y);
}

void Shader::setUniform(const std::string& name, const glm::vec3& value) const {
    glUniform3fv(glGetUniformLocation(m_programID, name.c_str()), 1, &value[0]);
}

void Shader::setUniform(const std::string& name, float x, float y, float z) const {
    glUniform3f(glGetUniformLocation(m_programID, name.c_str()), x, y, z);
}

void Shader::setUniform(const std::string& name, const glm::vec4& value) const {
    glUniform4fv(glGetUniformLocation(m_programID, name.c_str()), 1, &value[0]);
}

void Shader::setUniform(const std::string& name, float x, float y, float z, float w) const {
    glUniform4f(glGetUniformLocation(m_programID, name.c_str()), x, y, z, w);
}

void Shader::setUniform(const std::string& name, const glm::mat2& mat) const {
    glUniformMatrix2fv(glGetUniformLocation(m_programID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setUniform(const std::string& name, const glm::mat3& mat) const {
    glUniformMatrix3fv(glGetUniformLocation(m_programID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setUniform(const std::string& name, const glm::mat4& mat) const {
    glUniformMatrix4fv(glGetUniformLocation(m_programID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}

GLint Shader::getUniformLocation(const std::string& name) const {
    return glGetUniformLocation(m_programID, name.c_str());
}


bool Shader::getUniform(const std::string& name, bool& value) const {
    GLint location = getUniformLocation(name);
    if (location == -1) {
        return false;
    }
    GLint data;
    glGetUniformiv(m_programID, location, &data);
    value = (bool)data;
    return true;
}

bool Shader::getUniform(const std::string& name, int& value) const {
    GLint location = getUniformLocation(name);
    if (location == -1) {
        return false;
    }
    glGetUniformiv(m_programID, location, &value);
    return true;
}

bool Shader::getUniform(const std::string& name, float& value) const {
    GLint location = getUniformLocation(name);
    if (location == -1) {
        return false;
    }
    glGetUniformfv(m_programID, location, &value);
    return true;
}

bool Shader::getUniform(const std::string& name, glm::vec2& value) const {
    GLint location = getUniformLocation(name);
    if (location == -1) {
        return false;
    }
    glGetUniformfv(m_programID, location, &value[0]);
    return true;
}

bool Shader::getUniform(const std::string& name, glm::vec3& value) const {
    GLint location = getUniformLocation(name);
    if (location == -1) {
        return false;
    }
    glGetUniformfv(m_programID, location, &value[0]);
    return true;
}

bool Shader::getUniform(const std::string& name, glm::vec4& value) const {
    GLint location = getUniformLocation(name);
    if (location == -1) {
        return false;
    }
    glGetUniformfv(m_programID, location, &value[0]);
    return true;
}

bool Shader::getUniform(const std::string& name, glm::mat2& value) const {
    GLint location = getUniformLocation(name);
    if (location == -1) {
        return false;
    }
    glGetUniformfv(m_programID, location, &value[0][0]);
    return true;
}

bool Shader::getUniform(const std::string& name, glm::mat3& value) const {
    GLint location = getUniformLocation(name);
    if (location == -1) {
        return false;
    }
    glGetUniformfv(m_programID, location, &value[0][0]);
    return true;
}

bool Shader::getUniform(const std::string& name, glm::mat4& value) const {
    GLint location = getUniformLocation(name);
    if (location == -1) {
        return false;
    }
    glGetUniformfv(m_programID, location, &value[0][0]);
    return true;
}

