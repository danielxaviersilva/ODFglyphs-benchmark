#include "IndexBuffer.h"
#include <iostream>

//IndexBuffer::IndexBuffer()
//{
//    glGenBuffers(1,&m_vboID);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vboID);

//}

IndexBuffer::IndexBuffer(const unsigned int *data, int count)
{
    glGenBuffers(1,&m_iboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(unsigned int), data, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iboID);
    _check_gl_error(__FILE__, __LINE__);
    m_initialized = true;
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &m_iboID);
}

void IndexBuffer::genBuffer()
{
    if (!m_initialized){
        glGenBuffers(1,&m_iboID);
        m_initialized = true;
        return;
    }
    std::cerr << "Warning: Buffer already initialized e generated for this class" << std::endl;

}

void IndexBuffer::updateBufferData(const unsigned int *data, unsigned int count)
{
    if (!m_initialized)
        glGenBuffers(1,&m_iboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,count*sizeof(unsigned int),data, GL_STATIC_DRAW);
    _check_gl_error(__FILE__, __LINE__);
    m_initialized = true;
}

void IndexBuffer::bind()
{
    if (m_initialized)
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iboID);
    else
        std::cerr << "Index Buffer not initialized" << std:: endl;
    _check_gl_error(__FILE__, __LINE__);
}

void IndexBuffer::unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}



void IndexBuffer::_check_gl_error(const char *file, int line) {
    //Ting: sugestao para chamada
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
