#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SDL.h>
#include <string>

class TextureManager {
public:
    static SDL_Texture* loadTexture(const std::string& path, SDL_Renderer* renderer);
};

#endif
