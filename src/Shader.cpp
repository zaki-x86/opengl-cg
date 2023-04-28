#include "Shader.h"

Shader::Shader() 
: m_programID(0), m_vertexShaderID(0), m_fragmentShaderID(0), m_vertexShaderCode(""), m_fragmentShaderCode("") { }

Shader::~Shader() {
    glDeleteProgram(m_programID);
    glDeleteShader(m_vertexShaderID);
    glDeleteShader(m_fragmentShaderID);
}

bool Shader::CompileVertexShader(const std::string& filePath) {
    _readShaderFile(filePath, VERTEX_SHADER);
    if (m_vertexShaderCode.empty()) {
        std::cout << "Failed to read shader file: " << filePath << std::endl;
        return false;
    }
    
    const char* shaderCode = m_vertexShaderCode.c_str();
    m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(m_vertexShaderID, 1, &shaderCode, NULL);
    glCompileShader(m_vertexShaderID);

    int success;
    glGetShaderiv(m_vertexShaderID, GL_COMPILE_STATUS, &success);

    return success > 0;
}

bool Shader::CompileFragmentShader(const std::string& filePath) {
    _readShaderFile(filePath, FRAGMENT_SHADER);
    if (m_fragmentShaderCode.empty()) {
        std::cout << "Failed to read shader file: " << filePath << std::endl;
        return false;
    }
    
    const char* shaderCode = m_fragmentShaderCode.c_str();
    m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(m_fragmentShaderID, 1, &shaderCode, NULL);
    glCompileShader(m_fragmentShaderID);
    
    int success;
    glGetShaderiv(m_vertexShaderID, GL_COMPILE_STATUS, &success);

    return success > 0;
}

std::string Shader::GetCompileInfo() {
    char infoLog[512];
    glGetShaderInfoLog(m_vertexShaderID, 512, NULL, infoLog);

    return std::string(infoLog);
}

bool Shader::Link() {
    m_programID = glCreateProgram();
    glAttachShader(m_programID, m_vertexShaderID);
    glAttachShader(m_programID, m_fragmentShaderID);
    glLinkProgram(m_programID);

    int success;
    glGetProgramiv(m_programID, GL_LINK_STATUS, &success);

    return success > 0;
}

std::string Shader::GetLinkInfo() {
    char infoLog[512];
    glGetProgramInfoLog(m_programID, 512, NULL, infoLog);

    return std::string(infoLog);
}

void Shader::Use() {
    glUseProgram(m_programID);
}