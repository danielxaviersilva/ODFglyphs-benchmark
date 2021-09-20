/**
 * @file ODFSamples.h
 *
 * @brief Generate and store synthetic data derived from spherical harmonics in the whole sphere.
 * The functions are: $Re(Y_1^{-1})$ $Re(Y_1^0)$ $Im(Y_1^{-1})$ $Re(Y_2^{-2})$ $Im(Y_2^{-2})$ $Re(Y_2^{-1})$ $Im(Y_2^{-1})$ $Y_2^0$ $Y_0^0$ and
 *  $Y_3^0$, where it is indexed in sequence and periodically by j mod 10.
 *
 * @author Daniel Xavier Silva
 * Contact: danielxaviers@gmail.com
 *
 */

#ifndef ODFSAMPLES_H
#define ODFSAMPLES_H

#include <glm/glm.hpp>
#include <vector>
#include <math.h>
#include <complex.h>
#include "../Utilities/CGUtilities.h"

class ODFSamples: protected CGUtilities
{
  public:
typedef struct EDGE_T {
    unsigned int e1;
    unsigned int e2;
    int medianID;

    EDGE_T(unsigned int e1_in = 0, unsigned int e2_in = 0, unsigned int medianID_in = -1){
        e1 = e1_in;
        e2 = e2_in;
        medianID = medianID_in;
    }

    bool isEqual(unsigned int e1_in, unsigned int e2_in) {
        if ( e1_in == e1 && e2_in == e2 ) {
            return true;
        } else if( e1_in == e2 && e2_in == e1 ) {
            return true;
        }
        return false;
    }

        bool isEqual(EDGE_T edgeIn){
            if ( edgeIn.e1 == e1 && edgeIn.e2 == e2 ) {
                return true;
            } else if( edgeIn.e1 == e2 && edgeIn.e2 == e1) {
                return true;
            }
            return false;
    }
} Edge_t;


    typedef struct mesh_subset_property
    {
       std::vector<unsigned int> idxBuffer;
       unsigned int verticesAmount;
        mesh_subset_property()
        {
            verticesAmount = 0;
        }

    } MeshSubsetProperty_t;

protected:
    int m_instancesAmount; /**< Maximum amount of objects to be drawn*/


    float **m_ODF; /**< Pointer that stores pointers to each ODF for each index */

    std::vector<glm::vec3> m_baseDirections;
    std::vector<unsigned int> m_indexBuffer;

    glm::mat4 * m_translateMatrix;
    glm::vec3 * m_translateVector;
    float m_scale;
    int m_ODFsize;
public:


    ODFSamples(int instancesAmount = 30, int icoIterations = 3);
    virtual ~ODFSamples();

    /**
    * @brief Initialization and computation of ODFs.
    */
    virtual void computeODFs();
    void computeTranslationMatrices(const unsigned int& instancesAmount);

    /**
    * @brief returns the ODF for voxel indexed by index
    * @param index of the voxel on volume that odf is computed
    */
    float *getVoxelODF(int index);

    /**
    * @brief returns the amount of elements of the spherical mesh, represented by m_baseDirections
    */
    int getODFSize() const;

    /**
    * @brief returns a copy of the indexBuffer
    */
    std::vector<unsigned int> getIndexBuffer() const;

    /**
    * @brief returns a copy of the spherical mesh directions
    */
    std::vector<glm::vec3> getBaseDirections() const; /**< returns a copy of the spherical mesh directions*/

    glm::mat4 getVoxelDisplacement(int index);
    glm::vec3 getVoxelDisplacementVec3(int index);

    int getInstancesAmount() const;
    float getScale() const;

    std::vector<unsigned int> getIndexBuffer(const unsigned int icoResIndex) const;
    unsigned int getMeshSubsetVerticesAmount(const unsigned int icoResIndex) const;
    size_t getIndexBufferSetSize() const;

    unsigned int m_cols, m_rows;

protected:
    void generateIcoCoordsMeshSphere(const unsigned int meshIterations);
    void generateIcoCoordsMeshSphere_OPT(const unsigned int meshIterations);
    void generateUVCoordsMeshSphere(const unsigned int thetaRes, const unsigned int phiRes);
    void MinMaxNormalizePsi(float * psi, const int &size);

    std::vector<MeshSubsetProperty_t> m_indexBufferSet;
    int m_meshIterations;


    int getUsedEdgesIndex (Edge_t edge, std::vector<Edge_t>& edgesSet);

};
#endif // ODFSAMPLES_H
