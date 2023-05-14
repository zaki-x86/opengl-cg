#include "Texture.h"

Texture::Texture() :
    m_fileLoc(""),
    m_textureUnit(GL_TEXTURE0),
    m_width(0),
    m_height(0),
    m_bitDepth(0),
    m_textureID(0),
    m_textureBuffer(nullptr)
{}

Texture::Texture(const std::string& fileLoc, GLenum textureUnit) :
    m_fileLoc(fileLoc),
    m_textureUnit(GL_TEXTURE0),
    m_width(0),
    m_height(0),
    m_bitDepth(0),
    m_textureID(0)
{
    (void)textureUnit;
    load(fileLoc);
}

void Texture::load(const std::string& fileLoc) {
    m_textureBuffer = stbi_load(fileLoc.c_str(), &m_width, &m_height, &m_bitDepth, 0);
    stbi_set_flip_vertically_on_load(true);  

    if (!m_textureBuffer) {
        #ifdef EXCEPTIONS_ENABLED
        throw std::runtime_error("Failed to load texture: " + fileLoc);
        #else
        std::cout << "Failed to load texture: " << fileLoc << std::endl;
        #endif
        return;
    }

    GL_CALL(glGenTextures(1, &m_textureID));
    GL_CALL(glBindTexture(GL_TEXTURE_2D, m_textureID));
    

    /// Set the texture wrapping/filtering options (on the currently bound texture object)
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT)); // S coord, GL_REPEAT is the default
    
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT)); // T coord, GL_REPEAT is the default
    
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR)); // zoom out, GL_LINEAR is the default
    
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)); // zoom in, GL_NEAREST is the default
    
    
    /// Generate the texture
    GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_textureBuffer));
    
    GL_CALL(glGenerateMipmap(GL_TEXTURE_2D));
    

    /// unbind the texture. Why? 
    /// To make sure we don't accidentally mess up our texture.
    GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
    

    /// Free the texture buffer
    /// In some cases, you may wanna keep the data around, or add an argument in the constructor
    /// to decide whether to keep the data around or not.
    stbi_image_free(m_textureBuffer);

    //
}

void Texture::bind(GLuint slot /* = 0 */) {
    /// glActiveTexture: Selects which texture unit subsequent texture state calls will affect.

    GL_CALL(glActiveTexture(m_textureUnit + slot));
    
    GL_CALL(glBindTexture(GL_TEXTURE_2D, m_textureID));
}

void Texture::unbind() {
    GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));   
}

void Texture::clear() {
    GL_CALL(glDeleteTextures(1, &m_textureID));
    
    m_textureID = 0;
    m_width = 0;
    m_height = 0;
    m_bitDepth = 0;
    m_fileLoc = "";
}

Texture::~Texture() {
    clear();
}

