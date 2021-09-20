#include "ODFRendererMultiResolution.h"

ODFRendererMultiResolution::ODFRendererMultiResolution(): m_instancedParametersUploaded(false)
{

}


ODFRendererMultiResolution::MeshProperty_t *ODFRendererMultiResolution::getGlyphsMesh(unsigned int maxPixels)
{
    if ( maxPixels < m_meshProperty[0].maxPixels || m_meshProperty.size() == 1 ) {
//        if(&m_meshProperty[0]!= m_currentMeshProperties && m_currentMeshProperties!=nullptr  ) {
//            std::cout << "Mesh changed! " << m_currentMeshProperties->verticesAmount << " to " << m_meshProperty[0].verticesAmount << std::endl;
//        }
        return &m_meshProperty[0];
    }

    for ( size_t i = 0; i < m_meshProperty.size() - 1; i++ ) {
               if ( maxPixels < m_meshProperty[i].maxPixels  ) {
//                   if( &m_meshProperty[i]!= m_currentMeshProperties && m_currentMeshProperties!=nullptr ) {
//                       std::cout << "Mesh changed! " << m_currentMeshProperties->verticesAmount << " to " << m_meshProperty[i].verticesAmount << std::endl;
//                   }
                return &m_meshProperty[i];
            }
        }

//      if( &m_meshProperty[m_meshProperty.size()-1]!=m_currentMeshProperties && m_currentMeshProperties!=nullptr ) {
//          std::cout << "Mesh changed! " << m_currentMeshProperties->verticesAmount << " to " << m_meshProperty[m_meshProperty.size()-1].verticesAmount << std::endl;
//      }
      return &m_meshProperty[m_meshProperty.size()-1];

}

void ODFRendererMultiResolution::setMeshUsageTable(const ODFSamples *qBall)
{
    const size_t meshAmount = qBall->getIndexBufferSetSize();


//    GLuint * tempIdxBuffer = new GLuint[meshAmount];
    m_meshProperty.resize(meshAmount);

    std::cout << "Starting Mesh properties" << std::endl;

//    glGenBuffers(meshAmount,tempIdxBuffer);
    for ( size_t i = 0; i < meshAmount; i++ ) {
        const std::vector<unsigned int> tempIdxBuffer = qBall->getIndexBuffer(i);
        //m_meshProperty[i].idxBufferID = tempIdxBuffer[i];
        m_meshProperty[i].idxBufferSize = tempIdxBuffer.size();
        m_meshProperty[i].idxBufferID.updateBufferData(tempIdxBuffer.data(), tempIdxBuffer.size());
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_meshProperty[i].idxBufferID);
//        glBufferData(GL_ELEMENT_ARRAY_BUFFER, tempIdxBuffer.size()*sizeof(unsigned int), tempIdxBuffer.data(), GL_STATIC_DRAW);

        m_meshProperty[i].verticesAmount = qBall->getMeshSubsetVerticesAmount(i);
//        m_meshProperty[i].maxPixels = (tempIdxBuffer.size()/24)*(tempIdxBuffer.size()/24); //Taken from the expression delta = (#triangles/8)²
        m_meshProperty[i].maxPixels = (unsigned int) ( (25.0f/4.0f) * ( powf(4.f,float(i)) -1 )*( powf(4.f,float(i)) -1 ) );

    std::cout << "(idxBuffer, vertices, MaxPixels, idxBufferSize) = " << m_meshProperty[i].idxBufferID.iboID() << ", "
                                                                 << m_meshProperty[i].verticesAmount << ", "
                                                                 << m_meshProperty[i].maxPixels << ", "
                                                                 << m_meshProperty[i].idxBufferSize

              << std::endl;
    }
//    delete[] tempIdxBuffer;

}



void ODFRendererMultiResolution::initialize(ODFSamples *odfSamples)
{
    m_InstancesCount = odfSamples->getInstancesAmount();
    m_ODFListRef = odfSamples;
    if(!m_initialized) {
        m_initialized = true;
        m_program.loadProgramQt(":/renderODFVisibilityMultiRes_vert",":/renderODFVisibilityMultiRes_frag");
        m_program.useProgram();

        m_cols = odfSamples->m_cols;
        m_rows = odfSamples->m_rows;

        m_SphereAttributesVBO.genBuffer();
        m_SphereVBO.genBuffer();
        m_coordsIndexesVBO.genBuffer();
        m_idxBuffer.genBuffer();

        setVaoLayout();
        setSphereSurface(); //this method assign the m_SphereVBO buffer with a unitary sphere

        float scale = m_ODFListRef->getScale();
        int scaleLoc = m_program.getUniformLocation("u_scale");
        int colsLoc = m_program.getUniformLocation("u_cols");
        glUniform1f(scaleLoc, scale);
        glUniform1ui(colsLoc, m_cols);


        setProjectionMatrix(glm::mat4(1.0f));
        setMVMatrix(glm::mat4(1.0f));
        setMeshUsageTable(odfSamples);



        m_program.release();
    }
}

