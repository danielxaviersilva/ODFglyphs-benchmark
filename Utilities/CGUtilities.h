/**
 * @file CGUtilities.h
 *
 * @brief Generic computer graphics functions analytic geometries transforms.
 *
 * @author Daniel Xavier Silva
 * Contact: danielxaviers@gmail.com
 *
 */
#ifndef CGUTILITIES_H
#define CGUTILITIES_H
#include <QOpenGLFunctions>
#include <glm/glm.hpp>
#include <iostream>
#include <glm/gtx/transform.hpp>


class CGUtilities
{
protected:
    CGUtilities();
    void _check_gl_error(const char *file, int line);
     glm::mat4 shiftYtoAxisMatrix(glm::vec3 axis);
     glm::mat4 shiftZtoAxisMatrix(glm::vec3 axis);     
     void shrinkVec3(std::vector<glm::vec3> &V, std::vector<unsigned int> &index, bool verbose = false);
     bool AlignEvenMesh(std::vector<glm::vec3> &V, std::vector<unsigned int> &idxBuffer);




};

#endif // CGUTILITIES_H
