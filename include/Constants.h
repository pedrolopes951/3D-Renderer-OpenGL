#pragma once

#define WINDOWHEIGHT 540.f
#define WINDOWWIDTH 960.f
#define FOV 45.f

#define PI 3.14159265359

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

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


enum ModelShapes
{
    TRIANGLE = 0,
    SQUARE,
    CIRCLE,
    PIRAMID,
    CUBE,
    SHEPERE,
    ALL
};


