#ifndef UTILS_H
#define UTILS_H

#include <QDebug>

#include <GL/gl.h>
#include <GL/glu.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/normal.hpp"


inline void PRINT_GL_ERRORS(QString mess)
{
    GLenum err;
    while( (err=glGetError()) != GL_NO_ERROR)
        qDebug() << "GL ERROR: " << mess << err << (const char*)gluErrorString(err) << "(" << err <<")";
}


#endif // UTILS_H
