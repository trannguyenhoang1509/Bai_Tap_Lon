#include "Game.h"

int main(int argc, char* argv[]) {
    Game game;

    if (!game.init("Dino Game", 800, 400)) return -1;

    const int FPS = 60;
    const int frameDelay = 1000 / FPS; // Delay cho 60 FPS

    Uint32 frameStart;
    int frameTime;

    while (game.running()) {
        frameStart = SDL_GetTicks(); // Thời gian bắt đầu vòng lặp

        game.handleEvents();
        game.update();
        game.render();

        frameTime = SDL_GetTicks() - frameStart; // Tính thời gian đã trôi qua trong vòng lặp
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime); // Đảm bảo vòng lặp không chạy quá nhanh
        }
    }

    game.clean();
    return 0;
}
