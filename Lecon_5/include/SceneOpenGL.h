#pragma once
// Includes
#include <GL/glew.h>
// Includes GLM
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// Autres includes
#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include "Shader.h"
#include "Cube.h"
#include "Input.h"
#include "Texture.h"
#include "Caisse.h"
#include "Camera.h"
#include "Cabane.h"
#include "Sol.h"
#include "Cristal.h"

// Classe
class SceneOpenGL
{
    public:

    SceneOpenGL(std::string titreFenetre, int largeurFenetre, int hauteurFenetre);
    ~SceneOpenGL();

    bool initialiserFenetre();
    bool initGL();
    void bouclePrincipale();


    private:

    std::string m_titreFenetre;
    int m_largeurFenetre;
    int m_hauteurFenetre;

    SDL_Window* m_fenetre;
    SDL_GLContext m_contexteOpenGL;
    SDL_Event m_evenements;
    Input m_input;
};
