#include "SceneOpenGL.h"

SceneOpenGL::SceneOpenGL(std::string titreFenetre, int largeurFenetre, int hauteurFenetre)
{
    m_titreFenetre = titreFenetre;
    m_largeurFenetre = largeurFenetre;
    m_hauteurFenetre = hauteurFenetre;
}

SceneOpenGL::~SceneOpenGL()
{
    SDL_GL_DeleteContext(m_contexteOpenGL);
    SDL_DestroyWindow(m_fenetre);
    SDL_Quit();
}

bool SceneOpenGL::initialiserFenetre()
{
    // Initialisation de la SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << std::endl;
        SDL_Quit();

        return false;
    }

    // Version d'OpenGL
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    // Double Buffer
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    // Création de la fenêtre
    m_fenetre = SDL_CreateWindow(m_titreFenetre.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_largeurFenetre, m_hauteurFenetre, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if(m_fenetre == 0)
    {
        std::cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << std::endl;
        SDL_Quit();

        return false;
    }

    // Création du contexte OpenGL
    m_contexteOpenGL = SDL_GL_CreateContext(m_fenetre);

    if(m_contexteOpenGL == 0)
    {
        std::cout << SDL_GetError() << std::endl;
        SDL_DestroyWindow(m_fenetre);
        SDL_Quit();

        return false;
    }

    return true;
}

bool SceneOpenGL::initGL()
{
    // On initialise GLEW
    GLenum initialisationGLEW( glewInit() );

    // Si l'initialisation a échouée :
    if(initialisationGLEW != GLEW_OK)
    {
        // On affiche l'erreur grâce à la fonction : glewGetErrorString(GLenum code)
        std::cout << "Erreur d'initialisation de GLEW : " << glewGetErrorString(initialisationGLEW) << std::endl;

        // On quitte la SDL
        SDL_GL_DeleteContext(m_contexteOpenGL);
        SDL_DestroyWindow(m_fenetre);
        SDL_Quit();

        return false;
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SceneOpenGL::bouclePrincipale()
{
    // Matrices
    glm::mat4 projection;
    glm::mat4 modelview;

    // Initialisation matrices
    projection = glm::perspective(70.0, (double) m_largeurFenetre/m_hauteurFenetre, 1.0, 100.0);
    modelview = glm::mat4(1.0);

    // Variables
    bool terminer(false);
    float vertices[] = {0.0, 0.0, -1.0,  0.5, 0.0, -1.0,  0.0, 0.5, -1.0};
    float couleurs[] = {240.0/255.0, 210.0/255.0, 23.0/255.0,   230.0/255.0, 0.0, 230.0/255.0,   0.0, 1.0, 0.0};

    Shader shaderCouleur("Shaders/Shaders/couleur3D.vert", "Shaders/Shaders/couleur3D.frag");
    shaderCouleur.charger();

    // Boucle principale
    while(!terminer)
    {
        // Gestion des évènements
        SDL_WaitEvent(&m_evenements);

        if(m_evenements.window.event == SDL_WINDOWEVENT_CLOSE)
            terminer = true;

        // Nettoyage de l'écran
        glClear(GL_COLOR_BUFFER_BIT);

        // Réinitialisation de la matrice modelview
        modelview = glm::mat4(1.0);

        // Activation de l'écran
        glUseProgram(shaderCouleur.getProgramID());

        // On remplie puis on active le tableau Vertex Attrib 0
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices);
        glEnableVertexAttribArray(0);
        // On remplie puis on active le tableau Couleurs Attrib 1
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, couleurs);
        glEnableVertexAttribArray(1);

        // Translation
        //modelview = glm::translate(modelview, glm::vec3(0.4, 0.0, 0.0));
        // Rotation
        //modelview = glm::rotate(modelview, 60.0f, glm::vec3(0.0, 0.0, 1.0));
        // Homothétie
        //modelview = glm::scale(modelview, glm::vec3(1, -1, 1));

        // On envoie les matrices au shader
        glUniformMatrix4fv(glGetUniformLocation(shaderCouleur.getProgramID(), "modelview"), 1, GL_FALSE, glm::value_ptr(modelview));
        glUniformMatrix4fv(glGetUniformLocation(shaderCouleur.getProgramID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

        // On affiche le triangle
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // On désactive les tableaux Vertex Attrib puisque l'on n'en a plus besoin
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(0);

        // Désactivation du shader
        glUseProgram(0);

        // Actualisation de la fenêtre
        SDL_GL_SwapWindow(m_fenetre);
    }
}
