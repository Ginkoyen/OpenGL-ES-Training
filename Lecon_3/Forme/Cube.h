#pragma once

// Includes OpenGL
#include <GL/glew.h>

// Includes GLM
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// includes
#include "../Shaders/Shader.h"

class Cube
{
    public :
    Cube(float taille, std::string const vertexShader, std::string const fragmentShader);
    ~Cube();
    void afficher(glm::mat4 &projection, glm::mat4 &modelview);
    private :
    Shader m_shader;
    float m_vertices[108];
    float m_couleurs[108];
};
