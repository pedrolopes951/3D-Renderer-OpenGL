#include <iostream>
#include <memory>
#include <cmath>
#include <map>

#include "Shader.h"
#include "FactoryModels.h"
#include "Models.h"
#include "ShapeRenderer.h"
#include "Camera.h"

#include "Constants.h"



std::shared_ptr<Camera> g_camera;




// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);


static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
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

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
    GLFWwindow* window = glfwCreateWindow((int)WINDOWWIDTH, (int)WINDOWHEIGHT, "Tutorial 02 - Red triangle", NULL, NULL);
    if (window == NULL) {
        fprintf(stderr, "Failed to open GLFW window.\n");
        getchar();
        glfwTerminate();
        return nullptr;

    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    
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

    // Set up OpenGL
    glEnable(GL_DEPTH_TEST);

    return window;
}


static  std::map<ModelShapes, std::shared_ptr<IModel>> InitModels()
{
    // Create samples of shapes to be rendered trinagles
    std::shared_ptr<IModelFactory> triangleFactory = std::make_shared<TriangleFactory>();
    std::shared_ptr<IModelFactory> squareFactory = std::make_shared<SquareFactory>();
    std::shared_ptr<IModelFactory> circleFactory = std::make_shared<CircleFactory>();
    std::shared_ptr<IModelFactory> piramidFactory = std::make_shared<PiramidFactory>();
    std::shared_ptr<IModelFactory> cubeFactory = std::make_shared<CubeFactory>();
    std::shared_ptr<IModelFactory> shepereFactory = std::make_shared<SphereFactory>();



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

    std::vector<Vertex3D> piramid = {
        // Base
       { -0.5f, -0.5f, -0.5f },
       {  0.5f, -0.5f, -0.5f },
       {  0.5f, -0.5f,  0.5f },
       { -0.5f, -0.5f,  0.5f },

       // Front face
       {  0.0f,  0.5f,  0.0f },
       { -0.5f, -0.5f,  0.5f },
       {  0.5f, -0.5f,  0.5f },

       // Right face
       {  0.0f,  0.5f,  0.0f },
       {  0.5f, -0.5f,  0.5f },
       {  0.5f, -0.5f, -0.5f },

       // Back face
       {  0.0f,  0.5f,  0.0f },
       {  0.5f, -0.5f, -0.5f },
       { -0.5f, -0.5f, -0.5f },

       // Left face
       {  0.0f,  0.5f,  0.0f },
       { -0.5f, -0.5f, -0.5f },
       { -0.5f, -0.5f,  0.5f }
    };

    std::vector<Vertex3D> cubeVertices = {
        // Front face
        { -0.5f, -0.5f,  0.5f },
        {  0.5f, -0.5f,  0.5f },
        {  0.5f,  0.5f,  0.5f },
        { -0.5f,  0.5f,  0.5f },

        // Back face
        { -0.5f, -0.5f, -0.5f },
        {  0.5f, -0.5f, -0.5f },
        {  0.5f,  0.5f, -0.5f },
        { -0.5f,  0.5f, -0.5f },
    };
    std::vector<Vertex3D> sphereVertices;

    int numLatitudeDivisions = 20; // Adjust as needed
    int numLongitudeDivisions = 20; // Adjust as needed
    float radius_sphere = 1.0f; // Adjust as needed

    // Generate sphere vertices
    for (int lat = 0; lat <= numLatitudeDivisions; ++lat) {
        for (int lon = 0; lon <= numLongitudeDivisions; ++lon) {
            float theta = static_cast<float>(lat) / numLatitudeDivisions * glm::pi<float>();
            float phi = static_cast<float>(lon) / numLongitudeDivisions * 2.0f * glm::pi<float>();

            float x = radius_sphere * std::sin(theta) * std::cos(phi);
            float y = radius_sphere * std::cos(theta);
            float z = radius_sphere * std::sin(theta) * std::sin(phi);

            sphereVertices.push_back(Vertex3D(x, y, z));
        }
    }

     std::vector<unsigned int> sphereIndices;

     // Generate sphere indices
    for (int lat = 0; lat < numLatitudeDivisions; ++lat) {
        for (int lon = 0; lon < numLongitudeDivisions; ++lon) {
            int current = lat * (numLongitudeDivisions + 1) + lon;
            int next = current + numLongitudeDivisions + 1;

            // Define the two triangles that make up each square on the sphere
            sphereIndices.push_back(current);
            sphereIndices.push_back(next);
            sphereIndices.push_back(current + 1);

            sphereIndices.push_back(next);
            sphereIndices.push_back(next + 1);
            sphereIndices.push_back(current + 1);
        }
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

    std::vector<unsigned int> indicesPiramid = {
       0, 1, 2,
       0, 2, 3,
       4, 5, 6,
       7, 8, 9,
       10, 11, 12,
       13, 14, 15
    };

    std::vector<unsigned int> cubeIndices = {
        // Front face
        0, 1, 2,
        2, 3, 0,

        // Right face
        1, 5, 6,
        6, 2, 1,

        // Back face
        7, 6, 5,
        5, 4, 7,

        // Left face
        4, 0, 3,
        3, 7, 4,

        // Top face
        3, 2, 6,
        6, 7, 3,

        // Bottom face
        4, 5, 1,
        1, 0, 4,
    };




    return  std::map<ModelShapes, std::shared_ptr<IModel>>{{ModelShapes::TRIANGLE, triangleFactory->Create2DModel(triangle, indicesT, GLType::VERTEX2D) }, { ModelShapes::SQUARE, squareFactory->Create2DModel(square, indicesS, GLType::VERTEX2D) },
        { ModelShapes::CIRCLE,circleFactory->Create2DModel(circle, indicesC, GLType::VERTEX2D) }, { ModelShapes::PIRAMID,piramidFactory->Create3DModel(piramid,indicesPiramid,GLType::VERTEX3D) },
        { ModelShapes::CUBE,cubeFactory->Create3DModel(cubeVertices,cubeIndices,GLType::VERTEX3D) },
        { ModelShapes::SHEPERE,shepereFactory->Create3DModel(sphereVertices,sphereIndices,GLType::VERTEX3D) }};

}






static void myImplementation()
{
    g_camera = std::make_shared<Camera>(glm::vec3(0.0f, 0.0f, 3.0f));

    GLFWwindow* window = InitWindow();
    if (!window)
        return;

   auto models = InitModels();

   ShapeRenderer shaperender(window, models, g_camera);


    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0)
    {
        // per-frame time logic
       // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        g_camera->deltaTime= currentFrame - g_camera->lastFrame;
        g_camera->lastFrame = currentFrame;

        // Process the inputs
      // input
      // -----
        processInput(window);
        GLCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
     
        shaperender.Render();

       
        GLCall(glfwSwapBuffers(window)); // wap the color buffer (a large 2D buffer that contains color values for each pixel in GLFW's window) that is used to render to during this render iteration and show it as output to the screen.
        GLCall(glfwPollEvents());
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    // Cleans up all the resources before it closes window
    GLCall(glfwTerminate());
}

int main(void)
{
    myImplementation();


    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        g_camera->ProcessKeyboard(FORWARD, g_camera->deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        g_camera->ProcessKeyboard(BACKWARD, g_camera->deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        g_camera->ProcessKeyboard(LEFT, g_camera->deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        g_camera->ProcessKeyboard(RIGHT, g_camera->deltaTime);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (g_camera->firstMouse)
    {
        g_camera->lastX = xpos;
        g_camera->lastY = ypos;
        g_camera->firstMouse = false;
    }

    float xoffset = xpos - g_camera->lastX;
    float yoffset = g_camera->lastY - ypos; // reversed since y-coordinates go from bottom to top

    g_camera->lastX = xpos;
    g_camera->lastY = ypos;

    g_camera->ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    g_camera->ProcessMouseScroll(static_cast<float>(yoffset));
}
