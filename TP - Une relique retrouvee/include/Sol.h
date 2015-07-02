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

// Classe Sol
class Sol
{
    public:

    Sol(float longueur, float largeur, int repetitionLongueur, int repetitionLargeur, std::string const vertexShader, std::string const fragmentShader, std::string const texture);
    ~Sol();

    void afficher(glm::mat4 &projection, glm::mat4 &modelview);


    private:

    Shader m_shader;
    Texture m_texture;

    float m_vertices[18];
    float m_coordTexture[12];
};
