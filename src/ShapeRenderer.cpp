#include "ShapeRenderer.h"






ShapeRenderer::ShapeRenderer(GLFWwindow* window, std::map<ModelShapes, std::shared_ptr<IModel>>& models) : m_window{window}, m_models_available{models}
{
    this->InitTransformationMatrices();
    const char* glsl_version = "#version 130";
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    ImGui::StyleColorsDark();

}

ShapeRenderer::~ShapeRenderer()
{
}

void ShapeRenderer::Render()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    this->RenderImGuiWindow();

    switch (m_selected_shape)
    {
    case ModelShapes::TRIANGLE:

        m_models_available[ModelShapes::TRIANGLE]->ApplyTransformation(m_transformation_matrices[ModelShapes::TRIANGLE]);
        m_models_available[ModelShapes::TRIANGLE]->Render();
        break;
    case ModelShapes::SQUARE:
        m_models_available[ModelShapes::SQUARE]->ApplyTransformation(m_transformation_matrices[ModelShapes::SQUARE]);
        m_models_available[ModelShapes::SQUARE]->Render();
        break;
    case ModelShapes::CIRCLE:
        m_models_available[ModelShapes::CIRCLE]->ApplyTransformation(m_transformation_matrices[ModelShapes::CIRCLE]);
        m_models_available[ModelShapes::CIRCLE]->Render();
        break;
    case ModelShapes::PIRAMID:
        m_models_available[ModelShapes::PIRAMID]->ApplyTransformation(m_transformation_matrices[ModelShapes::PIRAMID]);
        m_models_available[ModelShapes::PIRAMID]->Render();
        m_selected_shape -= ModelShapes::ALL / 2;
        break;
    default:
        std::cerr << "Not available model for rendering" << std::endl;
        throw("Not available model for rendering");
        break;
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}


void ShapeRenderer::Render3D()
{
    const char* shapes3D[] = { "Piramid","Cube","Shepere" };
    ImGui::Text("Select a shape to render:");
    ImGui::Combo("Selected Shape", &(m_selected_shape), shapes3D, IM_ARRAYSIZE(shapes3D));

    m_selected_shape += ModelShapes::ALL / 2;

    // Camera moving 
    const float radius = 10.0f;
    float camX = sin(glfwGetTime()) * radius;
    float camZ = cos(glfwGetTime()) * radius;

    glm::mat4 view;

    view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0)); // First vector is the position of the camera, second is the target to the camero to point at, and the last one is the up vactor

    /*
    * Camera Position
    * glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);  Camera position z-axis is positve pointing
    * Camera Direction
    * glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);  e.g. at what direction it is pointing at. For now we let the camera point to the origin of our scene: (0,0,0). 
    * glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget); Subtracting the camera position vector from the scene's origin vector thus results in the direction vector we want. 
    * Right Axis
    * glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    * glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection)); we do a cross product on the up vector and the direction vector from step 2
    * Up Axis
    * glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight); etrieving the vector that points to the camera's positive y-axis is relatively easy: we take the cross product of the right and direction vector
    */

    if (m_selected_shape == ModelShapes::PIRAMID)
    {
        // ImGui slider for rotation angle
        /*ImGui::SliderFloat("Rotation Angle Y", &m_rotationAngle.x, 0.0f, 360.0f);
        ImGui::SliderFloat("Rotation Angle X", &m_rotationAngle.y, 0.0f, 360.0f);
        ImGui::SliderFloat("Rotation Angle Z", &m_rotationAngle.z, 0.0f, 360.0f);*/

        ImGui::ColorEdit4("Shape Color", glm::value_ptr(m_color));


        //m_transformation_matrices[ModelShapes::PIRAMID].Rotate(glm::radians(m_rotationAngle.x), 1.0f, 0.0f, 0.0f, AxisRotation::X);
        //m_transformation_matrices[ModelShapes::PIRAMID].Rotate(glm::radians(m_rotationAngle.y), 0.0f, 1.0f, 0.0f, AxisRotation::Y);
        //m_transformation_matrices[ModelShapes::PIRAMID].Rotate(glm::radians(m_rotationAngle.z), 0.0f, 0.0f, 1.0f, AxisRotation::Z);

        // Only set the view matrix once
        //m_transformation_matrices[ModelShapes::PIRAMID].View(0.0f, 0.0f, -3.0f);
        m_transformation_matrices[ModelShapes::PIRAMID].SetCameraViewMatrix(view);

        m_transformation_matrices[ModelShapes::PIRAMID].setColor(m_color);

    }
  

}

void ShapeRenderer::Render2D()
{
    ImGui::Text("Select a shape to render:");

    const char* shapes2D[] = { "Triangle", "Square","Circle"};
    ImGui::Combo("Selected Shape", &m_selected_shape, shapes2D, IM_ARRAYSIZE(shapes2D));


    if (m_selected_shape == ModelShapes::TRIANGLE || m_selected_shape == ModelShapes::SQUARE || m_selected_shape == ModelShapes::CIRCLE)
    {

        // Add which axis to rotate from
        ImGui::SliderFloat("Rotation Angle z-axis", &m_rotationAngle.z, 0.f, 360.f);

        // Which axis to translate the offset
        ImGui::SliderFloat2("Translation Offset", &m_translation.x, 0.0f, 960.0f);

        // Which Coordinate to scale it
        ImGui::SliderFloat2("Scales X", &m_scaling.x, 1.0f, 3.0f);

        ImGui::ColorEdit4("Shape Color", glm::value_ptr(m_color));


        //// Apply alll input to transformation matrices
        for (auto& trans : m_transformation_matrices)
        {
            trans.second.Rotate(glm::radians(m_rotationAngle.z), 0.0, 0.0, 1.0, AxisRotation::Z);

            trans.second.Translate(m_translation.x, m_translation.y, m_translation.z);

            trans.second.Scale(m_scaling.x, m_scaling.y, m_scaling.z);

            trans.second.setColor(m_color);

        }

    }

}

void ShapeRenderer::RenderImGuiWindow()
{
    ImGui::Begin("Shape Selection and Operations");

    ImGui::Text("Select 2D or 3D shapes to render:");

    const char* render_options[] = {"2D","3D"};
    ImGui::Combo("Render", &m_render_option, render_options, IM_ARRAYSIZE(render_options));

    if (m_render_option == ShapeRenderer::Render::TWOD)
    {
        this->Render2D();
    }
    else if (m_render_option == ShapeRenderer::Render::THREED)
    {
        this->Render3D();
    }

    ImGui::End();
}

void ShapeRenderer::InitTransformationMatrices()
{
    // Add transformation matrices available
    m_transformation_matrices[ModelShapes::TRIANGLE] = Transformation();
    m_transformation_matrices[ModelShapes::SQUARE] = Transformation();
    m_transformation_matrices[ModelShapes::CIRCLE] = Transformation();
    m_transformation_matrices[ModelShapes::PIRAMID] = Transformation();
       
}
