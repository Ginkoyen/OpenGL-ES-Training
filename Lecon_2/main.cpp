#include "SceneOpenGL.h"

int main(int argc, char **argv)
{
    // Cr�ation de la s�ne
    SceneOpenGL scene("Chapitre 3", 800, 600);

    // Initialisation de la sc�ne
    if(scene.initialiserFenetre() == false)
	return -1;

	if(scene.initGL() == false)
	return -1;

    // Boucle Principale
    scene.bouclePrincipale();

    return 0;
}
