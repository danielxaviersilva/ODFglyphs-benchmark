#include "ODFSamples.h"
#include <glm/gtx/string_cast.hpp>
//#include <fstream>
#include <complex>
#include <omp.h>
#include<iostream>
#include<QBallGlyphsCoefficientsSample.h>


using namespace std::chrono;

int ODFSamples::getInstancesAmount() const
{
    return m_instancesAmount;
}

float ODFSamples::getScale() const
{
    return m_scale;
}

ODFSamples::ODFSamples(int instancesAmount, int icoIterations):
    m_instancesAmount(instancesAmount)
{

//    bool isIco = true;

//      if(isIco) {
        generateIcoCoordsMeshSphere(icoIterations);
//      } else {
//          generateUVCoordsMeshSphere(thetaRes, phiRes);
//      }
      computeTranslationMatrices(m_instancesAmount);
}

ODFSamples::~ODFSamples()
{
    for (int i = 0; i < m_instancesAmount; i++)
        delete[] m_ODF[i];
    delete[] m_ODF;

    delete [] m_translateMatrix;
    delete [] m_translateVector;
}

void ODFSamples::computeODFs()
{

    m_ODF = new float*[m_instancesAmount];

#pragma omp parallel for
    for (int idx = 0; idx < m_instancesAmount; idx++)
    {
        float * psi = new float[m_baseDirections.size()];
        for (size_t i = 0; i < m_baseDirections.size(); i++) {
            const float r = sqrt(m_baseDirections[i].x*m_baseDirections[i].x +
                                 m_baseDirections[i].y*m_baseDirections[i].y +
                                 m_baseDirections[i].z*m_baseDirections[i].z);
            const float theta = acos(m_baseDirections[i].z/r);
            const float phi = atan2( m_baseDirections[i].y, m_baseDirections[i].x);

            float SH;

            if(idx%10 == 0) {
                auto temp = std::complex<float>(std::polar(1.f, -phi))*sin(theta);
                SH = 0.5*std::sqrtf(3/(2*M_PI))*std::real(temp);
            } else if(idx%10 == 1) {
                SH = 0.5*std::sqrtf(3/(M_PI))*(cos(theta));
            } else if(idx%10 == 2) {
                auto temp = std::complex<float>(std::polar(1.f, -phi))*sin(theta);
                SH = -0.5*std::sqrtf(3/(2*M_PI))*std::imag(temp);
            } else if(idx%10 == 3) {
                auto temp = std::complex<float>(std::polar(1.f, -2*phi))*sin(theta)*sin(theta);
                SH = 0.25*std::sqrtf(15/(2*M_PI))*std::real(temp);
            } else if(idx%10 == 4) {
                auto temp = std::complex<float>(std::polar(1.f, -2*phi))*sin(theta)*sin(theta);
                SH = 0.25*std::sqrtf(15/(2*M_PI))*std::imag(temp);
            } else if(idx%10 == 5) {
                auto temp = std::complex<float>(std::polar(1.f, -phi))*sin(theta)*cos(theta);
                SH = 0.5*std::sqrtf(15/(2*M_PI))*std::real(temp);
            }
            else if(idx%10 == 6) {
                auto temp = std::complex<float>(std::polar(1.f, -phi))*sin(theta)*cos(theta);
                SH = 0.5*std::sqrtf(15/(2*M_PI))*std::imag(temp);
            } else if(idx%10 == 7) {
                auto temp = 3*cos(theta)*cos(theta) -1;
                SH = -0.25*std::sqrtf(5/(M_PI))*std::abs(temp);
            } else if(idx%10 == 8) {
                auto temp = std::complex<float>(std::polar(1.f, -phi))*sin(theta);
                SH = 1.0f;
            } else if(idx%10 == 9) {
                auto temp = 5*cos(theta)*cos(theta)*cos(theta) - 3*cos(theta);
                SH = 0.25*std::sqrtf(7/(M_PI))*std::abs(temp);
            }

            psi[i] = abs(SH);
        }
        MinMaxNormalizePsi(psi, m_baseDirections.size());
        m_ODF[idx] = psi;
    }
}

