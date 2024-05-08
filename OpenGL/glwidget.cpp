#include "glwidget.h"
#include <QFile>
#include <QTextStream>


GLWidget::GLWidget() { }


void GLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    // program shadera
    programs["basic_shader"] = new GLSLProgram();
    programs["basic_shader"]->compileShaderFromFile("/home/student/Pobrane/gl_encapsulation_template/shaders/shader.vert", GL_VERTEX_SHADER);
    programs["basic_shader"]->compileShaderFromFile("/home/student/Pobrane/gl_encapsulation_template/shaders/shader.frag", GL_FRAGMENT_SHADER);
    programs["basic_shader"]->link();
    //....

    // jakas geometria
    geometries["axes"] = new Geometry();
    geometries["axes"]->primitiveMode = GL_LINES;
    glm::vec3 verts[] = { {0,0,0}, {0.5,0,0}, {0,0,0}, {0,0.5,0}, {0,0,0}, {0,0,0.5} };
    glm::vec3 colors[] = { {1,0,0}, {1,0,0},  {0,1,0}, {0,1,0},   {0,0,1}, {0,0,1} };
    geometries["axes"]->setVertices(0, verts, 6);
    geometries["axes"]->setAttribute(1, colors, 6);

/*
    v0    v1
    *-----*
    |   / |
    | /   |
    *-----*
    v3    v2
  */

    geometries["plane"] = new Geometry();
    float plane_size = 0.2;
    float plane_z = -1;
    geometries["plane"]->primitiveMode = GL_TRIANGLES;
    glm::vec3 plane_verts[] = {{-plane_size,  plane_size,plane_z},
                          { plane_size,  plane_size,plane_z},
                          { plane_size, -plane_size,plane_z},
                          {-plane_size, -plane_size,plane_z}};
    glm::vec3 plane_colors[] = {{1,0,1}, {0,1,1}, {1,1,0}, {1,0,0} };
    uint plane_idxs[] = {0,3,1,    1,3,2};
    geometries["plane"]->setVertices(0, plane_verts, 4);
    geometries["plane"]->setAttribute(1, plane_colors, 4);
    geometries["plane"]->setIndices(plane_idxs, 6);

    MVMat = glm::mat4(1.0);

    timer.setInterval(100);
    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
    timer.start();

    PRINT_GL_ERRORS("Widget::initializeGL(): ");
}

//void GLWidget::process_keys() {
//    if (key_pressed.contains(Qt::Key_W)) {
//        camera.pos = cameraq.pos + camera.forward * 10.0;
//    }
//    if (key_pressed.contains(Qt::Key_S)) {
//        camera.pos = cameraq.pos - camera.forward * 10.0;
//    }
//    if (key_pressed.contains(Qt::Key_A)) {
//        camera.pos = cameraq.pos + glm::normalize(glm::cross(camera.forward, camera.up));
//    }
//    if (key_pressed.contains(Qt::Key_D)) {
//        camera.pos = cameraq.pos - glm::normalize(glm::cross(camera.forward, camera.up));
//    }
//
//    camera.forward = glm::rotate(glm::identity(), posx, camera.up) * camera.forward;
//
//    camera.up = ...
//}



void GLWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
    PMat = glm::perspective(45.0f, float(w / h), 0.1f, 100.0f);
}

void GLWidget::paintGL()
{
    glClearColor(0.5, 0.5, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    MVMat = glm::rotate(MVMat, glm::radians(float(1)), glm::vec3(0, 0, 1));

    programs["basic_shader"]->use();
    programs["basic_shader"]->setUniform("MVMat", MVMat);
    programs["basic_shader"]->setUniform("PMat", PMat);

    geometries["axes"]->render();
    geometries["plane"]->render();

    qDebug() << "paint";
    PRINT_GL_ERRORS("Widget::paintGL(): ");
}
