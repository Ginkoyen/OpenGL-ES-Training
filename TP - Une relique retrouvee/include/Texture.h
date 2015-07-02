#pragma once
// Include
#include <GL/glew.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <string>

// Classe Textures
class Texture
{
    public:

    Texture();
    Texture(Texture const &textureACopier);
    Texture(std::string fichierImage);
    ~Texture();

    Texture& operator=(Texture const &textureACopier);
    bool charger();
    SDL_Surface* inverserPixels(SDL_Surface *imageSource) const;

    GLuint getID() const;
    void setFichierImage(const std::string &fichierImage);


    private:

    GLuint m_id;
    std::string m_fichierImage;
};