void ODFSamples::computeTranslationMatrices(const unsigned int& instancesAmount)
{
    int cols = (int) sqrt(instancesAmount);
    m_translateVector = new glm::vec3[cols*cols];
    m_translateMatrix = new glm::mat4[cols*cols];

    std::vector<float> borderMeshX;
    std::vector<float> borderMeshY;
    std::vector<glm::vec2> centerSet;

    for(float i = -1; i <= 1.01; i+=(2.f/float(cols)))
        borderMeshX.push_back(i);

    for(float j = 1; j >= -1.01; j-=2.f/float(cols))
        borderMeshY.push_back(j);

    int idx = 0;
    for(int j = 0; j < cols; j++)
        for(int i = 0; i < cols; i++) {
             m_translateVector[idx] =  glm::vec3(0.5f*(borderMeshX[i] + borderMeshX[i+1]),
                     0.5f*(borderMeshY[j] + borderMeshY[j+1]), 0.0f);
            m_translateMatrix[idx] = glm::translate(glm::mat4(1.0f),
                                                      glm::vec3(0.5f*(borderMeshX[i] + borderMeshX[i+1]),
                                                             0.5f*(borderMeshY[j] + borderMeshY[j+1]),
                                                             0.0f));
            idx++;

        }

    m_scale = 1.0f/((float)cols);

}

float *ODFSamples::getVoxelODF(int index)
{
    return m_ODF[index];
}


std::vector<unsigned int> ODFSamples::getIndexBuffer() const
{
    return m_indexBuffer;
}

std::vector<glm::vec3> ODFSamples::getBaseDirections() const
{
    return m_baseDirections;
}

glm::mat4 ODFSamples::getVoxelDisplacement(int index)
{
    return m_translateMatrix[index];
}

glm::vec3 ODFSamples::getVoxelDisplacementVec3(int index)
{
    return m_translateVector[index];
}

