#include "Texture2D.h"

#include "../Data/Image.h"
#include "GL/glew.h"

namespace trifle
{
Texture2D::Texture2D()
{
}

Texture2D::Texture2D(const Texture2D& rhs)
{
    m_id = rhs.m_id;
    m_width = rhs.m_width;
    m_height = rhs.m_height;
}

Texture2D::~Texture2D()
{
}

void Texture2D::SetDataByColour(unsigned int width, unsigned int height, Colour* data)
{
    m_width = width;
    m_height = height;

    glGenTextures(1, &m_id);
    Bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, m_width, m_height, 0, GL_RGBA, GL_FLOAT, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    Unbind();
}

void Texture2D::SubDataByColour(Colour* data)
{
    if (m_id != -1)
    {
        Bind();
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_width, m_height, GL_RGBA, GL_FLOAT, data);
    }
}

void Texture2D::Bind()
{
    glBindTexture(GL_TEXTURE_2D, m_id);
}

void Texture2D::Unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
bool Texture2D::IsInitialised()
{
    return m_id != -1;
}
} // namespace trifle
