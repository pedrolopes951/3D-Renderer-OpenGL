#version 330 core
in vec4 fragColor;      // Input color from the vertex shader
out vec4 outputColor;   // Output color

void main() {
    outputColor = fragColor;  // Pass the color from the vertex shader to the fragment shader output
}
