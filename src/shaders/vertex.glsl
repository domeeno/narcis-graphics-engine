#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

uniform vec3 offset;
uniform vec3 colorOffset;

void main()
{
    
    gl_Position = vec4(aPos+offset, 1.0);
    ourColor = aPos+offset+colorOffset;
}