void ODFRendererMultiResolution::render(const std::vector<unsigned int> &odfIndexSet, unsigned int window_width, unsigned int window_height)
{
    if(!m_instancedParametersUploaded) {
        setInstancedVertexAttribBuffer(odfIndexSet);
        m_instancedParametersUploaded = true;
    }
    m_program.useProgram();
    m_vao.bind();
    glm::mat4 inversePrjMat = glm::inverse(m_mvpMatrix);
    glm::vec4 viewLowerLeftH  = inversePrjMat * glm::vec4( -1.0, -1.0, 2.0  - 1.0, 1.0);
    glm::vec4 viewUpperRightH = inversePrjMat * glm::vec4(  1.0,  1.0, 2.0 - 1.0, 1.0);
    glm::vec3 viewLowerLeft   = glm::vec3(viewLowerLeftH) / glm::vec3(viewLowerLeftH.w);
    glm::vec3 viewUpperRight  = glm::vec3(viewUpperRightH) / glm::vec3(viewUpperRightH.w);
//    std::cout << glm::to_string(viewLowerLeft) << std::endl;
//    std::cout << glm::to_string(viewUpperRight)  << std::endl;
//    std::cout << std::endl;
    std::vector<unsigned int> visibleIndexes = visibilityDetector(odfIndexSet, viewLowerLeftH, viewUpperRightH);

//    std::cout << "*****" << std::endl;
//    for(auto & visible : visibleIndexes) {
////        visible = 3;
//        std::cout << visible << std::endl;
//    }

    std::cout << "Tamanho: " << visibleIndexes.size() << std::endl;
    std::cout << "*****" << std::endl;

    m_coordsIndexesVBO.updateBufferData(visibleIndexes.data(), visibleIndexes.size()*sizeof(unsigned int));
    unsigned int m_currentMaxP = window_width*window_height*fabs(m_mvpMatrix[0][0])/odfIndexSet.size();
    m_currentMeshProperties = getGlyphsMesh(m_currentMaxP);
    m_currentMeshProperties->idxBufferID.bind();

    m_ODFMapTexture.Bind(m_slot);
    glUniform1i(m_program.getUniformLocation("u_ODFMap"), m_slot);

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
#ifdef QT_DEBUG
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
#endif
     glDrawElementsInstanced(GL_TRIANGLES, m_currentMeshProperties->idxBufferSize,  GL_UNSIGNED_INT, nullptr, visibleIndexes.size());

//    glDisable(GL_DEPTH_TEST);
#ifdef QT_DEBUG
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
#endif
    glDisable(GL_CULL_FACE);

    m_idxBuffer.unbind();
    m_vao.unbind();
    m_program.release();

    std::cout <<
//                 "maxP:" << m_currentMaxP << std::endl <<
//                 "Triangles: " << m_currentMeshProperties->idxBufferSize/3 << std::endl <<
////                  "IDXBuffer: " << m_currentMeshProperties->idxBufferID.iboID() << std::endl <<
                 "zoom: " << m_mvpMatrix[0][0] <<
                 std::endl;


}

void ODFRendererMultiResolution::setInstancedVertexAttribBuffer(const std::vector<unsigned int> &odfIndexSet)
{
    m_program.useProgram();
    std::cout << "Instanced Buffers!" << std::endl;
    //    Timer T(__FUNCTION__);

        std::vector<glm::vec3> currentReorientMatrixSet;
        std::vector<float> currentODFListSet;
    //    currentReorientMatrixSet.reserve(m_pts_from_tex_coord.m_num_points);
    //    currentODFListSet.reserve(m_pts_from_tex_coord.m_num_points*m_ODFsize);


        currentReorientMatrixSet.resize(odfIndexSet.size());
        const unsigned int  hemisphereVecSize = m_ODFsize/2 + (4 - (m_ODFsize/2)%4);

        currentODFListSet.resize(odfIndexSet.size()*hemisphereVecSize);

    #pragma omp parallel
        for( size_t i = 0; i < odfIndexSet.size(); i++ ) {

            float* currentVoxelAttributes = m_ODFListRef->getVoxelODF(odfIndexSet[i]);
            int currentODFIndex = 0;
            for(size_t j = 0; j< m_ODFsize/2;j++) {
               currentODFListSet[i*hemisphereVecSize + j] = currentVoxelAttributes[currentODFIndex++];
            }
            currentReorientMatrixSet[i] = m_ODFListRef->getVoxelDisplacementVec3(odfIndexSet[i]);
         }
        m_ODFMapTexture.uploadTextureRGBA(currentODFListSet, hemisphereVecSize/4, odfIndexSet.size());
        glUniform1i(m_program.getUniformLocation("u_ODFMap"), m_slot);
        m_ODFMapTexture.Bind(m_slot);
//        m_ODFMapTexture.Unbind();

        m_SphereAttributesVBO.updateBufferData(currentReorientMatrixSet.data(), currentReorientMatrixSet.size()*sizeof(glm::vec3));

}

