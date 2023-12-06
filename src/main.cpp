#include <iostream>
#include <memory>
#include <cmath>
#include <map>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "FactoryModels.h"
#include "Models.h"
#include "ShapeRenderer.h"

#include <glm/glm.hpp>
// glm::translate, glm::rotate, glm::scale
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>


// glm::translate, glm::rotate, gl
// GUI
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"


#include "Constants.h"

// Vertex Shader source
static const char* vertexShaderSourceTest = R"(
    #version 330 core
    layout(location = 0) in vec3 aPos;
    uniform mat4 u_Transform;
    void main()
    {
        gl_Position = u_Transform * vec4(aPos, 1.0);
    }
)";

// Fragment Shader source
static const char* fragmentShaderSourceTest = R"(
    #version 330 core
    out vec4 FragColor;
    void main()
    {
        FragColor = vec4(1.0, 1.0, 1.0, 1.0);
    }
)";


// Vertex shaders process vertex data, while fragment shaders determine the final color of each pixel.

static void OperationsGlMath()
{
    // Summary : 2d/3D vecs, normalizing, dot(Computation of angle) and cross product(New Perpendicular vector)

    // Create Vector
    glm::vec3 A(4.0f, 0.0f, 0.0f);
    glm::vec3 B(0.0f, 4.0f, 0.0f);

    // Computation of the lenght of the vec3

    std::cout << "||A|| = " << glm::length(A) << std::endl;

    // Unit vector from A
    std::cout << "A-hgat " << glm::to_string(glm::normalize(A)) << std::endl;

    // Dot product of A and B
    std::cout << "A.B : " << glm::dot(A, B) << std::endl; // 3x0 + 4x7 + 0x0  = 28



    // Dot product of normalized A and normalized B
    float dotproduct = glm::dot(glm::normalize(A), glm::normalize(B));

    std::cout << "dotProduct: " << dotproduct << "\n";
    std::cout << std::acos(dotproduct) * 180 / PI << "\n";


    // For 3D System CrossProduct Right hand system
    glm::vec3 C = glm::cross(A, B);
    std::cout << "Cross product" << glm::to_string(C) << std::endl;


}


static void MatrixOperations()
{
    // Create a vertex, w=1 means we have a position but if w= 0 is a vector
    glm::vec4 vertex(1.0f, 5.0f, 1.0f, 1.f);

    // Create a model matrix for our geometry, in this case it is a identity matrix 
    glm::mat4 model(1.0f);

    // We can then perform operations on this metrix
    // Scalling Matrix

    glm::mat4 models = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 2.0f, 2.0f));

    // Roatation Matrix
    glm::mat4 modelr = glm::rotate(glm::mat4(1.0f),glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // Rotate over the y-axis

    // Translate Matrix building this translation matrix
    glm::mat4 modelt = glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 0.f, -2.f));



    std::cout << glm::to_string(model[0]) << std::endl;
    std::cout << glm::to_string(model[1]) << std::endl;
    std::cout << glm::to_string(model[2]) << std::endl;
    std::cout << glm::to_string(model[3]) << std::endl;

    // Now apply our model matrix to the Vertex

    // All all transformationTriangle together - 1- Translate then rotate then scale

    //model = models * modelr * modelt;

    model = modelt * modelr * models;


    glm::vec4 worldspace_vertex = (model * vertex);

    std::cout << "\n" << "our vertex in world space\n";
    std::cout << glm::to_string(worldspace_vertex) << std::endl;






}

static GLFWwindow* InitWindow()
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
    GLFWwindow* window = glfwCreateWindow((int)WINDOWWIDTH, (int)WINDOWHEIGHT, "Tutorial 02 - Red triangle", NULL, NULL);
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


