#ifndef MATHGL_H
#define MATHGL_H
#include <QDebug>

#include <math.h>


struct vec2 { float x,y; };
struct vec3 { float x,y,z; };
struct vec4 { float x,y,z,w; };

struct mat4 { float m[16]; };


inline float len(const vec3& a)
{

}

inline vec3 normal(const vec3& a)
{

}

inline float dot(const vec3& a, const vec3& b)
{

}

inline vec3 cross(const vec3& a, const vec3& b)
{

}


inline mat4 identity()
{
    mat4 m;
    memset(m.m, 0, 16*4);
    m.m[0]=m.m[5]=m.m[10]=m.m[15]=1.0f;
    return m;
}

inline mat4 translation_mat(float x, float y, float z)
{
    mat4 mret = identity();
    mret.m[12] = x;
    mret.m[13] = y;
    mret.m[14] = z;
    return mret;
}

inline mat4 rotation_mat(float angle, float x, float y, float z)
{
    mat4 mret = identity();
    //...

    return mret;
}

inline mat4 scale_mat(float x, float y, float z)
{
    mat4 mret = identity();
    //...

    return mret;
}

inline mat4 inversed(const mat4& mat)
{
    mat4 mret = identity();
    //...

    return mret;
}

inline mat4 transposed(const mat4& mat)
{
    mat4 mret = identity();
    //...

    return mret;
}

inline mat4 mul(const mat4& m1, const mat4& m2)
{
    mat4 mret;
    //...
    return mret;
}

inline vec3 mul(const mat4& m1, const vec3& v)
{
    vec3 vret;
    //...
    return vret;
}

inline vec4 mul(const mat4& m1, const vec4& v)
{
    vec4 vret;
    //...
    return vret;
}

inline mat4 perspective(float fovy, float aspect, float znear, float zfar)
{
    mat4 M;
    //...

    return M;
}

#endif // MATHGL_H
