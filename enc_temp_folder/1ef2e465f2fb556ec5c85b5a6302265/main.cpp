// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "FactoryModels.h"
#include "Models.h"
#include <iostream>
#include <memory>
#include <cmath>

#include <glm/glm.hpp>
// glm::translate, glm::rotate, glm::scale
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include <glm/gtx/string_cast.hpp>



#define PI 3.14159265359

// Vertex shaders process vertex data, while fragment shaders determine the final color of each pixel.

void OperationsGlMath()
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


void MatrixOperations()
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

    // All all transformation together - 1- Translate then rotate then scale

    //model = models * modelr * modelt;

    model = modelt * modelr * models;


    glm::vec4 worldspace_vertex = (model * vertex);

    std::cout << "\n" << "our vertex in world space\n";
    std::cout << glm::to_string(worldspace_vertex) << std::endl;






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
    std::unique_ptr<IModelFactory> circleFactory = std::make_unique<CircleFactory>();




    std::vector<Vertex2D> triangle =
    {
        Vertex2D(0.0f, 0.0f), //Bottom left
        Vertex2D(100.0f, 0.0f),  // Bottom right
        Vertex2D(50.0f, 100.0) // Top center
    };

    std::vector<Vertex2D> square =
    {
        Vertex2D(0.1f, -0.1f), // Bottom left (positioned to the right of the triangle)
        Vertex2D(0.2f, -0.1f), // Bottom right
        Vertex2D(0.2f, 0.1f), // Top right
        Vertex2D(0.1f, 0.1f) // Top left
    };

    // Circle position
    std::vector<Vertex2D> circle;

    int numSegment = 36; // Number of positions to draw the circle
    float radius = 0.05f;
    float xOffset = -0.2f; // Offset to position the circle to the left of tringle

    // 0 <=theta <= 2pi
    // X = radius * cos(theta) position that circle can assume in x axis
    // Y = radious * sen(theta) position that circle can assume in y axis

    // Fill up the possition of the circle
    for (int i = 0; i <= numSegment; i++)
    {
        float theta = 2.0f * PI * float(i) / float(numSegment);
        float x = radius * cos(theta) + xOffset;
        float y = radius * sin(theta);



        circle.push_back(Vertex2D(x, y));
    }



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

    // Some Basic Math Operations
   // OperationsGlMath();

    // Matrix operations
    MatrixOperations();



    //Shader shader("shaders/Basic.shader");
    /*shader.Bind();
    shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);*/

    std::unique_ptr<IModel> triangleModel = triangleFactory->Create2DModel(triangle, indicesT, GLType::VERTEX2D);
    std::unique_ptr<IModel> squareModel = squareFactory->Create2DModel(square, indicesS, GLType::VERTEX2D);
    std::unique_ptr<IModel> circleModel = circleFactory->Create2DModel(circle, indicesC, GLType::VERTEX2D);

    Transformation transformation;

    // Apply transformations to the transformation object
    //transformation.Translate(2.0f, 0.0f, 0.0f);
    //transformation.Rotate(0.0f, 0.0f, 0.0f, 1.0f);
    //transformation.Scale(1.0f, 1.0f, 0.0f);
    transformation.Ortho(0.0f,960.0f,0.0f,540.f); // Orthographic 

    //shader.Unbind();
    // Check if the ESC keys was pressed or the window was closed
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0)
    {
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
      
        triangleModel->ApplyTransformation(transformation);
        triangleModel->Render();
        //squareModel->Render();
        //circleModel->Render();
        //glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        GLCall(glfwSwapBuffers(window)); // wap the color buffer (a large 2D buffer that contains color values for each pixel in GLFW's window) that is used to render to during this render iteration and show it as output to the screen.
        GLCall(glfwPollEvents());
    }

    // Cleans up all the resources before it closes window
    GLCall(glfwTerminate());


    return 0;
}