void ODFSamples::generateIcoCoordsMeshSphere(const unsigned int meshIterations)
{
    {
        const float t = (1.0 + std::sqrt(5.0)) / 2.0;
        m_baseDirections.push_back(glm::normalize(glm::vec3(-1.0,  t, 0.0)));
        m_baseDirections.push_back(glm::normalize(glm::vec3( 1.0,  t, 0.0)));
        m_baseDirections.push_back(glm::normalize(glm::vec3(-1.0, -t, 0.0)));
        m_baseDirections.push_back(glm::normalize(glm::vec3( 1.0, -t, 0.0)));
        m_baseDirections.push_back(glm::normalize(glm::vec3( 0.0, -1.0,  t)));
        m_baseDirections.push_back(glm::normalize(glm::vec3( 0.0,  1.0,  t)));
        m_baseDirections.push_back(glm::normalize(glm::vec3( 0.0, -1.0, -t)));
        m_baseDirections.push_back(glm::normalize(glm::vec3( 0.0,  1.0, -t)));
        m_baseDirections.push_back(glm::normalize(glm::vec3(   t, 0.0, -1.0)));
        m_baseDirections.push_back(glm::normalize(glm::vec3(   t, 0.0,  1.0)));
        m_baseDirections.push_back(glm::normalize(glm::vec3(  -t, 0.0, -1.0)));
        m_baseDirections.push_back(glm::normalize(glm::vec3(  -t, 0.0,  1.0)));

        m_indexBuffer = {0,11,5,0,5,1,
                         0,1,7,0,7,10,
                         0,10,11,1,5,9,
                         5,11,4,11,10,2,
                         10,7,6,7,1,8,
                         3,9,4,3,4,2,
                         3,2,6,3,6,8,
                         3,8,9,4,9,5,
                         2,4,11,6,2,10,
                         8,6,7,9,8,1};


//        std::cout << "idxBufferSize/3 (#triangles): " << m_indexBuffer.size()/3 << std::endl;
//        std::cout << "vertexListSize: " << m_baseDirections.size() << std::endl << std::endl;
        AlignEvenMesh(m_baseDirections, m_indexBuffer);
        shrinkVec3(m_baseDirections, m_indexBuffer, true);
        AlignEvenMesh(m_baseDirections, m_indexBuffer);

        for (unsigned int it = 0; it < meshIterations; it++){
            unsigned int currentVertexIdx = m_baseDirections.size();
                std::vector<unsigned int> idxAux;// = m_indexBuffer;
                for (uint32_t i = 0; i < m_indexBuffer.size()/3; ++i) {
                    const uint32_t f0 = m_indexBuffer[i * 3];
                    const uint32_t f1 = m_indexBuffer[i * 3 + 1];
                    const uint32_t f2 = m_indexBuffer[i * 3 + 2];

                    const glm::vec3 v0 = glm::vec3(m_baseDirections[f0]);
                    const glm::vec3 v1 = glm::vec3(m_baseDirections[f1]);
                    const glm::vec3 v2 = glm::vec3(m_baseDirections[f2]);


                    const glm::vec3 v01 = glm::normalize(0.5f*(v0 + v1));
                    const glm::vec3 v12 = glm::normalize(0.5f*(v1 + v2));
                    const glm::vec3 v20 = glm::normalize(0.5f*(v2 + v0));



    //                std::cout << i << " Triangulo: " << std::endl;
    //                std::cout << "Geradores: " << std::endl;
    //                std::cout << glm::to_string(v0) << std::endl;
    //                std::cout << glm::to_string(v1) << std::endl;
    //                std::cout << glm::to_string(v2) << std::endl;
    //                std::cout << std::endl;
    //                std::cout << "Triangulos gerados: " << std::endl;
    //                std::cout << glm::to_string(v01) << std::endl;
    //                std::cout << glm::to_string(v12) << std::endl;
    //                std::cout << glm::to_string(v20) << std::endl;


                    m_baseDirections.push_back(v01);
                    m_baseDirections.push_back(v12);
                    m_baseDirections.push_back(v20);

                    idxAux.push_back(f0);
                    idxAux.push_back(currentVertexIdx);
                    idxAux.push_back(currentVertexIdx+2);

                    idxAux.push_back(currentVertexIdx);
                    idxAux.push_back(f1);
                    idxAux.push_back(currentVertexIdx+1);

                    idxAux.push_back(currentVertexIdx+1);
                    idxAux.push_back(f2);
                    idxAux.push_back(currentVertexIdx+2);

                    idxAux.push_back(currentVertexIdx);
                    idxAux.push_back(currentVertexIdx+1);
                    idxAux.push_back(currentVertexIdx+2);

                    currentVertexIdx+=3;
                }
                m_indexBuffer = idxAux;
                AlignEvenMesh(m_baseDirections, m_indexBuffer);
                shrinkVec3(m_baseDirections, m_indexBuffer);
                AlignEvenMesh(m_baseDirections, m_indexBuffer);
//                m_indexBufferSet[it+1].idxBuffer = m_indexBuffer;
//                m_indexBufferSet[it+1].verticesAmount = m_baseDirections.size();

//                std::cout << "idxBufferSize/3 (#triangles): " << m_indexBufferSet[it].idxBuffer.size()/3 << std::endl;
//                std::cout << "vertexListSize: " <<  m_indexBufferSet[it].verticesAmount << std::endl << std::endl;

            }

    }

}

