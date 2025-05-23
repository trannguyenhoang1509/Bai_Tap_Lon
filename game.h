#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <vector>
#include "Dino.h"
#include "Obstacle.h"

enum class GameState {
    MAIN_MENU,
    PLAYING,
    GAME_OVER
};

class Game {
public:
    Game();
    ~Game();

    bool init(const char* title, int width, int height);
    void handleEvents();
    void update();
    void render();
    void clean();
    bool running() const { return isRunning; }

private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    SDL_Texture* background = nullptr;
    SDL_Texture* mainMenu = nullptr;
    SDL_Texture* btnStart = nullptr;
    SDL_Texture* btnQuit = nullptr;
    SDL_Texture* gameOverMenu = nullptr;
    SDL_Texture* btnRestart = nullptr;
    SDL_Texture* btnExit = nullptr;

    SDL_Rect btnStartRect = { 300, 200, 200, 50 };
    SDL_Rect btnQuitRect = { 300, 270, 200, 50 };
    SDL_Rect btnRestartRect = { 300, 200, 200, 50 };
    SDL_Rect btnExitRect = { 300, 270, 200, 50 };

    Dino* dino = nullptr;
    std::vector<Obstacle*> obstacles;  // Sử dụng vector để chứa nhiều chướng ngại vật

    bool isRunning = false;
    bool isGameOver = false;
    GameState state = GameState::MAIN_MENU;

    void resetGame();
    bool checkCollision(SDL_Rect a, SDL_Rect b);
};

#endif
