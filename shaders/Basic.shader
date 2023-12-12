#shader vertex
#version 330 core
    layout (location = 0) in vec3 aPos;  //  is used for specifying layout details for attributes, buffers, or memory, often related to how data is organized or bound.

    uniform mat4 transformation;  // is used to declare shader variables representing values that don't change within the shader program and are accessible from all stages of the shader


    void main()
    {
	    gl_Position = transformation * vec4(aPos, 1.0f);
    }

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_Color;

void main()
{
       color = u_Color;
}
