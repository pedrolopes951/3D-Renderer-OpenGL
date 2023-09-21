// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

#include "FactoryModels.h"
#include "Models.h"
#include <iostream>
#include <memory>


// Shader Vertex
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
// Fragment shader
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";



void Shader(unsigned int& shaderProgram)
{
    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

GLFWwindow* InitWindow()
{
    // GLFW Provides a library to manage thigs like creting window, managing user input, and provinding event driven framework
    // Glew Provides OpenGL function exntension and functino loading, it ensures we can acess the lastest OpenGl features and functions regardless of the platform

    // Initialise GLFW
    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        getchar();
        return nullptr;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);// 4x times the antialiasing 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Use the core-profile instead of old immediate openGl version 

    // Open a window and create its OpenGL context
    GLFWwindow* window = glfwCreateWindow(960, 540, "Tutorial 02 - Red triangle", NULL, NULL);
    if (window == NULL) {
        fprintf(stderr, "Failed to open GLFW window.\n");
        getchar();
        glfwTerminate();
        return nullptr;

    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return nullptr;
    }

    std::cout << "Using GL Version: " << glGetString(GL_VERSION) << std::endl;


    //// Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);



    return window;
}

int main(void)
{
    GLFWwindow* window = InitWindow();
    if (!window)
        return -1;


    // Build Shader
    unsigned int shaderProgram;
    Shader(shaderProgram);

    // Create samples of shapes to be rendered
    std::unique_ptr<IModelFactory> triangleFactory = std::make_unique<TriangleFactory>();

    Vertex triangle[] =
    { Vertex(-0.5f, -0.5f, 0.0f),
    Vertex(0.5f, -0.5f, 0.0f),
    Vertex(0.0f, 0.5f, 0.0f) };

    std::unique_ptr<IModel> triangleModel = triangleFactory->CreateModel(triangle, GLType::FLOAT, 3);



    // Check if the ESC keys was pressed or the window was closed
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0)
    {
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
        // draw our first triangle
        glUseProgram(shaderProgram);
        triangleModel->Render();
        glfwSwapBuffers(window); // wap the color buffer (a large 2D buffer that contains color values for each pixel in GLFW's window) that is used to render to during this render iteration and show it as output to the screen.
        glfwPollEvents();
    }

    // Cleans up all the resources before it closes window
    glfwTerminate();


    return 0;
}
