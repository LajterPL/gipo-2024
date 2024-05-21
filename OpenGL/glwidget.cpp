#include "glwidget.h"
#include <QFile>
#include <QTextStream>


GLWidget::GLWidget() { }


void GLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    // program shadera
    programs["basic_shader"] = new GLSLProgram();
    programs["basic_shader"]->compileShaderFromFile("C:/Users/white/Downloads/gl_encapsulation_template_partial/gl_encapsulation_template/shaders/shader.vert", GL_VERTEX_SHADER);
    programs["basic_shader"]->compileShaderFromFile("C:/Users/white/Downloads/gl_encapsulation_template_partial/gl_encapsulation_template/shaders/shader.frag", GL_FRAGMENT_SHADER);
    programs["basic_shader"]->link();
    //....

    qDebug() << "Shader loaded...";

    // jakas geometria
    geometries["axes"] = new Geometry();
    geometries["axes"]->primitiveMode = GL_LINES;
    glm::vec3 verts[] = { {0,0,0}, {0.5,0,0}, {0,0,0}, {0,0.5,0}, {0,0,0}, {0,0,0.5} };
    glm::vec3 colors[] = { {1,0,0}, {1,0,0},  {0,1,0}, {0,1,0},   {0,0,1}, {0,0,1} };
    geometries["axes"]->setVertices(0, verts, 6);
    geometries["axes"]->setAttribute(1, colors, 6);

    qDebug() << "Axes created...";

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
    geometries["plane"]->primitiveMode = GL_TRIANGLES;
    glm::vec3 plane_verts[] = {{-plane_size,  plane_size, 0.0f},
                               { plane_size,  plane_size, 0.0f},
                               { plane_size, -plane_size, 0.0f},
                               {-plane_size, -plane_size, 0.0f}};
    glm::vec3 plane_colors[] = {{1,0,1}, {0,1,1}, {1,1,0}, {1,0,0} };
    uint plane_idxs[] = {0,3,1,    1,3,2};
    geometries["plane"]->setVertices(0, plane_verts, 4);
    geometries["plane"]->setAttribute(1, plane_colors, 4);
    geometries["plane"]->setIndices(plane_idxs, 6);

    objects["plane"] = new Frame();
    objects["plane"]->pos = glm::vec3(0.0f, 0.0f, -5.0f);
    objects["plane"]->forward = glm::vec3(0.0f, 0.0f, 1.0f);
    objects["plane"]->up = glm::vec3(0.0f, 1.0f, 0.0f);

    qDebug() << "Plane created...";

    int terrain_size = 2;
    float vert_spacing = 1.0f;

    geometries["terrain"] = new Geometry();
    geometries["terrain"]->primitiveMode = GL_TRIANGLES;

    int terrain_vert_num = terrain_size * terrain_size;

    glm::vec3* terrain_verts = new glm::vec3(terrain_vert_num);
    glm::vec3* terrain_colors = new glm::vec3(terrain_vert_num);

    int terrain_idxs_num = (terrain_size - 1) * 2 * (terrain_size - 1) * 3;

    uint* terrain_idxs = new uint(terrain_idxs_num);

     for (int y = 0; y < terrain_size; y++) {
         for (int x = 0; x < terrain_size; x++) {

             float height = 2.0f;

             terrain_verts[y*terrain_size + x] = glm::vec3(x*vert_spacing, height, y*vert_spacing);
             terrain_colors[y*terrain_size + x] = glm::vec3(0.0f, 0.0f, 1.0f - height/2.0f);

             // if (x < terrain_size - 1 && y < terrain_size -1) {

             //    terrain_idxs[last_index] = (y*terrain_size) + x;
             //    terrain_idxs[last_index+1] = ((y+1)*terrain_size) + x;
             //    terrain_idxs[last_index+2] = (y*terrain_size) + (x+1);
             //    last_index += 3;

             //    terrain_idxs[last_index] = (y*terrain_size) + (x+1);
             //    terrain_idxs[last_index+1] = ((y+1)*terrain_size) + (x+1);
             //    terrain_idxs[last_index+2] = ((y+1)*terrain_size) + x;
             //    last_index += 3;
             // }
         }
    }

    int last_index = 0;

     for(unsigned int y = 0; y < terrain_size-1; y++)       // for each row a.k.a. each strip
     {
         for(unsigned int x = 0; x < terrain_size; x++)      // for each column
         {
             for(unsigned int side = 0; side < 2; side++)      // for each side of the strip
             {
                 terrain_idxs[last_index] = (x + terrain_size * (y + side));
                 last_index++;
             }
         }
     }

    geometries["terrain"]->setVertices(0, terrain_verts, terrain_vert_num);
    geometries["terrain"]->setAttribute(1, terrain_colors, terrain_vert_num);
    geometries["terrain"]->setIndices(terrain_idxs, terrain_idxs_num);

    qDebug() << "Terrain created...";

    ModelMat = glm::mat4(1.0);

    camera.pos = glm::vec3(0.0f);
    camera.forward = glm::vec3(0.0f, 0.0f, -1.0f);
    camera.up = glm::vec3(0.0f, 1.0f, 0.0f);

    QWidget::setMouseTracking(true);
    setCursor(Qt::BlankCursor);

    timer.setInterval(100);
    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
    timer.start();

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
        camera.pos = camera.pos - camera.s();
    }
    if (key_pressed.contains(Qt::Key_D)) {
        camera.pos = camera.pos + camera.s();
    }
}



void GLWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
    ProjMat = glm::perspective(45.0f, float(w / h), 0.1f, 100.0f);

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
    if (e->position().x() == screen_width/2 && e->position().y() == screen_height/2) {
        return;
    }

    QCursor::setPos(screen_width/2 + e->globalPosition().x() - e->position().x(), screen_height/2 + e->globalPosition().y() - e->position().y());

    float x = e->position().x() - screen_width/2;
    float y = e->position().y() - screen_height/2;

    x = qDegreesToRadians(x) / 10.0;
    y = qDegreesToRadians(y) / 10.0;

    ProjMat = glm::rotate(ProjMat, x, glm::vec3(0.0f, 1.0f, 0.0f));

    camera.forward = glm::vec3(glm::rotate(glm::mat4(1.0f), -x, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::vec4(camera.forward, 1.0f));
    camera.forward = glm::normalize(camera.forward);

    camera.up = glm::vec3(glm::rotate(glm::mat4(1.0f), -x, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::vec4(camera.up, 1.0f));
    camera.up = glm::normalize(camera.up);

    glm::vec3 side = camera.s();

    ProjMat = glm::rotate(ProjMat, y, side);

    camera.forward = glm::vec3(glm::rotate(glm::mat4(1.0f), -y, side) * glm::vec4(camera.forward, 1.0f));
    camera.forward = glm::normalize(camera.forward);

    camera.up = glm::vec3(glm::rotate(glm::mat4(1.0f), -y, side) * glm::vec4(camera.up, 1.0f));
    camera.up = glm::normalize(camera.up);


}

void GLWidget::paintGL()
{
    process_keys();

    glClearColor(0.5, 0.5, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    programs["basic_shader"]->use();
    programs["basic_shader"]->setUniform("ModelMat", ModelMat);
    programs["basic_shader"]->setUniform("ProjMat", glm::translate(ProjMat, -camera.pos));

    geometries["axes"]->render();

    programs["basic_shader"]->setUniform("ModelMat", objects["plane"]->matrix());

    geometries["plane"]->render();

    objects["plane"]->forward = glm::normalize(glm::vec3(glm::rotate(glm::mat4(1.0f), qDegreesToRadians(5.0f), objects["plane"]->up) * glm::vec4(objects["plane"]->forward, 1.0f)));
    objects["plane"]->pos = glm::vec3(glm::rotate(glm::mat4(1.0f), qDegreesToRadians(1.0f), objects["plane"]->up) * glm::vec4(objects["plane"]->pos, 1.0f));

    PRINT_GL_ERRORS("Widget::paintGL(): ");
}
