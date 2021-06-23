#include "ODFSamplesHemisphere.h"
#include <chrono>
#include <fstream>

#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <omp.h>
#include<iostream>
#include<QBallGlyphsCoefficientsSample.h>

ODFSamplesHemisphere::ODFSamplesHemisphere(int instancesAmount, int icoIterations):
    ODFSamples( instancesAmount, icoIterations)
{
    AlignEvenMesh(m_baseDirections, m_indexBuffer);

    for (size_t i = 0; i < m_baseDirections.size(); i+=2) {
        m_baseHemisphere.push_back(m_baseDirections[i]);
    }
}

void ODFSamplesHemisphere::computeODFs()
{
    m_ODF = new float*[m_instancesAmount];
//    std::cout << "m_instancesAmount: " << m_instancesAmount << std::endl;

#pragma omp parallel for
    for (int idx = 0; idx < m_instancesAmount; idx++)
    {
//        std::cout << idx << std::endl;
        float * psi = new float[m_baseHemisphere.size()];
        for (size_t i = 0; i < m_baseHemisphere.size(); i++) {
            const float r = sqrt(m_baseHemisphere[i].x*m_baseHemisphere[i].x +
                                 m_baseHemisphere[i].y*m_baseHemisphere[i].y +
                                 m_baseHemisphere[i].z*m_baseHemisphere[i].z);
            const float theta = acos(m_baseHemisphere[i].z/r);
            const float phi = atan2( m_baseHemisphere[i].y, m_baseHemisphere[i].x);
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
            } else if(idx%10 ==9) {
                auto temp = 5*cos(theta)*cos(theta)*cos(theta) - 3*cos(theta);
                SH = 0.25*std::sqrtf(7/(M_PI))*std::abs(temp);
            }
            psi[i] = abs(SH);
        }
        MinMaxNormalizePsi(psi, m_baseHemisphere.size());
        m_ODF[idx] = psi;
    }
}
