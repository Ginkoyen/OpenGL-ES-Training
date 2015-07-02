#pragma once
// Includes OpenGL
#include <GL/glew.h>
// Includes GLM
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// Includes
#include "Shader.h"
// Macro utile au VBO
#ifndef BUFFER_OFFSET
    #define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif

// Classe Cube
class Cube
{
    public:

    Cube(float taille, std::string const vertexShader, std::string const fragmentShader);
    ~Cube();

    void afficher(glm::mat4 &projection, glm::mat4 &modelview);
    void charger();
    void updateVBO(void *donnees, int tailleBytes, int decalage);


    protected:

    Shader m_shader;
    float m_vertices[108];
    float m_couleurs[108];

    GLuint m_vboID;
    int m_tailleVerticesBytes;
    int m_tailleCouleursBytes;
    GLuint m_vaoID;

};
