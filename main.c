#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

#define TITLE "Minha primeira Tela SDL"
#define WIDTH 600
#define HEIGHT 800

struct {
    SDL_Window *window;
    SDL_Surface *surface;
} typedef Game;

void clean_game(Game *game, int status);
bool initialize_sdl(Game *game);

int main(void) {
    Game game = {
        .window = NULL,
        .surface = NULL,
    };
    if (initialize_sdl(&game)) {
        clean_game(&game, EXIT_FAILURE);
    }

    while (true) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    clean_game(&game, EXIT_SUCCESS);
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.scancode) {
                        case SDL_SCANCODE_ESCAPE:
                            clean_game(&game, EXIT_SUCCESS);
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
        }


        SDL_FillRect(game.surface, NULL, SDL_MapRGB(game.surface->format, 0xFF, 0xFF, 0xFF));

        SDL_UpdateWindowSurface(game.window);

        SDL_Delay(16);

    }

    clean_game(&game, EXIT_SUCCESS);

    return 0;
}

void clean_game(Game *game, const int status) {
    // SDL_DestroyRenderer(game->renderer);
    SDL_DestroyWindow(game->window);
    SDL_Quit();
    exit(status);
}

bool initialize_sdl(Game *game) {
    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        fprintf(stderr, "Erro ao iniciar o SDL: %s\n", SDL_GetError());
        return true;
    }

    game->window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    if (!game->window) {
        fprintf(stderr, "Erro ao iniciar o Windows: %s\n", SDL_GetError());
        return true;
    }

    game->surface = SDL_GetWindowSurface(game->window);

    return false;
}