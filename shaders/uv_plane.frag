#version 330

uniform sampler2D tex1;

in vec2 OutUVCoord;

out vec4 FragColor;

void main(void)
{
    FragColor = texture(tex1, OutUVCoord);
}
