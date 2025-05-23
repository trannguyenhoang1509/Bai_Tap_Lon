#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SDL.h>

class Obstacle {
public:
    Obstacle(SDL_Renderer* renderer);
    ~Obstacle();

    void update();
    void render();
    SDL_Rect getRect() const;

private:
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_Rect rect;

    const int speed = 5;
};

#endif
