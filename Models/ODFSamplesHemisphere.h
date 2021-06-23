/**
 * @file ODFSamplesHemisphere.h
 *
 * @brief Generate and store synthetic data derived from spherical harmonics in the half sphere.
 * The functions are: $Re(Y_1^{-1})$ $Re(Y_1^0)$ $Im(Y_1^{-1})$ $Re(Y_2^{-2})$ $Im(Y_2^{-2})$ $Re(Y_2^{-1})$ $Im(Y_2^{-1})$ $Y_2^0$ $Y_0^0$ and
 *  $Y_3^0$, where it is indexed in sequence and periodically by j mod 10.
 *
 * @author Daniel Xavier Silva
 * Contact: danielxaviers@gmail.com
 *
 */
#ifndef ODFSAMPLESHEMISPHERE_H
#define ODFSAMPLESHEMISPHERE_H

#include <glm/glm.hpp>
#include <vector>
#include <math.h>

#include "ODFSamples.h"

class ODFSamplesHemisphere : public ODFSamples
{
private:
    std::vector<glm::vec3> m_baseHemisphere;

public:
    ODFSamplesHemisphere(int instancesAmount = 30, int icoIterations = 3);
    void computeODFs();
};

#endif // ODFSAMPLESHEMISPHERE_H
