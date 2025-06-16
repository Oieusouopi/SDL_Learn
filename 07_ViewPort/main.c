#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
//
// Created by eec on 15/06/25.
//

#define WIDTH 800
#define HEIGHT 600

// Janela Global
SDL_Window* gWindow = NULL;

// Renderizador Global
SDL_Renderer* gRenderer = NULL;

// Carregar midia
bool loadMedia();

// Inicializador SDL
bool init();

// Fechar SDL
void close_SDL(int status);

int main() {
    if (init()) {
        printf("Deu algo errado");
        close_SDL(EXIT_FAILURE);
    }

    while (true) {
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                close_SDL(EXIT_SUCCESS);
            }
        }
    }

}

bool init() {
    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        fprintf(stderr, "Deu erro ao inciar o SDL: %s\n", SDL_GetError());
        return true;
    }

    gWindow = SDL_CreateWindow("07_ViewPort", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

    if (!gWindow) {
        fprintf(stderr, "Deu erro ao iniciar a janela: %s\n", SDL_GetError());
        return true;
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

    if (!gRenderer) {
        fprintf(stderr, "Deu erro ao iniciar o renderizador: %s\n", SDL_GetError());
        return true;
    }

    return false;
}

void close_SDL(int status) {
    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    SDL_Quit();

    exit(status);
}