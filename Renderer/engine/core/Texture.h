#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>
#include <fstream>

#include "../opengl/utils.h"
#include "Shader.h"
#include "stb_image/stb_image.h"

    /// Sampling
    /// sampling is the process of determining the texture color for a texture coordinate
    /// and is done using a sampler, which is a function that takes a texture coordinate as input
    /// and outputs a color
    /// a sampler is used in a shader program to read a texture

    /// Texture types
    /// GL_TEXTURE_2D: sets the texture target to a 2D texture, which is the default
    /// GL_TEXTURE_1D: sets the texture target to a 1D texture, which is used for storing a line of data
    /// GL_TEXTURE_3D: sets the texture target to a 3D texture, which is used for storing a 3D volume of data
    /// GL_TEXTURE_1D_ARRAY, GL_TEXTURE_2D_ARRAY: sets the texture target to a 1D or 2D texture array, which is used for storing an array of 1D or 2D textures
    /// GL_TEXTURE_RECTANGLE: sets the texture target to a rectangle texture, which is used for storing a single 2D texture that has no mipmaps and only uses GL_CLAMP_TO_EDGE for wrapping
    /// GL_TEXTURE_CUBE_MAP: sets the texture target to a cube map texture, which is used for storing a cube map
    /// GL_TEXTURE_CUBE_MAP_ARRAY: sets the texture target to a cube map array texture, which is used for storing an array of cube maps
    /// GL_TEXTURE_BUFFER: sets the texture target to a buffer texture, which is used for storing a one-dimensional texture buffer
    /// GL_TEXTURE_2D_MULTISAMPLE: sets the texture target to a 2D multisample texture, which is used for storing a multisample texture
    /// GL_TEXTURE_2D_MULTISAMPLE_ARRAY: sets the texture target to a 2D multisample array texture, which is used for storing an array of multisample textures

    /// Wrapping: what happens when texture coordinates are outside of the range [0, 1]
    /// Filtering: what happens when texture coordinates are between pixels
    
    /// Filtering
    /// GL_REPEAT: repeat the texture image
    /// GL_MIRRORED_REPEAT: repeat the texture image but mirror it with each repeat
    /// GL_CLAMP_TO_EDGE: clamp the coordinates between 0 and 1
    /// GL_CLAMP_TO_BORDER: coordinates outside the range are given a specified border color
    /// GL_NEAREST: (also called point filtering) selects the pixel nearest to the texture coordinate
    /// GL_LINEAR: (also called linear filtering) selects the four pixels nearest to the texture coordinate and interpolates them
    /// GL_NEAREST_MIPMAP_NEAREST: selects the mipmap that most closely matches the size of the pixel being textured and uses the GL_NEAREST criterion (the texture with the nearest color)
    /// GL_LINEAR_MIPMAP_NEAREST: selects the mipmap that most closely matches the size of the pixel being textured and uses the GL_LINEAR criterion (a weighted average of the four textures that are closest to the texture coordinate)
    /// GL_NEAREST_MIPMAP_LINEAR: selects the two mipmaps that most closely match the size of the pixel being textured and uses the GL_NEAREST criterion (the texture with the nearest color)
    /// GL_LINEAR_MIPMAP_LINEAR: selects the two mipmaps that most closely match the size of the pixel being textured and uses the GL_LINEAR criterion (a weighted average of the two mipmaps that are closest to the texture coordinate)
    /// GL_NEAREST is generally faster than GL_LINEAR, but it can produce textured images with sharper edges because the transition between texture elements is not as smooth. The quality of the texture sampling can be improved by using mipmaps.
    /// GL_LINEAR produces better quality images since it performs a linear interpolation to compute the texture value at a given coordinate. However, it is slightly slower than GL_NEAREST because it needs to process more texture elements.
    /// GL_LINEAR is generally preferred over GL_NEAREST for texture mapping.
    
    /// Wrapping
    /// GL_TEXTURE_WRAP_S: sets the wrapping method for texture coordinate s, which is the x coordinate in texture space
    /// GL_TEXTURE_WRAP_T: sets the wrapping method for texture coordinate t, which is the y coordinate in texture space
    /// GL_TEXTURE_WRAP_R: sets the wrapping method for texture coordinate r, which is the z coordinate in texture space
    
    /// Texture parameters
    /// GL_TEXTURE_MIN_FILTER: sets the texture minifying function, which is used whenever the pixel being textured maps to an area greater than one texture element
    /// GL_TEXTURE_MAG_FILTER: sets the texture magnification function, which is used when the pixel being textured maps to an area less than or equal to one texture element
    /// GL_TEXTURE_WRAP_S: sets the texture wrapping function for texture coordinate s
    /// GL_TEXTURE_WRAP_T: sets the texture wrapping function for texture coordinate t
    /// GL_TEXTURE_WRAP_R: sets the texture wrapping function for texture coordinate r
    /// GL_TEXTURE_BASE_LEVEL: sets the index of the lowest defined mipmap level
    /// GL_TEXTURE_MAX_LEVEL: sets the index of the highest defined mipmap level
    /// GL_TEXTURE_MAX_LOD: sets the maximum level-of-detail parameter
    /// GL_TEXTURE_MIN_LOD: sets the minimum level-of-detail parameter
    /// GL_TEXTURE_LOD_BIAS: sets the level-of-detail bias parameter

    /// Mipmaps
    /// mipmaps are a collection of images that represent the same texture at different levels of detail
    /// they are used to improve rendering performance
    /// mipmaps are pre-calculated, optimized collections of images that accompany a main texture, intended to increase rendering speed and reduce aliasing artifacts

class Texture {
public:
    Texture();
    Texture(const std::string& fileLoc, GLenum textureUnit = GL_TEXTURE0);
    ~Texture();

    void load(const std::string& fileLoc);
    void bind(GLuint slot = 0);
    void unbind();
    void clear();


    int width() const { return m_width; }
    void setWidth(int width) { m_width = width; }
    int height() const { return m_height; }
    void setHeight(int height) { m_height = height; }
    int bitDepth() const { return m_bitDepth; }
    void setBitDepth(int bitDepth) { m_bitDepth = bitDepth; }
private:
    std::string m_fileLoc;
    GLenum m_textureUnit; // texture unit is the slot that the texture is bound to
    int m_width, m_height, m_bitDepth;
    GLuint m_textureID;
    unsigned char* m_textureBuffer;

};

#endif // !_TEXTURE_H_