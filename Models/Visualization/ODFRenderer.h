/**
 * @file ODFRenderer.h
 *
 * @brief Prototype 1 for rendering glyphs benchmarking: indexing
 *
 * @author Daniel Xavier Silva
 * Contact: danielxaviers@gmail.com
 *
 */

#ifndef ODFRENDERER_H
#define ODFRENDERER_H
#include <iostream>
#include <vector>
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
//#include <OpenGL.h>
#include <QGLFunctions>
//#include <GL/glew.h>
#include "../../Utilities/VertexArray.h"
#include "../../Utilities/VertexBuffer.h"
#include "../../Utilities/IndexBuffer.h"
#include "../../Utilities/Shader.h"
#include "../../Utilities/CGUtilities.h"
#include "../../Utilities/Texture.h"

#include "ODFRendererInstanced.h"


class ODFRenderer : public ODFRendererInstanced
{
public:
    ODFRenderer();

    // QBallRenderer interface
public:
    void initialize(ODFSamples *odfSamples);
    void render(const std::vector<unsigned int> &odfIndexSet);

protected:
    void setVertexAttribBuffer(const std::vector<unsigned int> &odfIndexSet);
    std::vector <glm::vec3> m_sphereAttributesBuffer;
    std::vector<unsigned int> m_idxSetBase;

    // QBallRenderer interface
protected:
    void setVaoLayout();
    void setSphereSurface();
};

#endif // ODFRENDERER_H