std::vector<unsigned int> ODFRendererMultiResolution::visibilityDetector(const std::vector<unsigned int>& inputIndex, glm::vec3 viewLowerLeft, glm::vec3 viewUpperRight)
{
    std::vector<unsigned int> visibleIndexes;
    visibleIndexes.reserve(inputIndex.size());
    const float factorSumX = -1.f + 1.f/(float(m_cols));
    const float factorSumY = 1.f - 1.f/(float(m_rows));
    const float factorScaleX = 2.f/(float(m_cols));
    const float factorScaleY = -2.f/(float(m_rows));
    const float partialAppearanceThrX = 1.f/float(m_cols);
    const float partialAppearanceThrY = 1.f/float(m_rows);

    size_t currentPosition = 0;
    const float lowThrX = min(viewLowerLeft.x, viewUpperRight.x);
    const float highThrX = max(viewLowerLeft.x, viewUpperRight.x);
    const float lowThrY = min(viewLowerLeft.y, viewUpperRight.y);
    const float highThrY = max(viewLowerLeft.y, viewUpperRight.y);
    for (auto & index : inputIndex) {
        const unsigned int i = index%m_cols;
        const unsigned int j = index/m_cols;
//        std::cout << factorScaleX*float(i) + factorSumX << ", " <<  factorScaleY*float(j) + factorSumY << std::endl;
        if(  (factorScaleX*float(i) + factorSumX + partialAppearanceThrX > lowThrX  &&
             factorScaleX*float(i) + factorSumX - partialAppearanceThrX < highThrX &&
             factorScaleY*float(j) + factorSumY + partialAppearanceThrY > lowThrY  &&
             factorScaleY*float(j) + factorSumY - partialAppearanceThrY < highThrY)
          ) {
            visibleIndexes.emplace_back(index);

        }
    }
    return visibleIndexes;
}


void ODFRendererMultiResolution::setVaoLayout()
{

    int locVertex = m_program.getAttribLocation("vertex");
    _check_gl_error(__FILE__,__LINE__);
//    int locNormal = m_program.getAttribLocation("normal");

    m_vao.bind();
    _check_gl_error(__FILE__,__LINE__);

    m_vao.push<float>(locVertex, 3);
    m_vao.addBuffer(m_SphereVBO);
    _check_gl_error(__FILE__,__LINE__);
    m_vao.clearLayout(); //Clearing to support other buffer, that has the Center/Radius instanced parameters.




//    int locDisplacement = m_program.getAttribLocation("instance_displacement");



//    m_vao.push<float>(locDisplacement,     3, GL_FALSE, VertexArray::INSTANTIATION_MODE::INSTANCED, 1);


//    m_vao.push<float>(locDisplacement,   4, GL_FALSE, VertexArray::INSTANTIATION_MODE::INSTANCED, 1);
//    m_vao.push<float>(locDisplacement+1, 4, GL_FALSE, VertexArray::INSTANTIATION_MODE::INSTANCED, 1);
//    m_vao.push<float>(locDisplacement+2, 4, GL_FALSE, VertexArray::INSTANTIATION_MODE::INSTANCED, 1);
//    m_vao.push<float>(locDisplacement+3, 4, GL_FALSE, VertexArray::INSTANTIATION_MODE::INSTANCED, 1);
    _check_gl_error(__FILE__,__LINE__);

//    m_vao.addBuffer(m_SphereAttributesVBO);
//    m_vao.clearLayout();
    int locIndex = m_program.getAttribLocation("instance_index");
    _check_gl_error(__FILE__,__LINE__);
    m_vao.push<unsigned int>(locIndex, 1, GL_FALSE, VertexArray::INSTANTIATION_MODE::INSTANCED, 1);
    m_vao.addBuffer(m_coordsIndexesVBO);
    m_vao.clearLayout();
    _check_gl_error(__FILE__,__LINE__);
}
