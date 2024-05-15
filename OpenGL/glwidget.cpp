#include "glwidget.h"
#include <QFile>
#include <QTextStream>


GLWidget::GLWidget() { }


void GLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    // program shadera
    programs["basic_shader"] = new GLSLProgram();
    programs["basic_shader"]->compileShaderFromFile("/home/student/Pobrane/OpenGL/shaders/shader.vert", GL_VERTEX_SHADER);
    programs["basic_shader"]->compileShaderFromFile("/home/student/Pobrane/OpenGL/shaders/shader.frag", GL_FRAGMENT_SHADER);
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
    float plane_size = 0.4;
    float plane_z = -10;
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

    int terrain_size = 5;
    float vert_spacing = 1.0f;

    geometries["terrain"] = new Geometry();
    geometries["terrain"]->primitiveMode = GL_TRIANGLES;

    glm::vec3* terrain_verts = new glm::vec3(terrain_size * terrain_size);

    for (int x = 0; x < terrain_size; x++) {
        for (int y = 0; y < terrain_size; y++) {
            terrain_verts[x*terrain_size + y] = glm::vec3(x*vert_spacing, y*vert_spacing, 0.0f);
        }
    }


    MVMat = glm::mat4(1.0);

    timer.setInterval(100);
    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
    timer.start();

    camera.pos = glm::vec3(0.0f);
    camera.forward = glm::vec3(0.0f, 0.0f, 1.0f);
    camera.up = glm::vec3(0.0f, 1.0f, 0.0f);

    QWidget::setMouseTracking(true);

    PRINT_GL_ERRORS("Widget::initializeGL(): ");
}

void GLWidget::process_keys() {
    if (key_pressed.contains(Qt::Key_W)) {
        camera.pos = camera.pos + camera.forward * 1.0f;
    }
    if (key_pressed.contains(Qt::Key_S)) {
        camera.pos = camera.pos - camera.forward * 1.0f;
    }
    if (key_pressed.contains(Qt::Key_A)) {
        camera.pos = camera.pos - glm::normalize(glm::cross(camera.forward, camera.up));
    }
    if (key_pressed.contains(Qt::Key_D)) {
        camera.pos = camera.pos + glm::normalize(glm::cross(camera.forward, camera.up));
    }
}



void GLWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
    PMat = glm::perspective(45.0f, float(w / h), 0.1f, 100.0f);

    screen_width = w;
    screen_height = h;
}

void GLWidget::keyPressEvent(QKeyEvent *e)
{
    key_pressed.insert(Qt::Key(e->key()));
}

void GLWidget::keyReleaseEvent(QKeyEvent *e)
{
    key_pressed.remove(Qt::Key(e->key()));
}

void GLWidget::mouseMoveEvent(QMouseEvent *e)
{
    float x = e->position().x() / float (screen_width);
    float y = e->position().y() / float (screen_height);

    x = qDegreesToRadians((360 * x) - 180);
    y = qDegreesToRadians((360 * y) - 180);

    //qDebug() << x << y;

    camera.forward = glm::vec3(qSin(x), -qSin(y), -qCos(x));

    PMat = glm::perspective(45.0f, float(screen_width / screen_height), 0.1f, 100.0f);
    PMat = glm::rotate(PMat, x, camera.up);
    PMat = glm::rotate(PMat, y, glm::cross(camera.forward, camera.up));
}

void GLWidget::paintGL()
{
    process_keys();

    glClearColor(0.5, 0.5, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    programs["basic_shader"]->use();
    programs["basic_shader"]->setUniform("MVMat", glm::translate(MVMat, -camera.pos));
    programs["basic_shader"]->setUniform("PMat", PMat);

    geometries["axes"]->render();
    geometries["plane"]->render();

    qDebug() << "paint";
    PRINT_GL_ERRORS("Widget::paintGL(): ");
}
