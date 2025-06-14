#version 330 core

in vec3 position;
uniform float size;

void main()
{
    gl_Position = vec4(position,1.0);
    //gl_PointSize = size;
}