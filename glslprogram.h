#ifndef GLSLPROGRAM_H
#define GLSLPROGRAM_H

//#ifdef __linux
//#define GL_GLEXT_PROTOTYPES 1
//#endif

#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <string>
#include <QDebug>
#include <GL/glu.h>

#include "utils.h"


//Klasa zarzadzajaca programem shadera
// .... do dalszej rozbudowy ....
class GLSLProgram :  protected QOpenGLFunctions_3_3_Core
{
    GLuint handle;
    bool checkShaderStatus(GLuint);
    bool checkProgramStatus(GLuint);

public:
    GLSLProgram();
    //~GLSLProgram();
    bool compileShaderFromFile(const char* filename, GLenum type);
    bool compileShaderFromString(const std::string& source, GLenum type);
    bool link();
    void use();

    void setUniform(const char *name, int i);
    void setUniform(const char* name, glm::vec3 v);
    void setUniform(const char* name, glm::mat4 mat);
    //void setUniform(const char* name, int v);
    //void setUniform(const char* name, float v);

    //void bindAttribLocation(GLuint location, const char* name);

};

#endif // GLSLPROGRAM_H
