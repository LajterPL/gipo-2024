#include "glwidget.h"
#include <QFile>
#include <QTextStream>
#include <QCoreApplication>

const uint TERRAIN_SIZE = 200;

GLWidget::GLWidget() { }


// Inicjalizacja

void GLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    createShaders(":/shaders/shaders/");
    createTextures();
    createGeometry();

    ModelMat = glm::mat4(1.0f);
    ViewMat = glm::mat4(1.0f);

    camera.pos = glm::vec3(0.0f);
    camera.forward = glm::vec3(0.0f, 0.0f, -1.0f);
    camera.up = glm::vec3(0.0f, 1.0f, 0.0f);

    SunPos = glm::vec4(0, 10.0f, 10.0f, 1);

    QWidget::setMouseTracking(true);
    setCursor(Qt::BlankCursor);

    timer.setInterval(100);
    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
    timer.start();

    PRINT_GL_ERRORS("Widget::initializeGL(): ");
}

void GLWidget::createGeometry() {
    // Środek układu
    geometries["axes"] = new Geometry();
    geometries["axes"]->primitiveMode = GL_LINES;

    glm::vec3 verts[] = { {0,0,0}, {0.5,0,0}, {0,0,0}, {0,0.5,0}, {0,0,0}, {0,0,0.5} };
    glm::vec3 colors[] = { {1,0,0}, {1,0,0},  {0,1,0}, {0,1,0},   {0,0,1}, {0,0,1} };

    geometries["axes"]->setVertices(0, verts, 6);
    geometries["axes"]->setAttribute(1, colors, 6);

    qDebug() << "Axes created...";

    // Płaszczyzna
    float plane_size = 0.4;

    geometries["plane"] = new Geometry();
    geometries["plane"]->primitiveMode = GL_TRIANGLES;

    glm::vec3 plane_verts[] = {{-plane_size,  plane_size, 0.0f},
                               { plane_size,  plane_size, 0.0f},
                               { plane_size, -plane_size, 0.0f},
                               {-plane_size, -plane_size, 0.0f}};

    glm::vec3 plane_uvs[] = {{0,1, 0}, {1,1, 0}, {1,0, 0}, {0,0, 0}};
    uint plane_idxs[] = {0,3,1,    1,3,2};


    geometries["plane"]->setVertices(0, plane_verts, 4);
    geometries["plane"]->setAttribute(1, plane_uvs, 4);
    geometries["plane"]->setIndices(plane_idxs, 6);

    objects["plane"] = new Frame();
    objects["plane"]->pos = glm::vec3(0.0f, 0.0f, -5.0f);
    objects["plane"]->forward = glm::vec3(0.0f, 0.0f, 1.0f);
    objects["plane"]->up = glm::vec3(0.0f, 1.0f, 0.0f);

    qDebug() << "Plane created...";

    // Teren

    QImage height_map(":/textures/textures/clouds1.png");

    float vert_spacing = 0.1f;
    float max_height = 5.0f;
    float terrain_offset = (TERRAIN_SIZE * vert_spacing) / 2.0f;

    int terrain_verts_size = TERRAIN_SIZE * TERRAIN_SIZE;

    uint strip_num = TERRAIN_SIZE - 1;
    uint verts_in_strip = TERRAIN_SIZE * 2;
    uint terrain_idxs_size = strip_num * verts_in_strip;

    geometries["terrain"] = new Geometry();
    geometries["terrain"]->primitiveMode = GL_TRIANGLE_STRIP;

    glm::vec3 terrain_verts[terrain_verts_size];
    glm::vec3 terrain_uvs[terrain_verts_size];
    glm::vec3 terrain_normals[terrain_verts_size];

    std::fill_n(terrain_normals, terrain_verts_size, glm::vec3(0));

    uint last_index = 0;

    for (uint x = 0; x < TERRAIN_SIZE; x++) {
        for (uint y = 0; y < TERRAIN_SIZE; y++) {

            int height = qRed(height_map.pixel(x, y));

            terrain_verts[last_index] = glm::vec3(x * vert_spacing - terrain_offset, (height / 255.0f) * max_height - max_height, y * vert_spacing - terrain_offset);
            terrain_uvs[last_index] = glm::vec3((x / (float) TERRAIN_SIZE) * 10, (y / (float) TERRAIN_SIZE) * 10, 0);
            last_index++;
        }
    }


    uint terrain_idxs[terrain_idxs_size];

    last_index = 0;

    for (uint row = 0; row < strip_num; row++) {

        for (uint col = 0; col < TERRAIN_SIZE; col++) {

            for (uint side = 0; side < 2; side++) {

                terrain_idxs[last_index] = col + TERRAIN_SIZE * (row + side);
                last_index++;
            }
        }
    }


    for (uint strip = 0; strip < strip_num; strip++) {
        for (uint idx = 0; idx < verts_in_strip-2; idx++) {

            glm::vec3 a = terrain_verts[terrain_idxs[strip * verts_in_strip + idx + 1]] - terrain_verts[terrain_idxs[strip * verts_in_strip + idx]];
            glm::vec3 b = terrain_verts[terrain_idxs[strip * verts_in_strip + idx + 2]] - terrain_verts[terrain_idxs[strip * verts_in_strip + idx]];

            glm::vec3 n = glm::cross(a, b);

            if (n.y < 0) {
                n = -n;
            }

            terrain_normals[terrain_idxs[strip * verts_in_strip + idx]] += n;
            terrain_normals[terrain_idxs[strip * verts_in_strip + idx + 1]] += n;
            terrain_normals[terrain_idxs[strip * verts_in_strip + idx + 2]] += n;
        }
    }

    for (int i = 0; i < terrain_verts_size; i++) {
        terrain_normals[i] = glm::normalize(terrain_normals[i]);
    }

    geometries["terrain"]->setVertices(0, terrain_verts, terrain_verts_size);
    geometries["terrain"]->setAttribute(1, terrain_uvs, terrain_verts_size);
    geometries["terrain"]->setAttribute(2, terrain_normals, terrain_verts_size);
    // geometries["terrain"]->setAttribute(1, terrain_normals, terrain_verts_size);
    geometries["terrain"]->setIndices(terrain_idxs, terrain_idxs_size);

    qDebug() << "Terrain created...";
}

