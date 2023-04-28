#include "Shader.h"

Shader::Shader() 
: m_programID(0), m_vertexShaderID(0), m_fragmentShaderID(0), m_vertexShaderCode(""), m_fragmentShaderCode(""), m_debugInfo(nullptr), m_debug(true) { }

Shader::Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, bool debug)
: m_programID(0), m_vertexShaderID(0), m_fragmentShaderID(0), m_vertexShaderCode(""), m_fragmentShaderCode(""), m_debug(debug) {
    SetShader(vertexShaderPath, VERTEX_SHADER);
    SetShader(fragmentShaderPath, FRAGMENT_SHADER);

    if (m_debug) {
        m_debugInfo = new ShaderDebugInfo();
    }
}

Shader::~Shader() {
    glDeleteProgram(m_programID);
    glDeleteShader(m_vertexShaderID);
    glDeleteShader(m_fragmentShaderID);
}

void Shader::SetShader(const std::string& filePath, uint8_t shaderType) {
    if (shaderType == VERTEX_SHADER){
        _readShaderFile(filePath, VERTEX_SHADER);
        if (m_vertexShaderCode.empty()) {
            if(m_debug) {
                m_debugInfo->status = SHADER_COMPILE_FAILED || VERTEX_SHADER_FILE_EMPTY;
                m_debugInfo->VertexShaderCompileInfo = std::string("Failed to read shader file: " + filePath);
            }
            return;
        }
    }
    else if (shaderType == FRAGMENT_SHADER) {
        _readShaderFile(filePath, FRAGMENT_SHADER);
        if (m_fragmentShaderCode.empty()) {
            if(m_debug) {
                m_debugInfo->status = SHADER_COMPILE_FAILED || FRAGMENT_SHADER_FILE_EMPTY;
                m_debugInfo->FragmentShaderCompileInfo = "Failed to read shader file: " + filePath;
            }
            return;
        }
    }

    else {
        #ifdef EXCEPTIONS_ENABLED
        throw std::runtime_error("Invalid shader type");
        #endif // EXCEPTIONS_ENABLED
        return ;
    }
}


void Shader::Compile() {
    CompileVertexShader();
    CompileFragmentShader();
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
        m_debugInfo->status = SHADER_COMPILE_SUCCESS || SHADER_LINK_SUCCESS;
        m_debugInfo->LinkInfo = std::string("Shader program compiled and linked successfully");
    }
}