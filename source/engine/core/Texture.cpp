#include "Texture.h"

Texture::Texture() :
    m_textureID(0),
    m_width(0),
    m_height(0),
    m_bitDepth(0),
    m_fileLoc("")
{}

Texture::Texture(const std::string& fileLoc) :
    m_textureID(0),
    m_width(0),
    m_height(0),
    m_bitDepth(0),
    m_fileLoc(fileLoc)
{
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

    glGenTextures(1, &m_textureID);
    glBindTexture(GL_TEXTURE_2D, m_textureID);

    /// Set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // S coord, GL_REPEAT is the default
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // T coord, GL_REPEAT is the default
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // zoom out, GL_LINEAR is the default
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // zoom in, GL_NEAREST is the default
    
    /// Generate the texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_textureBuffer);
    glGenerateMipmap(GL_TEXTURE_2D);

    /// unbind the texture. Why? 
    /// To make sure we don't accidentally mess up our texture.
    glBindTexture(GL_TEXTURE_2D, 0);

    /// Free the texture buffer
    /// In some cases, you may wanna keep the data around, or add an argument in the constructor
    /// to decide whether to keep the data around or not.
    stbi_image_free(m_textureBuffer);

    //GL_CHECK_ERRORS();
}

void Texture::bind(GLuint slot /* = 0 */) {
    /// glActiveTexture: Selects which texture unit subsequent texture state calls will affect.

    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_textureID);

}

void Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::clear() {
    glDeleteTextures(1, &m_textureID);
    m_textureID = 0;
    m_width = 0;
    m_height = 0;
    m_bitDepth = 0;
    m_fileLoc = "";
}

Texture::~Texture() {
    clear();
}

