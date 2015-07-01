#include "SceneOpenGL.h"
#include "Cube.h"
#include "Input.h"

SceneOpenGL::SceneOpenGL(std::string titreFenetre, int largeurFenetre, int hauteurFenetre) : m_titreFenetre(titreFenetre), m_largeurFenetre(largeurFenetre),
                                                                                             m_hauteurFenetre(hauteurFenetre), m_fenetre(0), m_contexteOpenGL(0), m_input()
{

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

    //Activation du Depth Buffer
    glEnable(GL_DEPTH_TEST);

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SceneOpenGL::bouclePrincipale()
{
    unsigned int frameRate(1000/50);
    Uint32 debutBoucle(0), finBoucle(0), tempsEcoule(0);

    // Matrices
    glm::mat4 projection;
    glm::mat4 modelview;
    projection = glm::perspective(70.0, (double) m_largeurFenetre / m_hauteurFenetre, 1.0, 100.0);
    modelview = glm::mat4(1.0);

    // Déclaration d'un objet Cube
    Cube cube(2.0, "Include/Shaders/couleur3D.vert", "Include/Shaders/couleur3D.frag");

    // Variable angle
    float angleX(0.0);
    float angleY(0.0);

    // Boucle principale
    while(!m_input.terminer())
    {
        // On définit le temps de début de la boucle
        debutBoucle = SDL_GetTicks();

        // Gestion des évènements
        m_input.updateEvenements();

        if(m_input.getTouche(SDL_SCANCODE_ESCAPE))
            break;


        // Rotation du cube vers la gauche
        if(m_input.getTouche(SDL_SCANCODE_A))
        {
            angleY -= 5;

            if(angleY > 360)
                angleY -= 360;
        }
        // Rotation du cube vers la droite
        if(m_input.getTouche(SDL_SCANCODE_D))
        {
            angleY += 5;

            if(angleY < -360)
                angleY += 360;
        }
        // Rotation du cube vers le haut
        if(m_input.getTouche(SDL_SCANCODE_W))
        {
        angleX -= 5;

            if(angleX > 360)
                angleX -= 360;
        }
        // Rotation du cube vers le bas
        if(m_input.getTouche(SDL_SCANCODE_S))
        {
            angleX += 5;

            if(angleX < -360)
                angleX += 360;
        }


        // Nettoyage de l'écran
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Placement de la caméra
        modelview = glm::lookAt(glm::vec3(3, 3, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));


        // Sauvegarde de la matrice
        glm::mat4 sauvegardeModelview = modelview;


            modelview = glm::rotate(modelview, angleY, glm::vec3(0, 1, 0));
            modelview = glm::rotate(modelview, angleX, glm::vec3(1, 0, 0));
            // Affichage du cube
            cube.afficher(projection, modelview);

        // Restauration de la matrice
        modelview = sauvegardeModelview;


        // Actualisation de la fenêtre
        SDL_GL_SwapWindow(m_fenetre);

        // Calcul du temps écoulé
        finBoucle = SDL_GetTicks();
        tempsEcoule = finBoucle - debutBoucle;

        // Si nécessaire, on met en pause le programme
        if(tempsEcoule < frameRate)
            SDL_Delay(frameRate - tempsEcoule);
    }
}
