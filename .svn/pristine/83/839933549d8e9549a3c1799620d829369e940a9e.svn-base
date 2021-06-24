#include "Camera.h"
#include <iostream>
#include <glm/gtx/string_cast.hpp>

float Camera::cameraSpeed() const
{
    return m_cameraSpeed;
}

void Camera::setCameraSpeed(float cameraSpeed)
{
    m_cameraSpeed = cameraSpeed;
}

void Camera::scaleWorld(float scaleFactor)
{
    m_projectionParameters[0] *=scaleFactor;
    m_projectionParameters[1] *=scaleFactor;
    m_projectionParameters[2] *=scaleFactor;
    m_projectionParameters[3] *=scaleFactor;
    m_projectionParameters[4] *=scaleFactor;
    m_projectionParameters[5] *=scaleFactor;

    m_projection = glm::ortho( m_projectionParameters[0],
                               m_projectionParameters[1],
                               m_projectionParameters[2],
                               m_projectionParameters[3],
                               m_projectionParameters[4],
                               m_projectionParameters[5]);


}

glm::mat4 Camera::view() const
{
//    std::cout << "view: " << glm::to_string(m_view) << std::endl;
    return m_view;
}

glm::mat4 Camera::projection() const
{
//    std::cout << "projection: " << glm::to_string(m_projection) << std::endl;
    return m_projection;
}

Camera::Camera(unsigned int program,
               std::string mvpMatrixName,
               glm::vec3 cameraPos,
               glm::vec3 cameraDir,
               glm::vec3 cameraUp):
    m_cameraPos(cameraPos),
    m_cameraDir(cameraDir),
    m_cameraUp (cameraUp)
{
    m_cameraPosDefault=cameraPos;
    m_cameraDirDefault=cameraDir;
    m_cameraUpDefault =cameraUp;

    m_view = this->lookAt(m_cameraPos, m_cameraDir, m_cameraUp);
//    m_view = glm::mat4(1.0f);


    m_projectionParameters[0] = m_projectionParameters[2] = m_projectionParameters[4] = -1;
    m_projectionParameters[1] = m_projectionParameters[3] = m_projectionParameters[5] = 1;

    m_projection = glm::ortho( m_projectionParameters[0],
                               m_projectionParameters[1],
                               m_projectionParameters[2],
                               m_projectionParameters[3],
                               m_projectionParameters[4],
                               m_projectionParameters[5]);
    m_cameraSpeed = 0.05f;
//   std::cout << "projection: " << glm::to_string(m_projection) << std::endl;
//   std::cout << "view: " << glm::to_string(m_view) << std::endl;

    m_mvpMatrixLoc = -1;
    if (mvpMatrixName != "" || program != 0)
    {
        m_mvpMatrixLoc = glGetUniformLocation(program, mvpMatrixName.c_str());
        if (m_mvpMatrixLoc == -1)
            std::cerr << "MVP Matrix not found in the program" << std::endl;
    }

}

void Camera::setMvpMatrixLoc(unsigned int program, std::string mvpMatrixName)
{
    m_mvpMatrixLoc = glGetUniformLocation(program, mvpMatrixName.c_str());
    if (m_mvpMatrixLoc == -1)
        std::cerr << "MVP Matrix not found in the program" << std::endl;

}

void Camera::setMvpMatrixLoc(unsigned int program, const char* mvpMatrixName)
{
    m_mvpMatrixLoc = glGetUniformLocation(program, mvpMatrixName);
    if (m_mvpMatrixLoc == -1)
        std::cerr << "MVP Matrix not found in the program" << std::endl;

}

glm::mat4 Camera::lookAt(glm::vec3 cameraPos, glm::vec3 cameraDir, glm::vec3 cameraUp)
{
    glm::vec3 d = normalize(cameraDir - cameraPos);
    glm::vec3 l = normalize(glm::cross(d, cameraUp));
    glm::vec3 o = normalize(glm::cross(l,d));

//    std::cout << "d: " << glm::to_string(d) << std::endl;
//    std::cout << "l: " << glm::to_string(l) << std::endl;
//    std::cout << "o: " << glm::to_string(o) << std::endl;

    glm::mat4 out = glm::mat4(1.0f);

    out[0][0] = l.x;
    out[1][0] = l.y;
    out[2][0] = l.z;
    out[3][0] = -cameraPos.x;

    out[0][1] = o.x;
    out[1][1] = o.y;
    out[2][1] = o.z;
    out[3][1] = -cameraPos.y;

    out[0][2] = -d.x;
    out[1][2] = -d.y;
    out[2][2] = -d.z;
    out[3][2] = -cameraPos.z;

    out[0][3] = 0.0f;
    out[1][3] = 0.0f;
    out[2][3] = 0.0f;
    out[3][3] = 1.0f;

    return out;


}