static  std::map<ModelShapes, std::shared_ptr<IModel>> InitModels()
{
    // Create samples of shapes to be rendered trinagles
    std::shared_ptr<IModelFactory> triangleFactory = std::make_shared<TriangleFactory>();
    std::shared_ptr<IModelFactory> squareFactory = std::make_shared<SquareFactory>();
    std::shared_ptr<IModelFactory> circleFactory = std::make_shared<CircleFactory>();
    std::shared_ptr<IModelFactory> piramidFactory = std::make_shared<PiramidFactory>();



    std::vector<Vertex2D> triangle =
    {
        Vertex2D(-50.0f, 0.0f), //Bottom left
        Vertex2D(50.0f, 0.0f),  // Bottom right
        Vertex2D(0.0f, 50.0f) // Top center
    };

    std::vector<Vertex2D> square =
    {
        Vertex2D(-50.0f, -50.0f), // Bottom left (positioned to the right of the triangle)
        Vertex2D(50.0f, -50.0f), // Bottom right
        Vertex2D(50.0f, 50.0f), // Top right
        Vertex2D(-50.0f, 50.0f) // Top left
    };

    // Circle position
    std::vector<Vertex2D> circle;

    int numSegment = 36; // Number of positions to draw the circle
    float radius = 50.00f;
    float xOffset = 0.0f; // Offset to position the circle to the left of tringle
    float yOffset = 0.0f;

    // 0 <=theta <= 2pi
    // X = radius * cos(theta) position that circle can assume in x axis
    // Y = radious * sen(theta) position that circle can assume in y axis

    // Fill up the possition of the circle
    for (int i = 0; i <= numSegment; i++)
    {
        float theta = 2.0f * PI * float(i) / float(numSegment);
        float x = radius * cos(theta) + xOffset;
        float y = radius * sin(theta) + yOffset;



        circle.push_back(Vertex2D(x, y));
    }

    // Vertices Coordinates
    std::vector<Vertex3D> piramid=
    {
        // Coordinates
        Vertex3D(-50.0f,0.f,50.0f),    // Lower left corner
        Vertex3D(-50.f,0.f,-50.0f),    // Upper left corner
        Vertex3D(50.f,0.f,-50.0f),    // Upper right corner
        Vertex3D(50.f,0.f,50.f),   // Lower right corner
        Vertex3D(0.0,80.f,0.0f)     // Upper Corner

    };


    // indices
    std::vector<unsigned int> indicesT =
    { 0,1,2 }; // Draw Triangle
    std::vector<unsigned int> indicesS =
    { 0,1,2,
      2,3,0 }; // Draw Square
    std::vector<unsigned int> indicesC;

    // Adjust the circle's indices
    for (int i = 0; i <= numSegment; i++) {
        indicesC.push_back(i);
    }

    // Piramid
    std::vector<unsigned int> indicesPiramid =
    {
        0,1,2,
        0,2,3,
        0,1,4,
        1,2,4,
        2,3,4,
        3,0,4
    };




    return  std::map<ModelShapes, std::shared_ptr<IModel>>{{ModelShapes::TRIANGLE, triangleFactory->Create2DModel(triangle, indicesT, GLType::VERTEX2D) }, { ModelShapes::SQUARE, squareFactory->Create2DModel(square, indicesS, GLType::VERTEX2D) }, { ModelShapes::CIRCLE,circleFactory->Create2DModel(circle, indicesC, GLType::VERTEX2D) }, { ModelShapes::PIRAMID,piramidFactory->Create3DModel(piramid,indicesPiramid,GLType::VERTEX3D) }};

}

// Compile and link shaders
static GLuint createShaderProgram() {
    // Vertex Shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSourceTest, NULL);
    glCompileShader(vertexShader);

    // Check vertex shader compilation errors
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "Vertex shader compilation failed:\n" << infoLog << std::endl;
    }

    // Fragment Shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSourceTest, NULL);
    glCompileShader(fragmentShader);

    // Check fragment shader compilation errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "Fragment shader compilation failed:\n" << infoLog << std::endl;
    }

    // Link Shaders
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Check shader program linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "Shader program linking failed:\n" << infoLog << std::endl;
    }

    // Clean up
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}
static void TesttheFuckingPiramid()
{
    //GLFWwindow* window = InitWindow();



    // Vertices Coordinates
    std::vector<Vertex3D> pyramidVertices =
    {
        // Coordinates
       {-50.0f,0.f,50.0f},    // Lower left corner
       {-50.f,0.f,-50.0f},    // Upper left corner
       {50.f,0.f,-50.0f},    // Upper right corner
       {50.f,0.f,50.f},   // Lower right corner
       {0.0,80.f,0.0f}     // Upper Corner

    };

    // Piramid
    std::vector<unsigned int> pyramidIndices =
    {
        0,1,2,
        0,2,3,
        0,1,4,
        1,2,4,
        2,3,4,
        3,0,4
    };

    // Initialize GLFW and GLEW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Pyramid Example", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return;
    }

    
    // Set up OpenGL
    glEnable(GL_DEPTH_TEST);

    // Set up vertex array and buffer
    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex3D) * pyramidVertices.size(), pyramidVertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * pyramidIndices.size(), pyramidIndices.data(), GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Shader program
    GLuint shaderProgram = createShaderProgram();
    glUseProgram(shaderProgram);

    // Render loop
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Update uniform
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 proj = glm::mat4(1.0f);


        view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
        proj = glm::perspective(glm::radians(45.0f), (float)(800 / 600), 0.1f, 100.0f);


        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));  // Rotate

        glm::mat4 transformation = proj * view * model;
        int transloc = glGetUniformLocation(shaderProgram, "u_Transform");
        glUniformMatrix4fv(transloc, 1, GL_FALSE, glm::value_ptr(transformation));

        // Draw pyramid
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, pyramidIndices.size(), GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glfwTerminate();
}

int main(void)
{
    //GLFWwindow* window = InitWindow();
    //if (!window)
    //    return -1;

    //auto models = InitModels();

    //ShapeRenderer shaperender(window, models);
    //
    //while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0)
    //{
    //    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    //    // Disable face culling
    //    GLCall(glDisable(GL_CULL_FACE));
    //    GLCall(glEnable(GL_DEPTH_TEST));



    //    shaperender.Render();
    // 
    //    GLCall(glfwSwapBuffers(window)); // wap the color buffer (a large 2D buffer that contains color values for each pixel in GLFW's window) that is used to render to during this render iteration and show it as output to the screen.
    //    GLCall(glfwPollEvents());
    //}
    //ImGui_ImplOpenGL3_Shutdown();
    //ImGui_ImplGlfw_Shutdown();
    //ImGui::DestroyContext();
    //// Cleans up all the resources before it closes window
    //GLCall(glfwTerminate());


    TesttheFuckingPiramid();

    return 0;
}
