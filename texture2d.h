#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include <QOpenGLFunctions_3_3_Core>
#include <QMap>

#include "utils.h"

class Texture2D : protected QOpenGLFunctions_3_3_Core {

    GLuint m_handle;

public:
    Texture2D();

    void bind(int tex_unit);
    void unbind();

    bool loadFromFile(QString filename);

};

#endif // TEXTURE2D_H
