#include <iostream>
#include <memory>
#include <cmath>
#include <map>

#include "Shader.h"
#include "FactoryModels.h"
#include "Models.h"
#include "ShapeRenderer.h"

#include "Constants.h"

// Vertex Shader source
static const char* vertexShaderSourceTest = R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;

    uniform mat4 transformation;

    void main()
    {
	    gl_Position = transformation * vec4(aPos, 1.0f);
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





    return  std::map<ModelShapes, std::shared_ptr<IModel>>{{ModelShapes::TRIANGLE, triangleFactory->Create2DModel(triangle, indicesT, GLType::VERTEX2D) }, { ModelShapes::SQUARE, squareFactory->Create2DModel(square, indicesS, GLType::VERTEX2D) }, { ModelShapes::CIRCLE,circleFactory->Create2DModel(circle, indicesC, GLType::VERTEX2D) },{ ModelShapes::PIRAMID,piramidFactory->Create3DModel(piramid,indicesPiramid,GLType::VERTEX3D) }};

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
   


    std::vector<Vertex3D> vertices = {
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

    std::vector<unsigned int> indices = {
        0, 1, 2,
        0, 2, 3,
        4, 5, 6,
        7, 8, 9,
        10, 11, 12,
        13, 14, 15
    };

    GLFWwindow* window = InitWindow();
    

    // Set up vertex array and buffer
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex3D), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void*)0);
    glEnableVertexAttribArray(0);

    // Shader program
    GLuint shaderProgram = createShaderProgram();
    glUseProgram(shaderProgram);

    // Render loop
    while (!glfwWindowShouldClose(window)) {
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

        // create transformations
        glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        projection = glm::perspective(glm::radians(45.0f), (float)WINDOWHEIGHT / (float)WINDOWWIDTH, 0.1f, 100.0f);

        glm::mat4 transformation = projection * view * model;


        glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"transformation"), 1, GL_FALSE, &transformation[0][0]);


        // render pyramid
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glfwTerminate();
}

static void myImplementation()
{
    GLFWwindow* window = InitWindow();
    if (!window)
        return;

   auto models = InitModels();

   ShapeRenderer shaperender(window, models);

    std::vector<Vertex3D> vertices = {
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

    std::vector<unsigned int> indices = {
       0, 1, 2,
       0, 2, 3,
       4, 5, 6,
       7, 8, 9,
       10, 11, 12,
       13, 14, 15
    };

    // Set up vertex array and buffer
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex3D), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void*)0);
    glEnableVertexAttribArray(0);

    // Shader program
   /* GLuint shaderProgram = createShaderProgram();
    glUseProgram(shaderProgram);*/

    // VAO
    /*VertexArray<Vertex3D> m_vao;
    VertexBuffer<Vertex3D> m_vbo(vertices);
    ElementBuffer m_eb{indices};
    m_vao.Bind();
    m_vbo.Bind();
    m_eb.Bind();
    
    VertexBufferLayout m_layout;
    
    m_layout.AddVertex3D(3);
    m_vao.AddBuffer(m_vbo, m_layout, GLType::VERTEX3D);



    Shader shader("shaders/Basic.shader");
    shader.Bind();
    shader.SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);*/


    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0)
    {
        GLCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
     
        shaperender.Render();

        //glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 view = glm::mat4(1.0f);
        //glm::mat4 projection = glm::mat4(1.0f);
        //model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
        //view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        //projection = glm::perspective(glm::radians(45.0f), (float)WINDOWHEIGHT / (float)WINDOWWIDTH, 0.1f, 100.0f);

        //glm::mat4 transformation_matrix = projection * view * model;

        //glUniformMatrix4fv(glGetUniformLocation(shader.getID(), "transformation"), 1, GL_FALSE, &transformation_matrix[0][0]);


        ////glBindVertexArray(VAO);
        //m_vao.Bind();
        //glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);


     
        GLCall(glfwSwapBuffers(window)); // wap the color buffer (a large 2D buffer that contains color values for each pixel in GLFW's window) that is used to render to during this render iteration and show it as output to the screen.
        GLCall(glfwPollEvents());

        //glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

        //// create transformations
        //glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 view = glm::mat4(1.0f);
        //glm::mat4 projection = glm::mat4(1.0f);
        //model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
        //view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        //projection = glm::perspective(glm::radians(45.0f), (float)WINDOWHEIGHT / (float)WINDOWWIDTH, 0.1f, 100.0f);

        //glm::mat4 transformation = projection * view * model;

        //glUniformMatrix4fv(glGetUniformLocation(shader.getID(), "transformation"), 1, GL_FALSE, &transformation[0][0]);


        //// render pyramid
        //glBindVertexArray(VAO);
        //glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);

        //// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        //// -------------------------------------------------------------------------------
        //glfwSwapBuffers(window);
        //glfwPollEvents();
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


  // TesttheFuckingPiramid();

    return 0;
}
