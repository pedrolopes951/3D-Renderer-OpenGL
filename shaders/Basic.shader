#shader vertex
#version 330 core

layout(location = 0) in vec4 position;

uniform mat4 transform;



void main()
{
    gl_Position = transform * vec4(position, 1.0f);
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;


uniform vec4 u_Color;

void main()
{
  color = u_Color;
}
