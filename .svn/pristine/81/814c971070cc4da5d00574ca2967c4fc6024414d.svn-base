#ifndef CAMERA_H
#define CAMERA_H

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <QOpenGLFunctions>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_access.hpp>


class Camera
{
    glm::vec3 m_cameraPos;
    glm::vec3 m_cameraDir;
    glm::vec3 m_cameraUp;

    glm::vec3 m_cameraPosDefault;
    glm::vec3 m_cameraDirDefault;
    glm::vec3 m_cameraUpDefault;


    glm::mat4 m_view;
    glm::mat4 m_projection;

    float m_projectionParameters[6];

    bool isOrtho;
    float m_cameraSpeed;
    int m_mvpMatrixLoc;


public:
    Camera(unsigned int program = 0,
            std::string mvpMatrixName = "",
           glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  0.0f),
           glm::vec3 cameraDir = glm::vec3(0.0f, 0.0f, -1.0f),
           glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f));

    void setMvpMatrixLoc(unsigned int program, std::string mvpMatrixName);
    void updateMvpMatrix();


    void walkAround(glm::vec3 direction);
    float cameraSpeed() const;
    void setCameraSpeed(float cameraSpeed);

    void scaleWorld(float scaleFactor);
    void setMvpMatrixLoc(unsigned int program, const char *mvpMatrixName);
    glm::mat4 lookAt(glm::vec3 cameraPos, glm::vec3 cameraDir, glm::vec3 cameraUp);
    void zoomCommand(float factor);

    void rotateObserver(glm::vec3 axis, float angle);
    void resetCamera();

    glm::mat4 view() const;
    glm::mat4 projection() const;
};
#endif // CAMERA_H
