/**
 * @file ODFRendererInstanced.h
 *
 * @brief Prototype 2 for rendering glyphs benchmarking: indexing, Instance rendering
 *
 * @author Daniel Xavier Silva
 * Contact: danielxaviers@gmail.com
 *
 */
#ifndef ODFRENDERERINSTANCED_H
#define ODFRENDERERINSTANCED_H
#include "../ODFSamples.h"

#include <iostream>
#include <vector>
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <QOpenGLFunctions>
#include "../../Utilities/VertexArray.h"
#include "../../Utilities/VertexBuffer.h"
#include "../../Utilities/IndexBuffer.h"
#include "../../Utilities/Shader.h"
#include "../../Utilities/CGUtilities.h"
#include "../../Utilities/Texture.h"


class ODFRendererInstanced: protected CGUtilities
{

protected:
    VertexBuffer m_SphereVBO;
    VertexBuffer m_SphereAttributesVBO;
//    VertexBuffer m_SphereODFMapVBO;
    VertexArray m_vao;
    IndexBuffer m_idxBuffer;
    Shader m_program;

    int m_verticesSize;

    float     m_shineness;

    size_t m_ODFsize;

    unsigned int m_InstancesCount;

    bool m_initialized;
    bool m_attributesFlag;

    int m_slot;

    ODFSamples * m_ODFListRef;
    Texture m_ODFMapTexture;

    glm::mat4 m_projectionMatrix;
    glm::mat4 m_mvMatrix;
    glm::mat4 m_mvpMatrix;

public:
    ODFRendererInstanced();
    virtual ~ODFRendererInstanced();
    void addGlyph(const std::vector<float> &ODFList, glm::vec3 center, glm::vec3 axis = glm::vec3(0.0f,1.0f,0.0f), float scale = 1.0f);
    void addThreeAngleGlyph(const std::vector<float> &ODFList, float scale = 1.0f);
//    void addSphere(float r = 0.5, glm::vec3 center = glm::vec3(0.0f));


    virtual void initialize(ODFSamples* odfSamples);
    virtual void render(const std::vector<unsigned int>& odfIndexSet);
    virtual void render(const std::vector<unsigned int>& odfIndexSet, unsigned int window_width, unsigned int window_height){};
    virtual void getRenderingInfo(unsigned int* onScreenGlyphs, unsigned int* glyphResolution,unsigned int *maxPixels){};




    void setProjectionMatrix(glm::mat4 projectionMatrix);
    void setMVMatrix(glm::mat4 mvMatrix);

    void instantDrawGlyphs();

protected:
    virtual void setVaoLayout();
    virtual void setSphereSurface();
//    void updateODFMapTexture();

    virtual void setInstancedVertexAttribBuffer(const std::vector<unsigned int>& odfIndexSet);

};


#endif // ODFRENDERERINSTANCED_H
