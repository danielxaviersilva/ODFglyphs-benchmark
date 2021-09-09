#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

//#include <GL/glew.h>
#include <QOpenGLFunctions>


class VertexBuffer
{
    bool m_initialized;
    unsigned int m_vboID;

    void _check_gl_error(const char *file, int size);
public:
    VertexBuffer(): m_initialized(false), m_vboID(0){};
    VertexBuffer(const void * data, int size);
    ~VertexBuffer();

    void genBuffer();
    void bind();
    void unbind();
    void updateBufferData(const void *data, int size);





};

#endif // VERTEXBUFFER_H
