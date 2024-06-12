#ifndef GLWIDGET_H
#define GLWIDGET_H

#if QT_VERSION_MAJOR >= 6
    #include <QtOpenGLWidgets/QOpenGLWidget>
#else
    #include <QOpenGLWidget>
#endif

#include "glslprogram.h"
#include "geometry.h"
#include <QOpenGLFunctions_3_3_Core>
#include <QMap>
#include <QDebug>
#include <QTimer>
#include <QKeyEvent>
#include <QMouseEvent>

#include "frame.h"
#include "camera.h"
#include "texture2d.h"


class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
    QMap<QString, GLSLProgram*> programs;
    QMap<QString, Geometry*> geometries;
    QMap<QString, Frame*> objects;
    QMap<QString, Texture2D*> textures;

    Camera camera;

    glm::mat4 ModelMat;
    glm::mat4 ViewMat;
    glm::mat4 ProjMat;

    glm::vec4 SunPos;

    QTimer timer;

    QSet<Qt::Key> key_pressed;
    int screen_width;
    int screen_height;

    int cursor_x;
    int cursor_y;

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

    void createShaders(QString shader_folder_path);
    void createTextures();
    void createGeometry();

    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void leaveEvent(QMouseEvent *e);
    void process_keys();
public:
    GLWidget();
};


#endif // GLWIDGET_H
