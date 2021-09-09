/**
 * @file ODFRendererInstanced.h
 *
 * @brief Prototype 4 for rendering glyphs benchmarking: indexing, Instance rendering,
 * symmetry, coalescent lookup
 *
 * @author Daniel Xavier Silva
 * Contact: danielxaviers@gmail.com
 *
 */


#ifndef ODFRENDERERINSTANCEDSYMMETRICCOALESCENT_H
#define ODFRENDERERINSTANCEDSYMMETRICCOALESCENT_H
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


class ODFRendererInstancedSymmetricCoalescent: public ODFRendererInstanced
{
public:
    ODFRendererInstancedSymmetricCoalescent();

    // QBallRenderer interface
public:
    void initialize(ODFSamples *odfSamples);
    void render(const std::vector<unsigned int> &odfIndexSet);

protected:
    void setInstancedVertexAttribBuffer(const std::vector<unsigned int> &odfIndexSet);
};



#endif // ODFRENDERERINSTANCEDSYMMETRICCOALESCENT_H
