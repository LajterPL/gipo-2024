#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include "geometry.h"


Geometry* create_plane(float w, float h);
Geometry* create_axes(float length);
Geometry* create_cube(float w, float h, float d);
Geometry* create_cylinder(float r, float h, int slices);
//Geometry* create_sphere(float r, int slices, int stacks);


#endif // PRIMITIVES_H
