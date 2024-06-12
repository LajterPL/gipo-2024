#version 330

uniform mat4 ModelMat;
uniform mat4 ViewMat;
uniform mat4 ProjMat;

layout (location=0) in vec3 VertexPosition;
layout (location=2) in vec3 VertexNormal;
layout (location=1) in vec2 UVCoord;

out vec2 OutUVCoord;
out vec4 EyePos;
out vec3 Normal;

void main()
{
    gl_Position = ProjMat * ViewMat * ModelMat * vec4(VertexPosition, 1.0);
    OutUVCoord = UVCoord;

    Normal =  VertexNormal;
    EyePos = ModelMat * vec4(VertexPosition, 1.0);

}
