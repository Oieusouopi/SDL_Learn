#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
//
// Created by eec on 15/06/25.
//

#define WIDTH 800
#define HEIGHT 600

// Janela Global
SDL_Window* gWindow;

// Renderizador Global
SDL_Renderer* gRenderer;

// Textura Global
SDL_Texture* gTexture;

// Iniciar o SDL
bool init();

// Carregar media
bool loadMedia();

// Fechar o SDL
void closeSDL(int status);

int main() {
    if (init()) {
        printf("Aconteceu algum erro");
        closeSDL(EXIT_FAILURE);
    }

    while (true) {
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                closeSDL(EXIT_SUCCESS);
            }
        }

        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        // Renderizar quadrado de vermelho
        SDL_Rect fillRect = { WIDTH / 4, HEIGHT / 4, WIDTH / 2, HEIGHT / 2};
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xff);
        SDL_RenderFillRect(gRenderer, &fillRect);

        // Renderizar o quadrado de verde
        SDL_Rect outlineRect = { WIDTH / 6, HEIGHT / 6, WIDTH * 2 / 3, HEIGHT * 2 / 3};
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00,0xFF);
        SDL_RenderDrawRect(gRenderer, &outlineRect);

        // Desenhar linha no meio
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);
        SDL_RenderDrawLine(gRenderer, 0, HEIGHT / 2, WIDTH, HEIGHT/ 2);

        //Desenhar uma linha vertical de pontos amarelos
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0x00, 0xFF);
        for (int i = 0; i < WIDTH; i += 4) {
            SDL_RenderDrawPoint(gRenderer, WIDTH / 2, i);
        }

        // Atualizar a tela
        SDL_RenderPresent(gRenderer);
    }

}

bool init() {

    if (SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Erro ao iniciar o SDL: %s\n", SDL_GetError());
        return true;
    }

    gWindow = SDL_CreateWindow("06_Geometry_rendering", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

    if (!gWindow) {
        fprintf(stderr, "Erro ao iniciar a janela: %s\n", SDL_GetError());
        return true;
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

    if (!gRenderer) {
        fprintf(stderr, "Erro ao iniciar o renderizador: %s\n", SDL_GetError());
        return true;
    }

    return false;
}

void closeSDL(int status) {
    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    SDL_Quit();

    exit(status);
}

bool loadMedia() {
    return true;
}