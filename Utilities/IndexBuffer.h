#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H
//#include <GL/glew.h>
#include <QOpenGLFunctions>


class IndexBuffer
{
    bool m_initialized;
    unsigned int m_iboID;
    void _check_gl_error(const char *file, int size);
public:
    IndexBuffer(): m_initialized(false), m_iboID(0){};
    IndexBuffer(const unsigned int *data, int count);
    ~IndexBuffer();

    void genBuffer();
    void bind();
    void unbind();
    void updateBufferData(const void *data, int size);
    void updateBufferData(const unsigned int *data, unsigned int count);
};

#endif // INDEXBUFFER_H
