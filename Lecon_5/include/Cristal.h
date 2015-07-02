#pragma once
// Includes OpenGL
#include <GL/glew.h>
// Includes GLM
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// Autres includes
#include "Shader.h"
#include "Texture.h"

// Classe Cristal
class Cristal
{
    public:

    Cristal(std::string const vertexShader, std::string const fragmentShader, std::string const texture);
    Cristal();

    void afficher(glm::mat4 &projection, glm::mat4 &modelview);


    private:

    Shader m_shader;
    Texture m_texture;

    float m_vertices[72];
    float m_coordTexture[48];
};
