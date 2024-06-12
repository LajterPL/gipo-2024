#version 330

uniform mat4 ModelMat;
uniform mat4 ProjMat;

layout (location=0) in vec3 VertexPosition;
layout (location=1) in vec2 UVCoord;

out vec2 OutUVCoord;

void main()
{
    gl_Position = ProjMat * ModelMat * vec4(VertexPosition, 1.0);
    OutUVCoord = UVCoord;
}
