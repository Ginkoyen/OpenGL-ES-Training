#include "../Include/SceneOpenGL.h"

// Permet d'éviter la ré-écriture du namespace glm::
using namespace glm;

// Constructeur de Destucteur
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

// Méthodes
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
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);


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

        // Si l'initialisation a échoué :
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

    // Activation du Depth Buffer
    glEnable(GL_DEPTH_TEST);

    // Tout s'est bien passé, on retourne true
    return true;
}

void SceneOpenGL::bouclePrincipale()
{
    // Variables
    unsigned int frameRate (1000 / 50);
    Uint32 debutBoucle(0), finBoucle(0), tempsEcoule(0);

    // Matrices
    mat4 projection;
    mat4 modelview;

    projection = perspective(70.0, (double) m_largeurFenetre / m_hauteurFenetre, 1.0, 100.0);
    modelview = mat4(1.0);

    // Caméra mobile
    Camera camera(vec3(3, 4, 10), vec3(0, 2.1, 2), vec3(0, 1, 0), 0.5, 0.5);
    m_input.afficherPointeur(false);
    m_input.capturerPointeur(true);

    // Cabanne
    Cabane cabane("Shaders/texture.vert", "Shaders/texture.frag");

    // Sols
    Sol solHerbeux(30.0, 30.0, 15, 15, "Shaders/texture.vert", "Shaders/texture.frag", "Textures/Herbe.jpg");
    Sol solTerreux(10.0, 10.0, 5, 5, "Shaders/texture.vert", "Shaders/texture.frag", "Textures/Sol.jpg");

    // Caisses
    Caisse caisse(2.0, "Shaders/texture.vert", "Shaders/texture.frag", "Textures/Caisse2.jpg");
    caisse.charger();
    Caisse caisseDanger(2.0, "Shaders/texture.vert", "Shaders/texture.frag", "Textures/Caisse.jpg");
    caisseDanger.charger();

    // Cristal
    Cristal cristal("Shaders/texture.vert", "Shaders/texture.frag", "Textures/Cristal.tga");
    float angle(0.0);

    // Boucle principale
    while(!m_input.terminer())
    {
        // On définit le temps de début de boucle
        debutBoucle = SDL_GetTicks();

        // Gestion des évènements
        m_input.updateEvenements();

        if(m_input.getTouche(SDL_SCANCODE_ESCAPE))
            break;

        camera.deplacer(m_input);

        // Nettoyage de l'écran
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Gestion de la caméra
        camera.lookAt(modelview);


        /* ***** Rendu ***** */

        // Affichage de la cabane
        cabane.afficher(projection, modelview);

        // Affichage du sol terreux
        solTerreux.afficher(projection, modelview);

        // Affichage du sol herbeux
        mat4 sauvegardeModelview = modelview;

            modelview = translate(modelview, vec3(0, -0.01, 0));
            solHerbeux.afficher(projection, modelview);

        modelview = sauvegardeModelview;

        // Sauvegarde de la matrice
        sauvegardeModelview = modelview;

            // Première caisse
            modelview = translate(modelview, vec3(-2.5, 1, -3));
            caisse.afficher(projection, modelview);

            // Deuxième caisse
            modelview = translate(modelview, vec3(5, 0, 1));
            caisseDanger.afficher(projection, modelview);

            // Troisième caisse
            modelview = translate(modelview, vec3(-2.5, 0, 4));
            caisse.afficher(projection, modelview);

            // Rotation du cristal
            angle++;

            if(angle > 360)
                angle -= 360;

            // Affichage du cristal
            modelview = translate(modelview, vec3(0, 2.1, 0));
            modelview = rotate(modelview, angle, vec3(0, 1, 0));

            cristal.afficher(projection, modelview);

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
