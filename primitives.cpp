#include "primitives.h"


Geometry *create_axes(float length)
{
    Geometry *g = new Geometry();
    g->primitiveMode = GL_LINES;
    glm::vec3 verts[] = { {0,0,0}, {length,0,0}, {0,0,0}, {0,0.5,0}, {0,0,0}, {0,0,0.5} };
    glm::vec3 colors[] = { {1,0,0}, {1,0,0},  {0,1,0}, {0,1,0},   {0,0,1}, {0,0,1} };
    g->setVertices(0, verts, 6);
    g->setAttribute(1, colors, 6);
    return g;
}

Geometry *create_plane(float w, float h)
{
    Geometry *g = new Geometry();
    g->primitiveMode = GL_TRIANGLES;
    glm::vec3 plane_verts[] = {{-w/2.0f,  h/2.0f,0},
                          { w/2.0f,  h/2.0f,0},
                          { w/2.0f, -h/2.0f,0},
                          {-w/2.0f, -h/2.0f,0}};
    glm::vec3 plane_colors[] = {{1,1,1}, {1,1,1}, {1,1,1}, {1,1,1} };
    uint plane_idxs[] = {0,3,1,    1,3,2};
    g->setVertices(0, plane_verts, 4);
    g->setAttribute(1, plane_colors, 4);
    g->setIndices(plane_idxs, 6);
    return g;
}