void Camera::updateMvpMatrix()
{
    if (m_mvpMatrixLoc == -1)
    {
        std::cerr << "Not possible to update mvpMatrix. The localization of it in the current program wasn't found" << std::endl;
        return;
    }
//    std::cout << "Projection: " << glm::to_string(m_projection) << std::endl;
    glm::mat4 mvp = m_projection*m_view;
//    std::cout << "m_projection: " << glm::to_string(m_projection) << std::endl;
//    std::cout << "m_view: " << glm::to_string(m_view) << std::endl;
//    std::cout << "mvp: " << glm::to_string(mvp) << std::endl;
//    std::cout << "coluna MVP: " << glm::to_string(glm::row(mvp, 3)) << std::endl;
    glUniformMatrix4fv(m_mvpMatrixLoc, 1, GL_FALSE, glm::value_ptr(mvp));
}

void Camera::walkAround(glm::vec3 direction)
{

   m_projectionParameters[0]+=m_cameraSpeed*direction.x;
   m_projectionParameters[1]+=m_cameraSpeed*direction.x;
   m_projectionParameters[2]+=m_cameraSpeed*direction.y;
   m_projectionParameters[3]+=m_cameraSpeed*direction.y;
   m_projectionParameters[4]+=m_cameraSpeed*direction.z;
   m_projectionParameters[5]+=m_cameraSpeed*direction.z;

    m_projection = glm::ortho( m_projectionParameters[0],
                               m_projectionParameters[1],
                               m_projectionParameters[2],
                               m_projectionParameters[3],
                               m_projectionParameters[4],
                               m_projectionParameters[5]);
//    m_cameraPos += m_cameraSpeed*direction;
//    m_view = lookAt(m_cameraPos, m_cameraPos, m_cameraUp);
}

void Camera::zoomCommand(float factor)
{

   m_projectionParameters[0]+=m_cameraSpeed*factor;
   m_projectionParameters[1]-=m_cameraSpeed*factor;
   m_projectionParameters[2]+=m_cameraSpeed*factor;
   m_projectionParameters[3]-=m_cameraSpeed*factor;
   m_projectionParameters[4]+=m_cameraSpeed*factor;
   m_projectionParameters[5]-=m_cameraSpeed*factor;

    m_projection = glm::ortho( m_projectionParameters[0],
                               m_projectionParameters[1],
                               m_projectionParameters[2],
                               m_projectionParameters[3],
                               m_projectionParameters[4],
                               m_projectionParameters[5]);
//    m_cameraPos += m_cameraSpeed*direction;
    //    m_view = lookAt(m_cameraPos, m_cameraPos, m_cameraUp);
}

void Camera::rotateObserver(glm::vec3 axis, float angle)
{
    glm::mat4 rotMatrix(1.0f);
    rotMatrix = glm::rotate(rotMatrix, m_cameraSpeed*angle, axis);

    m_cameraPos = glm::vec3(rotMatrix*glm::vec4(m_cameraPos, 1.0f));
    m_cameraDir = glm::vec3(rotMatrix*glm::vec4(m_cameraDir, 1.0f));
    m_cameraUp  = glm::vec3(rotMatrix*glm::vec4(m_cameraUp, 1.0f));
    m_view = lookAt(m_cameraPos, m_cameraDir, m_cameraUp);

//    m_view = rotMatrix*m_view;


//    std::cout << "m_cameraPos: " << to_string(m_cameraPos) << std::endl;
//    std::cout << "m_view: " << to_string(m_view) << std::endl;

}

void Camera::resetCamera()
{
//    m_view = m_projection = glm::mat4(1.0f);
    m_cameraPos = m_cameraPosDefault;
    m_cameraDir = m_cameraDirDefault;
    m_cameraUp  = m_cameraUpDefault;

    m_view = lookAt(m_cameraPosDefault, m_cameraDirDefault, m_cameraUpDefault);
//    m_view = glm::mat4(1.0);
    m_projectionParameters[0] = m_projectionParameters[2] = m_projectionParameters[4] = -1;
    m_projectionParameters[1] = m_projectionParameters[3] = m_projectionParameters[5] = 1;

    m_projection = glm::ortho( m_projectionParameters[0],
                               m_projectionParameters[1],
                               m_projectionParameters[2],
                               m_projectionParameters[3],
                               m_projectionParameters[4],
                               m_projectionParameters[5]);
}


