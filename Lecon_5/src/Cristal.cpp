#include "../Include/Cristal.h"

// Permet d'éviter la ré-écriture du namespace glm::
using namespace glm;

// Constructeur et Destructeur
Cristal::Cristal(std::string const vertexShader, std::string const fragmentShader, std::string const texture) : m_shader(vertexShader, fragmentShader), m_texture(texture)
{
    // Chargement du shader
    m_shader.charger();

    // Chargement de la texture
    m_texture.charger();

    // Vertices temporaires
    float verticesTmp[] = {-0.5, 0, -0.5,   0.5, 0, -0.5,   0, 1, 0,      // Triangle 1
                           0.5, 0, -0.5,   0.5, 0, 0.5,  0, 1, 0,         // Triangle 2
                           0.5, 0, 0.5,   -0.5, 0, 0.5,   0, 1, 0,        // Triangle 3
                           -0.5, 0, 0.5,   -0.5, 0, -0.5,   0, 1, 0,      // Triangle 4

                           -0.5, 0, -0.5,   0.5, 0, -0.5,   0, -1, 0,     // Triangle 5
                           0.5, 0, -0.5,   0.5, 0, 0.5,  0, -1, 0,        // Triangle 6
                           0.5, 0, 0.5,   -0.5, 0, 0.5,   0, -1, 0,       // Triangle 7
                           -0.5, 0, 0.5,   -0.5, 0, -0.5,   0, -1, 0};    // Triangle 8

    // Coordonnées de texture temporaires
    float coordTexture[] = {0, 0,   0.5, 0,   0.5, 0.5,      // Triangle 1
                            0, 0,   0.5, 0,   0.5, 0.5,      // Triangle 2
                            0, 0,   0.5, 0,   0.5, 0.5,      // Triangle 3
                            0, 0,   0.5, 0,   0.5, 0.5,      // Triangle 4
                            0, 0,   0.5, 0,   0.5, 0.5,      // Triangle 5
                            0, 0,   0.5, 0,   0.5, 0.5,      // Triangle 6
                            0, 0,   0.5, 0,   0.5, 0.5,      // Triangle 7
                            0, 0,   0.5, 0,   0.5, 0.5};     // Triangle 8

    // Copie des vertices
    for(int i(0); i < 72; i++)
        m_vertices[i] = verticesTmp[i];

    // Copie des coordonnées
    for(int i(0); i < 48; i++)
        m_coordTexture[i] = coordTexture[i];
}

// Méthodes
void Cristal::afficher(glm::mat4 &projection, glm::mat4 &modelview)
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

        // Verrouillage de la texture
        glBindTexture(GL_TEXTURE_2D, m_texture.getID());

        // Rendu
        glDrawArrays(GL_TRIANGLES, 0, 24);

        // Déverrouillage de la texture
        glBindTexture(GL_TEXTURE_2D, 0);

        // Désactivation des tableaux
        glDisableVertexAttribArray(2);
        glDisableVertexAttribArray(0);

    // Désactivation du shader
    glUseProgram(0);
}
