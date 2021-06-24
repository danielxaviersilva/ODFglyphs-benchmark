#ifndef RENDERCROSSLINE_H
#define RENDERCROSSLINE_H
#include <iostream>
#include <vector>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>

//Render a orange triangle, indepedent of externals variables/shaders
void renderCrossLine(){
 std::vector<float> vertices =  {-1.00f,  0.0f, 0.0f, 1.0f,
                                 1.00f,  0.0f, 0.0f, 1.0f,
                                0.00f, -1.0f, 0.0f, 1.0f,
                                0.00f, 1.0f, 0.0f, 1.0f};
    unsigned int VBO;
    glGenBuffers(1,&VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), vertices.data(), GL_STATIC_DRAW);

    const char *vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec4 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = aPos;\n"
        "}\0";
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    const char *fragmentShaderSource = "#version 330 core\n"
                                "out vec4 FragColor;\n"
                                "void main()\n"
                                "{FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);}\0";
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glUseProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_LINES, 0, 4);
}


#endif // RENDERCROSSLINE_H
