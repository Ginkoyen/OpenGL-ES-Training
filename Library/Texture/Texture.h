#pragma once

// Include
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

// Classe Texture
class Texture
{
    public:
    Texture();
    Texture(Texture const &textureACopier);
    Texture(std::string fichierImage);
    ~Texture();
    bool charger();
    GLuint getID() const;
    void setFichierImage(const std::string &fichierImage);
    Texture& operator=(Texture const &textureACopier);

    private:
    GLuint m_id;
    std::string m_fichierImage;
    SDL_Surface* inverserPixels(SDL_Surface *imageSource) const;
};
