#version 330 core
layout(location = 0) in vec3 inPosition;  // Input vertex position
out vec4 fragColor;                     // Output color

void main() {
    gl_Position = vec4(inPosition, 1.0);
    fragColor = vec4(1.0, 0.0, 0.0, 1.0);  // Red color
}
