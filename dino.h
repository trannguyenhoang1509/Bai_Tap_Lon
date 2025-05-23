#ifndef DINO_H
#define DINO_H

#include <SDL.h>

class Dino {
public:
    Dino(SDL_Renderer* renderer);
    ~Dino();

    void handleEvent(SDL_Event& e);
    void update();
    void render();
    SDL_Rect getRect() const;
    void setSpeed(int newSpeed);

private:
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_Rect rect;

    int velocityY;      // Vận tốc theo trục Y
    int jumpSpeed;      // Tốc độ nhảy
    bool isJumping;     // Đang trong trạng thái nhảy
};

#endif
