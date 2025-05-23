#include "Dino.h"
#include "TextureManager.h"
#include <iostream>

Dino::Dino(SDL_Renderer* renderer)
    : renderer(renderer), velocityY(0), jumpSpeed(-22), isJumping(false) {
    texture = TextureManager::loadTexture("dino.png", renderer);
    rect = { 100, 300, 40, 50 };  // Xuất phát thấp hơn
}

Dino::~Dino() {
    SDL_DestroyTexture(texture);
}

void Dino::handleEvent(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN) {
        // Nhấn W hoặc Space để nhảy
        if ((e.key.keysym.sym == SDLK_w || e.key.keysym.sym == SDLK_SPACE) && !isJumping && rect.y == 300) {
            isJumping = true;
            velocityY = jumpSpeed;
        }
    }
}

void Dino::update() {
    if (isJumping) {
        velocityY += 1;       // Mô phỏng trọng lực
        rect.y += velocityY;

        // Khi chạm đất thì reset lại trạng thái
        if (rect.y >= 300) {
            rect.y = 300;
            velocityY = 0;
            isJumping = false;
        }
    }
}

void Dino::render() {
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

SDL_Rect Dino::getRect() const {
    return rect;
}

void Dino::setSpeed(int newSpeed) {
    jumpSpeed = newSpeed;
}

