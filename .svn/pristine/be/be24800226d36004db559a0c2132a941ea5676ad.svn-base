#include "ODFRenderer.h"
#include <glm/gtx/string_cast.hpp>

#include <QFile>
//#include <QString>
//#include <QDebug>
//#include <QTextStream>
//#include <QResource>
//#include <QIODevice>


ODFRenderer::ODFRenderer()
{

}

void ODFRenderer::initialize(ODFSamples *odfSamples)
{
    m_InstancesCount = odfSamples->getInstancesAmount();
    m_ODFListRef = odfSamples;
    if(!m_initialized) {
        m_initialized = true;

        m_program.loadProgramQt(":/renderODF_vert",":/renderODF_frag");
        m_program.useProgram();

        m_SphereAttributesVBO.genBuffer();
        m_SphereVBO.genBuffer();
        m_idxBuffer.genBuffer();

        setVaoLayout();
        setSphereSurface(); //this method assign the m_SphereVBO buffer with a unitary sphere

        float scale = m_ODFListRef->getScale();
        int scaleLoc = m_program.getUniformLocation("u_scale");

//        std::cout << scale << std::endl;
        glUniform1f(scaleLoc, scale);

        setProjectionMatrix(glm::mat4(1.0f));
        setMVMatrix(glm::mat4(1.0f));

        m_program.release();
    }
}

void ODFRenderer::render(const std::vector<unsigned int> &odfIndexSet)
{
    if (!m_initialized) {
        std::cerr << "SphereODF.render(): not rendering because not initialized yet. Use method initialize()" << std::endl;
        return;
    }

    m_program.useProgram();
    m_vao.bind();

    setVertexAttribBuffer(odfIndexSet);
    m_idxBuffer.bind();
//    glUniform1i(m_program.getUniformLocation("u_ODFMap"), m_slot);
//    m_ODFMapTexture.Bind(m_slot);

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    #ifndef QT_NO_DEBUG
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    #endif
    glDrawElements(GL_TRIANGLES, m_idxSetBase.size()*odfIndexSet.size(), GL_UNSIGNED_INT, nullptr);
    _check_gl_error(__FILE__,__LINE__);

//    glDisable(GL_DEPTH_TEST);
#ifndef QT_NO_DEBUG
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
#endif
//    glDisable(GL_CULL_FACE);

    m_ODFMapTexture.deleteTexture();
    m_idxBuffer.unbind();
    m_vao.unbind();
    m_program.release();
}

void ODFRenderer::setVertexAttribBuffer(const std::vector<unsigned int> &odfIndexSet)
{
    //    Timer T(__FUNCTION__);

        std::vector<glm::vec3> currentVertexAttribute;
        std::vector<glm::vec3> currentTranslationAttribute;
        std::vector<unsigned int> currentIndexSet;

   currentVertexAttribute.resize(odfIndexSet.size()*m_sphereAttributesBuffer.size());
   currentTranslationAttribute.resize(odfIndexSet.size()*m_sphereAttributesBuffer.size());
   currentIndexSet.resize(m_idxSetBase.size()*odfIndexSet.size());

    #pragma omp parallel
    for(size_t i = 0; i < odfIndexSet.size(); i++) {
        float* currentVoxelAttributes = m_ODFListRef->getVoxelODF(odfIndexSet[i]);

        int currentODFIndex = 0;
        for(size_t j = 0; j< m_ODFsize;j++) {
           currentVertexAttribute[i*m_ODFsize + j] = currentVoxelAttributes[j]*m_sphereAttributesBuffer[j];
           currentTranslationAttribute[i*m_ODFsize + j] = m_ODFListRef->getVoxelDisplacementVec3(odfIndexSet[i]);
        }
        for (size_t j = 0; j < m_idxSetBase.size(); j++) {
            currentIndexSet[i*m_idxSetBase.size() + j] = m_idxSetBase[j] + i*m_ODFsize;
        }
    }
//    for (auto &i : currentIndexSet)
//        std::cout << i << std::endl;
    m_SphereVBO.updateBufferData(currentVertexAttribute.data(), currentVertexAttribute.size()*sizeof(glm::vec3));
    m_SphereAttributesVBO.updateBufferData(currentTranslationAttribute.data(), currentTranslationAttribute.size()*sizeof(glm::vec3));
    m_idxBuffer.updateBufferData(currentIndexSet.data(), currentIndexSet.size());
        _check_gl_error(__FILE__,__LINE__);
}

void ODFRenderer::setVaoLayout()
{
    int locVertex = m_program.getAttribLocation("vertex");
    _check_gl_error(__FILE__,__LINE__);
//    int locNormal = m_program.getAttribLocation("normal");

    m_vao.bind();
    _check_gl_error(__FILE__,__LINE__);

    m_vao.push<float>(locVertex, 3);
//    m_vao.push<float>(locNormal, 4);
//    m_vao.push<float>(-1, 2); //Reserved for texture, which is not being used
    m_vao.addBuffer(m_SphereVBO);
    _check_gl_error(__FILE__,__LINE__);
    m_vao.clearLayout(); //Clearing to support other buffer, that has the Center/Radius instanced parameters.

    int locDisplacement = m_program.getAttribLocation("displacement");
    _check_gl_error(__FILE__,__LINE__);



    m_vao.push<float>(locDisplacement, 3);
    _check_gl_error(__FILE__,__LINE__);

    m_vao.addBuffer(m_SphereAttributesVBO);
    m_vao.clearLayout();
    _check_gl_error(__FILE__,__LINE__);

}

void ODFRenderer::setSphereSurface()
{
    m_sphereAttributesBuffer = m_ODFListRef->getBaseDirections();
    m_idxSetBase =           m_ODFListRef->getIndexBuffer();
    m_ODFsize = m_sphereAttributesBuffer.size();

//    std::cout << "Sphere" << std::endl;
//    for (auto &s : m_sphereAttributesBuffer)
//        std::cout << glm::to_string(s) << std::endl;

//    for (auto &i : m_idxSetBase)
//        std::cout << i << std::endl;
}

