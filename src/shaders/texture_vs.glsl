#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

uniform vec3 offset;
uniform vec3 colorOffset;

void main()
{
    
    gl_Position = vec4(aPos+offset, 1.0);
    ourColor = aPos+offset+colorOffset;
    TexCoord = aTexCoord;
}
