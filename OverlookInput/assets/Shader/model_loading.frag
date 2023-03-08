#version 450 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D aiTextureType_DIFFUSE1;

void main()
{    
    FragColor = texture(aiTextureType_DIFFUSE1, TexCoords);
}