#include "../Include/Sol.h"

// Permet d'éviter la ré-écriture du namespace glm::
using namespace glm;

// Constructeur de Destructeur
Sol::Sol(float longueur, float largeur, int repetitionLongueur, int repetitionLargeur, std::string const vertexShader, std::string const fragmentShader, std::string const texture) :
         m_shader(vertexShader, fragmentShader), m_texture(texture)
{
    // Chargement du shader
    m_shader.charger();

    // Chargement de la texture
    m_texture.charger();

    // Division de la taille
    longueur /= 2.0;
    largeur /= 2.0;

    // Vertices temporaires
    float verticesTmp[] = {-longueur, 0, -largeur,   longueur, 0, -largeur,   longueur, 0, largeur,     // Triangle 1
                           -longueur, 0, -largeur,   -longueur, 0, largeur,   longueur, 0, largeur};    // Triangle 2

    // Coordonnées de texture temporaires
    float coordTexture[] = {0, 0,   repetitionLongueur, 0,   repetitionLongueur, repetitionLargeur,      // Triangle 1
                            0, 0,   0, repetitionLargeur,   repetitionLongueur, repetitionLargeur};      // Triangle 2

    // Copie des vertices
    for(int i(0); i < 18; i++)
        m_vertices[i] = verticesTmp[i];

    // Copie des coordonnées
    for(int i(0); i < 12; i++)
        m_coordTexture[i] = coordTexture[i];
}
Sol::~Sol(){}

// Méthodes
void Sol::afficher(glm::mat4 &projection, glm::mat4 &modelview)
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
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // Déverrouillage de la texture
        glBindTexture(GL_TEXTURE_2D, 0);

        // Désactivation des tableaux
        glDisableVertexAttribArray(2);
        glDisableVertexAttribArray(0);

    // Désactivation du shader
    glUseProgram(0);
}