void ODFSamples::generateIcoCoordsMeshSphere_OPT(const unsigned int meshIterations)
{
    {
        const float t = (1.0 + std::sqrt(5.0)) / 2.0;
        m_baseDirections.push_back(glm::normalize(glm::vec3(-1.0,  t, 0.0)));
        m_baseDirections.push_back(glm::normalize(glm::vec3( 1.0,  t, 0.0)));
        m_baseDirections.push_back(glm::normalize(glm::vec3(-1.0, -t, 0.0)));
        m_baseDirections.push_back(glm::normalize(glm::vec3( 1.0, -t, 0.0)));
        m_baseDirections.push_back(glm::normalize(glm::vec3( 0.0, -1.0,  t)));
        m_baseDirections.push_back(glm::normalize(glm::vec3( 0.0,  1.0,  t)));
        m_baseDirections.push_back(glm::normalize(glm::vec3( 0.0, -1.0, -t)));
        m_baseDirections.push_back(glm::normalize(glm::vec3( 0.0,  1.0, -t)));
        m_baseDirections.push_back(glm::normalize(glm::vec3(   t, 0.0, -1.0)));
        m_baseDirections.push_back(glm::normalize(glm::vec3(   t, 0.0,  1.0)));
        m_baseDirections.push_back(glm::normalize(glm::vec3(  -t, 0.0, -1.0)));
        m_baseDirections.push_back(glm::normalize(glm::vec3(  -t, 0.0,  1.0)));

        m_indexBuffer = {0,11,5,0,5,1,
                         0,1,7,0,7,10,
                         0,10,11,1,5,9,
                         5,11,4,11,10,2,
                         10,7,6,7,1,8,
                         3,9,4,3,4,2,
                         3,2,6,3,6,8,
                         3,8,9,4,9,5,
                         2,4,11,6,2,10,
                         8,6,7,9,8,1};


//        std::cout << "idxBufferSize/3 (#triangles): " << m_indexBuffer.size()/3 << std::endl;
//        std::cout << "vertexListSize: " << m_baseDirections.size() << std::endl << std::endl;
//        shrinkVec3(m_baseDirections, m_indexBuffer, true);
        AlignEvenMesh(m_baseDirections, m_indexBuffer);

        for (unsigned int it = 0; it < meshIterations; it++){
            std::vector<Edge_t> usedEdges;
               unsigned int currentVertexIdx = m_baseDirections.size();
               std::vector<unsigned int> idxAux;// = m_indexBuffer;
                for (uint32_t i = 0; i < m_indexBuffer.size()/3; ++i) {
                    const uint32_t f0 = m_indexBuffer[i * 3];
                    const uint32_t f1 = m_indexBuffer[i * 3 + 1];
                    const uint32_t f2 = m_indexBuffer[i * 3 + 2];

                    {
                        Edge_t currentEdge(f0, f1);
                        int currentEdgeIndex = getUsedEdgesIndex(currentEdge, usedEdges);
                        if ( currentEdgeIndex == -1 ) {
                            const glm::vec3 v0 = glm::vec3(m_baseDirections[f0]);
                            const glm::vec3 v1 = glm::vec3(m_baseDirections[f1]);
                            glm::vec3 v01_temp = 0.5f*(v0 + v1);
                            const glm::vec3 v01 = glm::normalize(v01_temp);
                            m_baseDirections.push_back(v01);
                            currentEdge.medianID = int(currentVertexIdx);
                            usedEdges.push_back(currentEdge);
                            currentVertexIdx++;
                        } else {



                        }

                    }

                    {
                        Edge_t currentEdge(f1, f2);
                        int currentEdgeIndex = getUsedEdgesIndex(currentEdge, usedEdges);
                        if ( currentEdgeIndex == -1 ) {
                            const glm::vec3 v0 = glm::vec3(m_baseDirections[f0]);
                            const glm::vec3 v1 = glm::vec3(m_baseDirections[f1]);
                            glm::vec3 v01_temp = 0.5f*(v0 + v1);
                            const glm::vec3 v01 = glm::normalize(v01_temp);
                            m_baseDirections.push_back(v01);
                            currentEdge.medianID = int(currentVertexIdx);
                            usedEdges.push_back(currentEdge);
                            currentVertexIdx++;
                        }

                    }



                    const glm::vec3 v2 = glm::vec3(m_baseDirections[f2]);

//                    currentEdge = Edge_t(f0, f1);
//                    isEdgeUsed = false;

//                    for (auto &edges : usedEdges) {
//                        if (edges.isEqual(currentEdge)) {
//                            isEdgeUsed = true;
//                            break;
//                        }
//                    }
//                    if (!isEdgeUsed) {

//                    }



//                    glm::vec3 v12_temp = 0.5f*(v1 + v2);
//                    const glm::vec3 v12 = glm::normalize(v12_temp);
//                    m_baseDirections.push_back(v12);


//                    glm::vec3 v20_temp = 0.5f*(v2 + v0);
//                    const glm::vec3 v20 = glm::normalize(v20_temp);
//                    m_baseDirections.push_back(v20);

//                    const glm::vec3 v01 = v01_temp;
//                    const glm::vec3 v12 = v12_temp;
//                    const glm::vec3 v20 = v20_temp;









                    idxAux.push_back(f0);
                    idxAux.push_back(currentVertexIdx);
                    idxAux.push_back(currentVertexIdx+2);

                    idxAux.push_back(currentVertexIdx);
                    idxAux.push_back(f1);
                    idxAux.push_back(currentVertexIdx+1);

                    idxAux.push_back(currentVertexIdx+1);
                    idxAux.push_back(f2);
                    idxAux.push_back(currentVertexIdx+2);

                    idxAux.push_back(currentVertexIdx);
                    idxAux.push_back(currentVertexIdx+1);
                    idxAux.push_back(currentVertexIdx+2);

                    currentVertexIdx+=3;
                }
//                std::cout << "Vertices: " <<  m_baseDirections.size() << std::endl;
//                std::cout << "IndexMax: " << *max_element(std::begin(idxAux), std::end(idxAux)) << std::endl;
                shrinkVec3(m_baseDirections,idxAux, false);
                AlignEvenMesh(m_baseDirections,idxAux);
//                std::cout << "Pós Redução: " << std::endl;
//                std::cout << "Vertices: " <<  m_baseDirections.size() << std::endl;
//                std::cout << "IndexMax: " << *max_element(std::begin(idxAux), std::end(idxAux)) << std::endl;
                m_indexBuffer = idxAux;
            }

    }

}

