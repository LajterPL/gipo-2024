#include "geometry.h"

Geometry::Geometry()
{
    // inicjalizacja wskaznikow do funkcji OpenGLa
    initializeOpenGLFunctions();

    // wygenerowanie nazwy dla Vertex Array Object
    glGenVertexArrays(1, &vao);

    primitiveMode = GL_TRIANGLES;
    n_verts = 0;

    ibo = 0;
    n_indices = 0;    
}

void Geometry::render()
{
    // narysowanie wszystkiego co jest wrzucone do tablicy obiektow wierzcholkow vao
    glBindVertexArray(vao);
    if(n_indices > 0){
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glDrawElements(primitiveMode, n_indices, GL_UNSIGNED_INT, 0);
    }
    else {
        glDrawArrays(primitiveMode, 0, n_verts);
    }
    glBindVertexArray(0);

    PRINT_GL_ERRORS("Geometry::render(): ");
}

void Geometry::setIndices(uint *data, int n)
{
    n_indices = n;
    if(ibo==0){
        glGenBuffers(1, &ibo);
    }
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, n_indices * sizeof(uint), data, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    PRINT_GL_ERRORS("Geometry::setIndices(): ");
}

void Geometry::setVertices(uint index, glm::vec3* verts, int n)
{
    n_verts = n;
    setAttribute(index, verts, n);
    PRINT_GL_ERRORS("Geometry::setVertices(): ");
}

void Geometry::setAttribute(uint index, glm::vec3 *data, int n)
{
    //wygenerowanie nazwy bufora dla atrybutu i dodanie do mapy pod konkretnym indexem
    if( !bufferObjects.contains(index) )
    {
        GLuint i;
        glGenBuffers(1, &i);
        bufferObjects.insert(index, i);
    }

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, bufferObjects[index]);
    glBufferData(GL_ARRAY_BUFFER, n * sizeof(glm::vec3), data,GL_STATIC_DRAW);
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindVertexArray(0);

    PRINT_GL_ERRORS("Geometry::setAttribute(): ");
}

void Geometry::setAttribute(uint index, glm::vec2 *data, int n)
{
    //wygenerowanie nazwy bufora dla atrybutu i dodanie do mapy pod konkretnym indexem
    if( !bufferObjects.contains(index) )
    {
        GLuint i;
        glGenBuffers(1, &i);
        bufferObjects.insert(index, i);
    }

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, bufferObjects[index]);
    glBufferData(GL_ARRAY_BUFFER, n * sizeof(glm::vec2), data,GL_STATIC_DRAW);
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindVertexArray(0);

    PRINT_GL_ERRORS("Geometry::setAttribute(): ");
}

