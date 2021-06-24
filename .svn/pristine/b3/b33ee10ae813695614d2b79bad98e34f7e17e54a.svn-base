#include "VertexArray.h"
#include <iostream>

VertexArray::VertexArray(): m_stride(0), m_initialized(false)
{
//    glGenVertexArrays(1, &m_vao);
}

VertexArray::~VertexArray()
{
    if (m_initialized)
      glDeleteVertexArrays(1, &m_vao);
}

void VertexArray::bind()
{
    if (!m_initialized)
    {
        glGenVertexArrays(1, &m_vao);
        m_initialized = true;
    }
    glBindVertexArray(m_vao);
}
void VertexArray::unbind()
{
    glBindVertexArray(0);
}

void VertexArray::clearLayout()
{
    m_layout.clear();
    m_stride = 0;
}

void VertexArray::addBuffer(VertexBuffer &vb)
{
    bind();
    vb.bind();
    int offset = 0;
    for (int i = 0 ; i < int(m_layout.size()); i++)
    {
        glEnableVertexAttribArray(m_layout[i].varLocation);
        glVertexAttribPointer(m_layout[i].varLocation, m_layout[i].elementCount, m_layout[i].type, m_layout[i].normalized, m_stride, (void*)( offset) );
        if (m_layout[i].isInstanced == INSTANCED)
            glVertexAttribDivisor(m_layout[i].varLocation, m_layout[i].instanciationDivisor);

        switch(m_layout[i].type)
        {
            case GL_FLOAT: offset += m_layout[i].elementCount*sizeof(GLfloat); break;
            case GL_UNSIGNED_INT: offset += m_layout[i].elementCount*sizeof(GLuint); break;
            case GL_BYTE: offset += m_layout[i].elementCount*sizeof(GLbyte); break;
            default :std:: cerr << "Something wrong with the variable type stated in this layout" << std::endl;
        }
    }

}

template <typename T>
void VertexArray::push(unsigned int varLocation, unsigned int elementCount)
{
    std::cerr<< "Something went a little wrong with the variables type you called the function" << std::endl;
    std::cerr<< varLocation << elementCount << std::endl;
}

template<>
void VertexArray::push<float>(unsigned int varLocation, unsigned int elementCount)
{
    m_layout.push_back({varLocation, elementCount,GL_FLOAT, GL_FALSE, INSTANTIATION_MODE::NON_INSTANCED, 0});
     m_stride += elementCount*sizeof(GLfloat);
}

template<>
void VertexArray::push<unsigned int> (unsigned int varLocation, unsigned int elementCount)
{
    m_layout.push_back({varLocation, elementCount, GL_UNSIGNED_INT, GL_FALSE, INSTANTIATION_MODE::NON_INSTANCED, 0});
     m_stride += elementCount*sizeof(GLuint);
}

template<>
void VertexArray::push<unsigned char> (unsigned int varLocation, unsigned int elementCount)
{
    m_layout.push_back({varLocation, elementCount, GL_BYTE, GL_TRUE, INSTANTIATION_MODE::NON_INSTANCED, 0});
    m_stride += elementCount*sizeof(GLbyte);
}

/*************************************************************************************************************************/
template<typename T>
void VertexArray::push(unsigned int varLocation, unsigned int elementCount, bool normalized)
{
    std::cerr<< "Something went a little wrong with the variables type you called the function" << std::endl;
    std::cerr<< varLocation << elementCount << normalized << std::endl;
}

template<>
void VertexArray::push<float>(unsigned int varLocation, unsigned int elementCount, bool normalized)
{
    m_layout.push_back({varLocation, elementCount,GL_FLOAT,normalized, INSTANTIATION_MODE::NON_INSTANCED, 0});
     m_stride += elementCount*sizeof(GLfloat);
}


template<>
void VertexArray::push<unsigned int>(unsigned int varLocation, unsigned int elementCount, bool normalized)
{
    m_layout.push_back({varLocation, elementCount,GL_UNSIGNED_INT,normalized, INSTANTIATION_MODE::NON_INSTANCED, 0});
    m_stride += elementCount*sizeof(GLuint);
}



template<>
void VertexArray::push<unsigned char>(unsigned int varLocation, unsigned int elementCount, bool normalized)
{
    m_layout.push_back({varLocation, elementCount,GL_BYTE, normalized, INSTANTIATION_MODE::NON_INSTANCED, 0});
    m_stride += elementCount*sizeof(GLbyte);
}

/*************************************************************************************************************************/

template<typename T>
void VertexArray::push(unsigned int varLocation, unsigned int elementCount, bool normalized, VertexArray::INSTANTIATION_MODE isInstanced, int instatiation)
{
    std::cerr<< "Something went a little wrong with the variables type you called the function" << std::endl;
    std::cerr<< varLocation << elementCount << normalized << isInstanced << instatiation << std::endl;
}

template<>
void VertexArray::push<float>(unsigned int varLocation, unsigned int elementCount, bool normalized, VertexArray::INSTANTIATION_MODE isInstanced, int instatiation)
{
    m_layout.push_back({varLocation, elementCount,GL_FLOAT,normalized, isInstanced, instatiation});
    m_stride += elementCount*sizeof(GLfloat);

}

template<>
void VertexArray::push<unsigned int>(unsigned int varLocation, unsigned int elementCount, bool normalized, VertexArray::INSTANTIATION_MODE isInstanced, int instatiation)
{
    m_layout.push_back({varLocation, elementCount,GL_UNSIGNED_INT,normalized, isInstanced, instatiation});
    m_stride += elementCount*sizeof(GLuint);

}
template<>
void VertexArray::push<unsigned char>(unsigned int varLocation, unsigned int elementCount, bool normalized, VertexArray::INSTANTIATION_MODE isInstanced, int instatiation)
{
    m_layout.push_back({varLocation, elementCount,GL_BYTE, normalized, isInstanced, instatiation});
    m_stride += elementCount*sizeof(GLbyte);

}
