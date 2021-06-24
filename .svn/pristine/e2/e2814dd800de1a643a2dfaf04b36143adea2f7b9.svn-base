#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include <QOpenGLFunctions>
#include <vector>
#include "VertexBuffer.h"


class VertexArray
{
public:
    enum INSTANTIATION_MODE{
        NON_INSTANCED, INSTANCED
    };
private:
    typedef struct _layout{
        unsigned int varLocation;
        unsigned int elementCount;
        unsigned int type;
        bool normalized;
        INSTANTIATION_MODE isInstanced;
        int instanciationDivisor;

    } layout;

    std::vector<layout> m_layout;
    unsigned int m_vao;
    unsigned int m_stride;
    bool m_initialized;
public:



    VertexArray();
    ~VertexArray();
    void bind();
    void unbind();
    void clearLayout();

    void addBuffer(VertexBuffer &vb);


    /*Buffer layout methods*/

    template<typename T>
    void push(unsigned int varLocation, unsigned int elementCount);
    template<>
    void push<float>(unsigned int varLocation, unsigned int elementCount);
    template<>
    void push<unsigned int> (unsigned int varLocation, unsigned int elementCount);
    template<>
    void push<unsigned char> (unsigned int varLocation, unsigned int elementCount);



    template<typename T>
    void push(unsigned int varLocation, unsigned int elementCount, bool normalized);
    template<>
    void push<float>(unsigned int varLocation, unsigned int elementCount, bool normalized);
    template<>
    void push<unsigned int>(unsigned int varLocation, unsigned int elementCount, bool normalized);
    template<>
    void push<unsigned char>(unsigned int varLocation, unsigned int elementCount, bool normalized);


    template<typename T>
    void push(unsigned int varLocation, unsigned int elementCount, bool normalized, INSTANTIATION_MODE isInstanced, int instatiation);

    template<>
    void push<float>(unsigned int varLocation, unsigned int elementCount, bool normalized, INSTANTIATION_MODE isInstanced, int instatiation);

    template<>
    void push<unsigned int>(unsigned int varLocation, unsigned int elementCount, bool normalized, INSTANTIATION_MODE isInstanced, int instatiation);

    template<>
    void push<unsigned char>(unsigned int varLocation, unsigned int elementCount, bool normalized, INSTANTIATION_MODE isInstanced, int instatiation);



};

#endif // VERTEXARRAY_H
