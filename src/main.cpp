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
    GLCall(glShaderSource(vertexShader, 1, &vertexShaderSource, NULL));
    GLCall(glCompileShader(vertexShader));
    // check for shader compile errors
    int success;
    char infoLog[512];
    GLCall(glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success));
    if (!success)
    {
        GLCall(glGetShaderInfoLog(vertexShader, 512, NULL, infoLog));
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = GLCall(glCreateShader(GL_FRAGMENT_SHADER));
    GLCall(glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL));
    GLCall( glCompileShader(fragmentShader));
    // check for shader compile errors
    GLCall(glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success));
    if (!success)
    {
        GLCall(glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog));
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    shaderProgram = GLCall(glCreateProgram());
    GLCall(glAttachShader(shaderProgram, vertexShader));
    GLCall( glAttachShader(shaderProgram, fragmentShader));
    GLCall(glLinkProgram(shaderProgram));
    // check for linking errors
    GLCall(glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success));
    if (!success) {
        GLCall(glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog));
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    GLCall(glDeleteShader(vertexShader));
    GLCall(glDeleteShader(fragmentShader));
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

    //// Build Shader
    //unsigned int shaderProgram;
    //Shader(shaderProgram);

    // Create samples of shapes to be rendered trinagles
    std::unique_ptr<IModelFactory> triangleFactory = std::make_unique<TriangleFactory>();
    std::unique_ptr<IModelFactory> squareFactory = std::make_unique<SquareFactory>();

    std::vector<Vertex> triangle =
    {
        Vertex(-0.1f, -0.1f, 0.0f), // Bottom left
        Vertex(0.1f, -0.1f, 0.0f),  // Bottom right
        Vertex(0.0f, 0.1f, 0.0f)   // Top center
    };

    std::vector<Vertex> square =
    {
        Vertex(0.1f, -0.1f, 0.0f),  // Bottom left (positioned to the right of the triangle)
        Vertex(0.2f, -0.1f, 0.0f),  // Bottom right
        Vertex(0.2f, 0.1f, 0.0f),  // Top right
        Vertex(0.1f, 0.1f, 0.0f)   // Top left
    };

    // indices
    std::vector<unsigned int> indicesT =
    { 0,1,2 }; // Draw Triangle
    std::vector<unsigned int> indicesS =
    { 0,1,2,
      2,3,0}; // Draw Triangle


    std::unique_ptr<IModel> triangleModel = triangleFactory->CreateModel(triangle, indicesT,GLType::FLOAT);
    std::unique_ptr<IModel> squareModel = squareFactory->CreateModel(square, indicesS, GLType::FLOAT);

    
    // Check if the ESC keys was pressed or the window was closed
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0)
    {
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
        // draw our first triangle
        //GLCall(glUseProgram(shaderProgram));
        triangleModel->Render();
        squareModel->Render();
        //glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        GLCall(glfwSwapBuffers(window)); // wap the color buffer (a large 2D buffer that contains color values for each pixel in GLFW's window) that is used to render to during this render iteration and show it as output to the screen.
        GLCall(glfwPollEvents());
    }

    // Cleans up all the resources before it closes window
    GLCall(glfwTerminate());


    return 0;
}