void GLWidget::createShaders(QString shader_folder_path)
{
    programs["basic_shader"] = new GLSLProgram();
    programs["basic_shader"]->compileShaderFromFile(qPrintable(shader_folder_path + QString("shader.vert")), GL_VERTEX_SHADER);
    programs["basic_shader"]->compileShaderFromFile(qPrintable(shader_folder_path + QString("shader.frag")), GL_FRAGMENT_SHADER);
    programs["basic_shader"]->link();

    programs["base_tex"] = new GLSLProgram();
    programs["base_tex"]->compileShaderFromFile(qPrintable(shader_folder_path + QString("uv_plane.vert")), GL_VERTEX_SHADER);
    programs["base_tex"]->compileShaderFromFile(qPrintable(shader_folder_path + QString("uv_plane.frag")), GL_FRAGMENT_SHADER);
    programs["base_tex"]->link();

    programs["basic_light"] = new GLSLProgram();
    programs["basic_light"]->compileShaderFromFile(qPrintable(shader_folder_path + QString("ads_frag.vert")), GL_VERTEX_SHADER);
    programs["basic_light"]->compileShaderFromFile(qPrintable(shader_folder_path + QString("ads_frag.frag")), GL_FRAGMENT_SHADER);
    programs["basic_light"]->link();

    qDebug() << "Shader loaded...";
}

