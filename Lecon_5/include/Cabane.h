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

// Classe Cabane
class Cabane
{
    public:

    Cabane(std::string const vertexShader, std::string const fragmentShader);
    ~Cabane();

    void afficher(glm::mat4 &projection, glm::mat4 &modelview);


    private:

    Shader m_shader;
    Texture m_textureMur;
    Texture m_textureToit;

    float m_vertices[99];
    float m_coordTexture[66];
};
