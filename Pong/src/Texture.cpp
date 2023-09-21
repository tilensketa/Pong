#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <spdlog/spdlog.h>

Texture::Texture() {

    GLenum texType = GL_TEXTURE_2D;
    GLenum slot = GL_TEXTURE0;
    GLenum pixelType = GL_UNSIGNED_BYTE;

    m_Type = texType;

    int widthImg, heightImg, numColCh;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* bytes = stbi_load("Textures/white.png", &widthImg, &heightImg, &numColCh, 0);

    GLenum format;
    if (numColCh == 1)
        format = GL_RED;
    else if (numColCh == 3)
        format = GL_RGB;
    else if (numColCh == 4)
        format = GL_RGBA;
    else {
        spdlog::critical("Unsupported number of channels: {}", numColCh);
        stbi_image_free(bytes);
        return;
    }

    glGenTextures(1, &m_ID);
    glActiveTexture(slot);
    glBindTexture(texType, m_ID);

    glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
    glGenerateMipmap(texType);

    stbi_image_free(bytes);
    glBindTexture(texType, 0);
}

Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum pixelType) {
    m_Type = texType;
    
    int widthImg, heightImg, numColCh;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

    GLenum format;
    if (numColCh == 1)
        format = GL_RED;
    else if (numColCh == 3)
        format = GL_RGB;
    else if (numColCh == 4)
        format = GL_RGBA;
    else {
        spdlog::critical("Unsupported number of channels: {}", numColCh);
        stbi_image_free(bytes);
        return;
    }

    glGenTextures(1, &m_ID);
    glActiveTexture(slot);
    glBindTexture(texType, m_ID);

    glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
    glGenerateMipmap(texType);

    stbi_image_free(bytes);
    glBindTexture(texType, 0);
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit) {
    GLuint tex0Uni = glGetUniformLocation(shader.ID, uniform);
    shader.Activate();
    glUniform1i(tex0Uni, unit);
}

void Texture::Bind() {
    glBindTexture(m_Type, m_ID);
}

void Texture::Unbind() {
    glBindTexture(m_Type, 0);
}

void Texture::Delete() {
    glDeleteTextures(1, &m_ID);
}