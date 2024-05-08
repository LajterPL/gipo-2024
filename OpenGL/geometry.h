#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <QOpenGLFunctions_3_3_Core>
#include <QMap>
#include "utils.h"


//const int position_index = 1;
//const int color_index = 2;

// Klasa zarzadzajaca geometria, buforami i renderingiem
class Geometry : protected QOpenGLFunctions_3_3_Core
{
protected:
    GLuint vao;    // Vertex Array Object
    int n_verts;   //ilosc wierzcholkow

    GLuint ibo;     //bufor indeksow
    int n_indices;  //ilosc indeksow

    //! Mapa buforow atrybutow
    //! klucz mapy to index danego atrybutu, wartosc mapy to uchwyt do bufora
    QMap<uint, GLuint> bufferObjects;


public:
    GLenum primitiveMode;  // tryb rysowania geometrii: punkty, linie, trojkaty

    Geometry();
    virtual ~Geometry() {}

    virtual void render();

    void setIndices(uint* data, int n);

    void setVertices(uint index, glm::vec3* verts, int n);
    void setAttribute(uint index, glm::vec3* data, int n);
    //void setAttribute(index, vec2* data, int n);
    //void setAttribute(float* data, int n);
    //...
};



#endif // GEOMETRY_H
