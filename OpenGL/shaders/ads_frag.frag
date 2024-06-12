#version 330

uniform sampler2D tex1;
uniform vec4 LightPos;
uniform vec4 LightColor;
uniform vec4 MaterialProp;

in vec2 OutUVCoord;
in vec4 EyePos;
in vec3 Normal;

out vec4 FragColor;

void main(void)
{
    vec4 tex_color = texture(tex1, OutUVCoord);
    vec3 lightDir = normalize((LightPos - EyePos).xyz);

    vec4 ambient = LightColor * MaterialProp.x;

    float diffuse = max(0.0f, dot(lightDir, Normal));

    vec3 r = reflect(-lightDir, Normal);
    vec3 v = normalize(-EyePos.xyz);

    float spec = pow(max(0.0f, dot(r, v)), MaterialProp.w);

   FragColor = ambient +
               diffuse * LightColor * MaterialProp.y +
               spec * LightColor * MaterialProp.z;

    FragColor = FragColor * tex_color;
}
