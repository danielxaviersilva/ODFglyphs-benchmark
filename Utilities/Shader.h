#ifndef SHADER_H
#define SHADER_H
//#include<GL/glew.h>
#include <iostream>
#include <fstream>
#include <QOpenGLFunctions>
#include <QFile>
#include <QTextStream>
//#include <OpenGL.h>

#include <vector>


class Shader
{
    unsigned int vertShader, fragShader, program;
    bool isProgramLinked;
    std::string m_pathVertShader, m_pathFragShader;
public:
    Shader();
    Shader(const char * vert_path, const char * frag_path);
    Shader(std::string vert_path, std::string frag_path);
    void loadProgram(const char * vert_path, const char * frag_path);
    void loadProgramQt(const char * vert_path, const char * frag_path);
    void loadProgramText(const char * vert, const char * frag);

    ~Shader();

    unsigned int getProgramID();
    uint LoadShader(const char *vertex_path, const char *fragment_path);

    bool loadVertexShader(const char *vert_path);
    bool loadFragmentShader(const char *frag_path);

    bool loadFragmentShaderQt(const char* frag_path);
    bool loadVertexShaderQt(const char* frag_path);

    bool linkProgram();

    bool useProgram();
    void programVarInfo();

    void release();

    //aux functions
    std::string readText(const char *filePath);
    std::string readTextQt(const char *filePath);

    int getAttribLocation(std::string varName);
    int getUniformLocation(std::string varName);
};

#endif // SHADER_H

