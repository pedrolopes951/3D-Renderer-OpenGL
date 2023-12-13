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
    const char* shapes3D[] = {"Piramid","Cube","Shepere"};
    ImGui::Text("Select a shape to render:");
    ImGui::Combo("Selected Shape", &(m_selected_shape), shapes3D, IM_ARRAYSIZE(shapes3D));

    m_selected_shape += ModelShapes::ALL/2;
    
   if (m_selected_shape == ModelShapes::PIRAMID)
    {
       float rotationAngleY = 0.0f;  // Initialize the rotation angle
       float rotationAngleX = 0.0f;  // Initialize the rotation angle
       float rotationAngleZ = 0.0f;  // Initialize the rotation angle


        // ImGui slider for rotation angle
        ImGui::SliderFloat("Rotation Angle Y", &rotationAngleY, 0.0f, 360.0f);
        ImGui::SliderFloat("Rotation Angle X", &rotationAngleX, 0.0f, 360.0f);
        ImGui::SliderFloat("Rotation Angle Z", &rotationAngleZ, 0.0f, 360.0f);


        m_transformation_matrices[ModelShapes::PIRAMID].Rotate(glm::radians(rotationAngleY), 0.0f, 1.0f, 0.0f);
        m_transformation_matrices[ModelShapes::PIRAMID].Rotate(glm::radians(rotationAngleX), 1.0f, 0.0f, 0.0f);
        m_transformation_matrices[ModelShapes::PIRAMID].Rotate(glm::radians(rotationAngleZ), 0.0f, 0.0f, 1.0f);


        m_transformation_matrices[ModelShapes::PIRAMID].View(0.0f, 0.0f, -3.0f);

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

        //// Apply alll input to transformation matrices
        for (auto& trans : m_transformation_matrices)
        {
            trans.second.Rotate(glm::radians(m_rotationAngle.z), 0.0, 0.0, 1.0);

            trans.second.Translate(m_translation.x, m_translation.y, m_translation.z);

            trans.second.Scale(m_scaling.x, m_scaling.y, m_scaling.z);

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
