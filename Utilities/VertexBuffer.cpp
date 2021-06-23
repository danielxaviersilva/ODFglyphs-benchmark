#include "VertexBuffer.h"
#include <iostream>

//VertexBuffer::VertexBuffer()
//{
//    glGenBuffers(1,&m_vboID);
//    glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

//}

VertexBuffer::VertexBuffer(const void *data, int size)
{
    glGenBuffers(1,&m_vboID);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
    glBufferData(GL_ARRAY_BUFFER, size,data, GL_STATIC_DRAW);
    _check_gl_error(__FILE__, __LINE__);
    m_initialized = true;
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_vboID);
}

void VertexBuffer::genBuffer()
{
    if (!m_initialized){
        glGenBuffers(1,&m_vboID);
        m_initialized = true;
        return;
    }
    std::cerr << "Warning: Buffer already initialized e generated for this class" << std::endl;

}

void VertexBuffer::updateBufferData(const void *data, int size)
{
    if (!m_initialized)
        glGenBuffers(1,&m_vboID);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
    glBufferData(GL_ARRAY_BUFFER, size,data, GL_STATIC_DRAW);
    m_initialized = true;
}

void VertexBuffer::bind()
{
    if (m_initialized)
        glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
    else
        std::cerr << "Vertex Buffer not initialized" << std:: endl;
}

void VertexBuffer::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::_check_gl_error(const char *file, int line) {
    //sugestao para chamada
    //_check_gl_error(__FILE__,__LINE__)
    GLenum err (glGetError());
    while(err!=GL_NO_ERROR) {
        std::string error;
        switch(err) {
            case GL_INVALID_OPERATION: error="INVALID_OPERATION"; break;
            case GL_INVALID_ENUM: error="INVALID_ENUM"; break;
            case GL_INVALID_VALUE: error="INVALID_VALUE"; break;
            case GL_OUT_OF_MEMORY: error="OUT_OF_MEMORY"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: error="INVALID_FRAMEBUFFER_OPERATION"; break;
            case GL_STACK_UNDERFLOW: error="GL_STACK_UNDERFLOW"; break;
            case GL_STACK_OVERFLOW: error="GL_STACK_OVERFLOW"; break;
        }
        std::cout << "GL_" << error.c_str() <<" - "<< file << ":" << line << std::endl;
        err=glGetError();
    }
}
