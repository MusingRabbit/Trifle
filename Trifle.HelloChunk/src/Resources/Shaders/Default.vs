#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aTint;
layout(location = 3) in vec2 aTextCoord;

out vec2 textCoord;
out vec4 vertexTint;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    textCoord = vec2(aTextCoord.x, aTextCoord.y);
    vertexTint = vec4(aTint, 1.0);
};