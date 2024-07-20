#version 330 core

in vec2 textCoord;
in vec4 vertexTint;

out vec4 FragColor;

uniform sampler2D texture1;

void main()
{
    // FragColor = vec4(1.0f,1.0f,1.0f,1.0f);
    FragColor = texture(texture1, textCoord);
};
