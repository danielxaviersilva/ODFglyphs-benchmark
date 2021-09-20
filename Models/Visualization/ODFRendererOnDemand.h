#ifndef ODFRENDERERONDEMAND_H
#define ODFRENDERERONDEMAND_H
#include <iostream>
#include <vector>
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
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

#define min(a,b) a<b?a:b
#define max(a,b) a>b?a:b


class ODFRendererOnDemand: public ODFRendererInstanced
{
public:
    ODFRendererOnDemand();

    typedef struct mesh_property
        {
           IndexBuffer idxBufferID;
           unsigned int verticesAmount;
           unsigned int maxPixels;
           unsigned int idxBufferSize;

            mesh_property()
            {
                idxBufferID;
                idxBufferSize = 0;
                verticesAmount = 0;
                maxPixels = 0;
            }

        } MeshProperty_t;

        std::vector<MeshProperty_t> m_meshProperty;
        MeshProperty_t * m_currentMeshProperties;

        MeshProperty_t *getGlyphsMesh(unsigned int maxPixels);
        void setMeshUsageTable(const ODFSamples * qBall);

    // ODFRendererInstanced interface
public:
    void initialize(ODFSamples *odfSamples);
    void render(const std::vector<unsigned int> &odfIndexSet, unsigned int window_width, unsigned int window_height);
    // ODFRendererInstanced interface
protected:
    void setInstancedVertexAttribBuffer(const std::vector<unsigned int> &odfIndexSet);
    unsigned int m_cols, m_rows, m_currentODFSamplesDemand;

    bool m_instancedParametersUploaded;
    unsigned int m_currentMaxP;
    unsigned int m_currentGlyphNumber;
    std::vector<unsigned int> visibilityDetector(const std::vector<unsigned int> &inputIndex, glm::vec3 viewLowerLeft, glm::vec3 viewUpperRight);
    VertexBuffer m_coordsIndexesVBO;

    // ODFRendererInstanced interface
protected:
    void setVaoLayout();

    // ODFRendererInstanced interface
public:
    void getRenderingInfo(unsigned int *onScreenGlyphs, unsigned int *glyphResolution, unsigned int *maxPixels);
};



#endif // ODFRENDERERONDEMAND_H
