#include "Shader.h"

Shader::Shader() 
: m_programID(0), m_vertexShaderID(0), m_fragmentShaderID(0), m_vertexShaderCode(""), m_fragmentShaderCode(""), m_debugInfo(nullptr), m_debug(true), m_vertLocation(0) { }

Shader::Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, bool debug)
: m_programID(0), m_vertexShaderID(0), m_fragmentShaderID(0), m_vertexShaderCode(""), m_fragmentShaderCode(""), m_debug(debug), m_vertLocation(0) {
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
    m_vertLocation = glGetAttribLocation(m_programID, "position");
    //TODO IT FAILS std::cout << "Vertex location: " << m_vertLocation << std::endl;

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

// Set uniforms implementations

void Shader::SetUniform(const std::string& name, bool value) const {
    glUniform1i(glGetUniformLocation(m_programID, name.c_str()), (int)value);
}

void Shader::SetUniform(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(m_programID, name.c_str()), value);
}

void Shader::SetUniform(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(m_programID, name.c_str()), value);
}

void Shader::SetUniform(const std::string& name, const glm::vec2& value) const {
    glUniform2fv(glGetUniformLocation(m_programID, name.c_str()), 1, &value[0]);
}

void Shader::SetUniform(const std::string& name, float x, float y) const {
    glUniform2f(glGetUniformLocation(m_programID, name.c_str()), x, y);
}

void Shader::SetUniform(const std::string& name, const glm::vec3& value) const {
    glUniform3fv(glGetUniformLocation(m_programID, name.c_str()), 1, &value[0]);
}

void Shader::SetUniform(const std::string& name, float x, float y, float z) const {
    glUniform3f(glGetUniformLocation(m_programID, name.c_str()), x, y, z);
}

void Shader::SetUniform(const std::string& name, const glm::vec4& value) const {
    glUniform4fv(glGetUniformLocation(m_programID, name.c_str()), 1, &value[0]);
}

void Shader::SetUniform(const std::string& name, float x, float y, float z, float w) const {
    glUniform4f(glGetUniformLocation(m_programID, name.c_str()), x, y, z, w);
}

void Shader::SetUniform(const std::string& name, const glm::mat2& mat) const {
    glUniformMatrix2fv(glGetUniformLocation(m_programID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::SetUniform(const std::string& name, const glm::mat3& mat) const {
    glUniformMatrix3fv(glGetUniformLocation(m_programID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::SetUniform(const std::string& name, const glm::mat4& mat) const {
    glUniformMatrix4fv(glGetUniformLocation(m_programID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
