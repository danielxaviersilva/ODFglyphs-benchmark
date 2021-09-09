/**
 * @file ODFRendererInstanced.h
 *
 * @brief Prototype 3 for rendering glyphs benchmarking: indexing, Instance rendering, symmetry
 *
 * @author Daniel Xavier Silva
 * Contact: danielxaviers@gmail.com
 *
 */

#ifndef ODFRENDERERINSTANCEDSYMMETRIC_H
#define ODFRENDERERINSTANCEDSYMMETRIC_H
#include <iostream>
#include <vector>
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
//#include <OpenGL.h>
//#include <QGLFunctions>
//#include <GL/glew.h>
#include "../../Utilities/VertexArray.h"
#include "../../Utilities/VertexBuffer.h"
#include "../../Utilities/IndexBuffer.h"
#include "../../Utilities/Shader.h"
#include "../../Utilities/CGUtilities.h"
#include "../../Utilities/Texture.h"

#include "ODFRendererInstanced.h"


class ODFRendererInstancedSymmetric: public ODFRendererInstanced
{
public:
    ODFRendererInstancedSymmetric();


    // QBallRenderer interface
public:
    void initialize(ODFSamples *odfSamples) override;
    void render(const std::vector<unsigned int>& odfIndexSet) override;

protected:
    void setInstancedVertexAttribBuffer(const std::vector<unsigned int>& odfIndexSet) override;
};

#endif // ODFRENDERERINSTANCEDSYMMETRIC_H