void ODFSamples::generateUVCoordsMeshSphere(const unsigned int thetaRes, const unsigned int phiRes)
{
    m_indexBuffer.reserve(6*thetaRes*(phiRes-1));

        for (unsigned int i = 0; i< phiRes; i++) {
            const float phi = M_PI/2 - M_PI*i/(phiRes-1);
            for (unsigned int j = 0; j< thetaRes; j++) {
                const float theta = 2*(M_PI)*j/(thetaRes);
                m_baseDirections.push_back(glm::vec3(
                                                    cos(phi)*cos(theta),
                                                     sin(phi),
                                                     cos(phi)*sin(theta)
                                                     ));


                if ( i < phiRes -1 ){
                      m_indexBuffer.emplace_back(i*thetaRes + j                   );
                      m_indexBuffer.emplace_back((i+1)*thetaRes + j               );
                      m_indexBuffer.emplace_back((i+1)*thetaRes + (j+1)%thetaRes);
                      m_indexBuffer.emplace_back(i*thetaRes + j                   );
                      m_indexBuffer.emplace_back((i+1)*thetaRes + (j+1)%thetaRes);
                      m_indexBuffer.emplace_back(i*thetaRes + (j+1)%thetaRes    );
                }
            }
        }
}

void inline ODFSamples::MinMaxNormalizePsi(float *psi, const int &size){
    std::vector<int> nonValidIdx;
    nonValidIdx.reserve(size);

    for (int idx = 0; idx < size; idx++)
        if(psi[idx] < 0.0f){
            psi[idx] = 0.0f;
            nonValidIdx.emplace_back(idx);
        }

    float minPsi = std::numeric_limits<float>::max();
    float maxPsi = std::numeric_limits<float>::min();
    for(int idx =0; idx < size; idx++){
        if(!std::count(nonValidIdx.begin(), nonValidIdx.end(), idx))  {
            if(psi[idx] > maxPsi)
                maxPsi = psi[idx];
            if(psi[idx] < minPsi)
                minPsi = psi[idx];
        }
    }
    if(abs(minPsi - maxPsi) < 0.00001) {
            for (int idx = 0; idx < size; idx++)
                psi[idx] = 1.0f;
            return;
        }

        for (int i = 0; i<size; i++)
            if(!std::count(nonValidIdx.begin(), nonValidIdx.end(), i))
                psi[i] = (psi[i] - minPsi)/(maxPsi - minPsi);



}

int ODFSamples::getUsedEdgesIndex(ODFSamples::Edge_t edge, std::vector<ODFSamples::Edge_t> &edgesSet)
{
    int idx = 0;
    for (auto &  edgeIdx : edgesSet) {
        if (edgeIdx.isEqual(edge)) {
            return idx;
        }
        idx++;
    }
    return -1;

}


