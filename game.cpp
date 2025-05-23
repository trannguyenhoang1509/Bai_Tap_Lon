#include "Game.h"
#include "TextureManager.h"
#include <iostream>

Game::Game() {}
Game::~Game() {}

bool Game::init(const char* title, int width, int height) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cerr << "SDL Initialization Failed: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if (!window) {
        std::cerr << "Window Creation Failed: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        std::cerr << "Renderer Creation Failed: " << SDL_GetError() << std::endl;
        return false;
    }

    // Load textures
    background = TextureManager::loadTexture("background.jpg", renderer);
    mainMenu = TextureManager::loadTexture("menu.png", renderer);
    btnStart = TextureManager::loadTexture("start.png", renderer);
    btnQuit = TextureManager::loadTexture("quit.png", renderer);
    gameOverMenu = TextureManager::loadTexture("gameover.png", renderer);
    btnRestart = TextureManager::loadTexture("restart.png", renderer);
    btnExit = TextureManager::loadTexture("exit.png", renderer);

    dino = new Dino(renderer);

    // Tạo nhiều chướng ngại vật
    for (int i = 0; i < 3; i++) {  // Chúng ta sẽ tạo ra 3 chướng ngại vật ban đầu
        obstacles.push_back(new Obstacle(renderer));
    }

    isRunning = true;
    return true;
}

void Game::handleEvents() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) isRunning = false;

        if (state == GameState::MAIN_MENU && e.type == SDL_MOUSEBUTTONDOWN) {
            int x, y;
            SDL_GetMouseState(&x, &y);

            if (x >= btnStartRect.x && x <= btnStartRect.x + btnStartRect.w &&
                y >= btnStartRect.y && y <= btnStartRect.y + btnStartRect.h) {
                state = GameState::PLAYING;
                resetGame();
            }

            if (x >= btnQuitRect.x && x <= btnQuitRect.x + btnQuitRect.w &&
                y >= btnQuitRect.y && y <= btnQuitRect.y + btnQuitRect.h) {
                isRunning = false;
            }
        } else if (state == GameState::PLAYING && !isGameOver) {
            dino->handleEvent(e);
        } else if (state == GameState::GAME_OVER && e.type == SDL_MOUSEBUTTONDOWN) {
            int x, y;
            SDL_GetMouseState(&x, &y);

            if (x >= btnRestartRect.x && x <= btnRestartRect.x + btnRestartRect.w &&
                y >= btnRestartRect.y && y <= btnRestartRect.y + btnRestartRect.h) {
                resetGame();
                state = GameState::PLAYING;
            }

            if (x >= btnExitRect.x && x <= btnExitRect.x + btnExitRect.w &&
                y >= btnExitRect.y && y <= btnExitRect.y + btnExitRect.h) {
                isRunning = false;
            }
        }
    }
}

void Game::update() {
    if (state == GameState::PLAYING && !isGameOver) {
        dino->update();

        // Cập nhật tất cả các chướng ngại vật
        for (auto& obstacle : obstacles) {
            obstacle->update();
        }

        // Kiểm tra va chạm với tất cả các chướng ngại vật
        for (auto& obstacle : obstacles) {
            if (checkCollision(dino->getRect(), obstacle->getRect())) {
                isGameOver = true;
                state = GameState::GAME_OVER;
                break;
            }
        }
    }
}

void Game::render() {
    SDL_RenderClear(renderer);

    if (state == GameState::MAIN_MENU) {
        SDL_RenderCopy(renderer, mainMenu, nullptr, nullptr);
        SDL_RenderCopy(renderer, btnStart, nullptr, &btnStartRect);
        SDL_RenderCopy(renderer, btnQuit, nullptr, &btnQuitRect);
    } else if (state == GameState::PLAYING) {
        SDL_RenderCopy(renderer, background, nullptr, nullptr);
        dino->render();

        // Vẽ tất cả các chướng ngại vật
        for (auto& obstacle : obstacles) {
            obstacle->render();
        }
    } else if (state == GameState::GAME_OVER) {
        SDL_RenderCopy(renderer, gameOverMenu, nullptr, nullptr);
        SDL_RenderCopy(renderer, btnRestart, nullptr, &btnRestartRect);
        SDL_RenderCopy(renderer, btnExit, nullptr, &btnExitRect);
    }

    SDL_RenderPresent(renderer);
}

void Game::resetGame() {
    delete dino;
    dino = new Dino(renderer);

    // Xóa tất cả các chướng ngại vật hiện tại và tạo lại
    for (auto& obstacle : obstacles) {
        delete obstacle;
    }
    obstacles.clear();
    for (int i = 0; i < 2; i++) {
        obstacles.push_back(new Obstacle(renderer));
    }

    isGameOver = false;
}

bool Game::checkCollision(SDL_Rect a, SDL_Rect b) {
    return SDL_HasIntersection(&a, &b);
}

void Game::clean() {
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(mainMenu);
    SDL_DestroyTexture(btnStart);
    SDL_DestroyTexture(btnQuit);
    SDL_DestroyTexture(gameOverMenu);
    SDL_DestroyTexture(btnRestart);
    SDL_DestroyTexture(btnExit);

    delete dino;

    // Xóa tất cả các chướng ngại vật
    for (auto& obstacle : obstacles) {
        delete obstacle;
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
