#include "Obstacle.h"
#include "TextureManager.h"
#include <cstdlib>

Obstacle::Obstacle(SDL_Renderer* renderer) : renderer(renderer), speed(6) {  // Tốc độ cố định
    texture = TextureManager::loadTexture("cactus.png", renderer);
    rect = { 800, 300, 40, 50 };  // Đặt thấp hơn (giống Dino)
}

Obstacle::~Obstacle() {
    SDL_DestroyTexture(texture);
}

void Obstacle::update() {
    rect.x -= speed;  // Di chuyển chướng ngại vật

    // Nếu chướng ngại vật ra ngoài màn hình, reset lại vị trí từ bên phải
    if (rect.x + rect.w < 0) {
       rect.x = 800 + rand() % 200;
    }
}

void Obstacle::render() {
    SDL_RenderCopy(renderer, texture, NULL, &rect);  // Vẽ chướng ngại vật lên màn hình
}

SDL_Rect Obstacle::getRect() const {
    return rect;
}