void GLWidget::createTextures()
{
    textures["grass"] = new Texture2D();
    if (!textures["grass"]->loadFromFile(":/textures/textures/grass_2k.jpg")) {
        qDebug() << "Nie udalo sie wczytac tekstury";
    }

    textures["metal"] = new Texture2D();
    if (!textures["metal"]->loadFromFile(":/textures/textures/metal2.jpg")) {
        qDebug() << "Nie udalo sie wczytac tekstury";
    }

    textures["moss"] = new Texture2D();
    if (!textures["moss"]->loadFromFile(":/textures/textures/moss.jpg")) {
        qDebug() << "Nie udalo sie wczytac tekstury";
    }

}


// Obsługa sterowania

void GLWidget::process_keys() {
    if (key_pressed.contains(Qt::Key_W)) {
        camera.pos = camera.pos + camera.forward * 0.2f;
    }
    if (key_pressed.contains(Qt::Key_S)) {
        camera.pos = camera.pos - camera.forward * 0.2f;
    }
    if (key_pressed.contains(Qt::Key_A)) {
        camera.pos = camera.pos - camera.s();
    }
    if (key_pressed.contains(Qt::Key_D)) {
        camera.pos = camera.pos + camera.s();
    }

    ViewMat = glm::mat4(1.0f);
    ViewMat = glm::translate(ViewMat, -camera.pos);
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


// Renderowanie

void GLWidget::paintGL()
{
    process_keys();

    glClearColor(0.5, 0.5, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    programs["basic_shader"]->use();
    programs["basic_shader"]->setUniform("ModelMat", ModelMat);
    programs["basic_shader"]->setUniform("ProjMat", glm::translate(ProjMat, -camera.pos));

    geometries["axes"]->render();

    // geometries["terrain"]->renderStrip(TERRAIN_SIZE - 1, TERRAIN_SIZE*2);

    textures["moss"]->bind(0);

    programs["base_tex"]->use();
    programs["base_tex"]->setUniform("ModelMat", ModelMat);
    programs["base_tex"]->setUniform("ProjMat", glm::translate(ProjMat, -camera.pos));
    programs["base_tex"]->setUniform("tex1", 0);

    // geometries["terrain"]->renderStrip(TERRAIN_SIZE - 1, TERRAIN_SIZE*2);

    programs["base_tex"]->setUniform("ModelMat", objects["plane"]->matrix());

    geometries["plane"]->render();

    objects["plane"]->forward = glm::normalize(glm::vec3(glm::rotate(glm::mat4(1.0f), qDegreesToRadians(5.0f), objects["plane"]->up) * glm::vec4(objects["plane"]->forward, 1.0f)));
    objects["plane"]->pos = glm::vec3(glm::rotate(glm::mat4(1.0f), qDegreesToRadians(1.0f), objects["plane"]->up) * glm::vec4(objects["plane"]->pos, 1.0f));

    programs["basic_light"]->use();
    programs["basic_light"]->setUniform("ModelMat", ModelMat);
    programs["basic_light"]->setUniform("ViewMat", ViewMat);
    programs["basic_light"]->setUniform("ProjMat", ProjMat);
    programs["basic_light"]->setUniform("LightPos", SunPos);
    programs["basic_light"]->setUniform("LightColor", glm::vec4( 252 / 255.0f, 247 / 255.0f, 224 / 255.0f, 0));
    programs["basic_light"]->setUniform("MaterialProp", glm::vec4(0.1f, 0.7f, 0.8f, 32.0f)); // Ambient, Diffuse, Specular, Shininess
    programs["basic_light"]->setUniform("tex1", 0);

    geometries["terrain"]->renderStrip(TERRAIN_SIZE - 1, TERRAIN_SIZE*2);

    SunPos = glm::rotate(glm::mat4(1.0f), qDegreesToRadians(1.0f), glm::vec3(0, 1, 0)) * SunPos;

    PRINT_GL_ERRORS("Widget::paintGL(): ");
}

void GLWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
    ProjMat = glm::perspective(45.0f, float(w / h), 0.1f, 100.0f);

    screen_width = w;
    screen_height = h;
}
