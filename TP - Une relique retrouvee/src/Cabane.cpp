#include "../Include/Cabane.h"

// Permet d'éviter la ré-écriture du namespace glm::
using namespace glm;

// Constructeur et Destructeur
Cabane::Cabane(std::string const vertexShader, std::string const fragmentShader) : m_shader(vertexShader, fragmentShader),
                                                                                   m_textureMur("Textures/Mur.jpg"), m_textureToit("Textures/Toit.jpg")
{
    // Chargement du shader
    m_shader.charger();

    // Chargement des textures
    m_textureMur.charger();
    m_textureToit.charger();

    // Vertices temporaires
    float verticesTmp[] = {-5, 0, -5,   5, 0, -5,   5, 5, -5,      // Mur du Fond
                           -5, 0, -5,   -5, 5, -5,   5, 5, -5,     // Mur du Fond

                           -5, 0, -5,   -5, 0, 5,   -5, 5, 5,      // Mur Gauche
                           -5, 0, -5,   -5, 5, -5,   -5, 5, 5,     // Mur Gauche

                           5, 0, -5,   5, 0, 5,   5, 5, 5,         // Mur Droit
                           5, 0, -5,   5, 5, -5,   5, 5, 5,        // Mur Droit

                           -5, 5, -5,   5, 5, -5,   0, 6, -5,      // Combles

                           -6, 4.8, -6,   -6, 4.8, 6,   0, 6, 6,   // Toit Gauche
                           -6, 4.8, -6,   0, 6, -6,   0, 6, 6,     // Toit Gauche

                           6, 4.8, -6,   6, 4.8, 6,   0, 6, 6,     // Toit Droit
                           6, 4.8, -6,   0, 6, -6,   0, 6, 6};     // Toit Droit

    // Coordonnées de texture temporaires
    float coordTexture[] = {0, 0,   1, 0,   1, 1,        // Mur du Fond
                            0, 0,   0, 1,   1, 1,        // Mur du Fond

                            0, 0,   1, 0,   1, 1,        // Mur Gauche
                            0, 0,   0, 1,   1, 1,        // Mur Gauche

                            0, 0,   1, 0,   1, 1,        // Mur Droit
                            0, 0,   0, 1,   1, 1,        // Mur Droit

                            0, 0,   1, 0,   0.5, 0.5,    // Combles

                            0, 0,   1, 0,   1, 1,        // Toit Gauche
                            0, 0,   0, 1,   1, 1,        // Toit Gauche

                            0, 0,   1, 0,   1, 1,        // Toit Droit
                            0, 0,   0, 1,   1, 1};       // Toit Droit

    // Copie des vertices
    for(int i(0); i < 99; i++)
        m_vertices[i] = verticesTmp[i];

    // Copie des coordonnées
    for(int i(0); i < 66; i++)
        m_coordTexture[i] = coordTexture[i];
}
Cabane::~Cabane(){}

// Méthodes
void Cabane::afficher(glm::mat4 &projection, glm::mat4 &modelview)
{
    // Activation du shader
    glUseProgram(m_shader.getProgramID());

        // Envoi des vertices
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, m_vertices);
        glEnableVertexAttribArray(0);

        // Envoi des coordonnées de texture
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, m_coordTexture);
        glEnableVertexAttribArray(2);

        // Envoi des matrices
        glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelview));

        // Verrouillage de la texture du Mur
        glBindTexture(GL_TEXTURE_2D, m_textureMur.getID());

        // Rendu
        glDrawArrays(GL_TRIANGLES, 0, 21);

        // Déverrouillage de la texture
        glBindTexture(GL_TEXTURE_2D, 0);

        // Verrouillage de la texture du Toit
        glBindTexture(GL_TEXTURE_2D, m_textureToit.getID());

        // Rendu
        glDrawArrays(GL_TRIANGLES, 21, 12);

        // Déverrouillage de la texture
        glBindTexture(GL_TEXTURE_2D, 0);

        // Désactivation des tableaux
        glDisableVertexAttribArray(2);
        glDisableVertexAttribArray(0);

    // Désactivation du shader
    glUseProgram(0);
}
