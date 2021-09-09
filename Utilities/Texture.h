#ifndef TEXTURE_H
#define TEXTURE_H
#include <iostream>
#include <string>
//#include <GL/glew.h>
//#include <QGLFunctions>
#if defined(__APPLE__)
#include <OpenGL/gl.h>
#else
#include <gl.h>
#endif
//#include <gl.h>
#include "CGUtilities.h"



class Texture : protected CGUtilities
{
    unsigned int m_rendererID;
    std::string m_path;
    unsigned char *m_localBuffer;
    int m_width, m_height, m_BPP;
    bool m_initialized;

public:
    Texture();
    ~Texture();

    void Bind (unsigned int slot = 0) const;
    void Unbind() const;

    int getWidth() const;
    int getHeight() const;
    Texture(std::vector<float> data, int width, int height);
    void uploadTexture(std::vector<float> data, int width, int height);
    void uploadTextureRGBA(std::vector<float> data, int width, int height);
    void deleteTexture();
};

#endif // TEXTURE_H
