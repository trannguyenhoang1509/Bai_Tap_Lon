#include "TextureManager.h"
#include <SDL_image.h>
#include <iostream>

SDL_Texture* TextureManager::loadTexture(const std::string& path, SDL_Renderer* renderer) {
    // Tải ảnh vào SDL_Surface
    SDL_Surface* tempSurface = IMG_Load(path.c_str());
    if (!tempSurface) {
        // Log lỗi nếu không thể load ảnh
        std::cerr << "Lỗi load ảnh: " << path << " Error: " << IMG_GetError() << "\n";
        return nullptr;
    }

    // Tạo texture từ surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    if (!texture) {
        // Log lỗi nếu không thể tạo texture
        std::cerr << "Lỗi tạo texture từ surface: " << SDL_GetError() << "\n";
        return nullptr;
    }

    return texture;
}
