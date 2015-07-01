#pragma once

// Includes
#include <SDL2/SDL.h>

class Input
{
    public :
    Input();
    ~Input();
    void updateEvenements();
    bool terminer() const;

    private :
    SDL_Event m_evenements;
    bool m_touches[SDL_NUM_SCANCODES];
    bool m_boutonsSouris[8];

    int m_x;
    int m_y;
    int m_xRel;
    int m_yRel;

    bool m_terminer;
};
