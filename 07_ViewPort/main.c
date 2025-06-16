#include <SDL_image.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
//
// Created by eec on 15/06/25.
//

#define WIDTH 800
#define HEIGHT 600
#define IMG_FLAG IMG_INIT_PNG

// Janela Global
SDL_Window* gWindow = NULL;

// Renderizador Global
SDL_Renderer* gRenderer = NULL;

// Textura 1
SDL_Texture* texture_1 = NULL;

// Textura 2
SDL_Texture* texture_2 = NULL;

// Textura 3
SDL_Texture* texture_3 = NULL;

// Carregar midia
bool loadMedia();

// Inicializador SDL
bool init();

SDL_Texture* generateTexture(char path[]);

// Fechar SDL
void closeSDL(int status);

int main() {
    if (init()) {
        printf("Deu algo errado");
        closeSDL(EXIT_FAILURE);
    }

    if (loadMedia()) {
        printf("Deu algum erro ao carregar as midias");
        closeSDL(EXIT_FAILURE);
    }

    while (true) {
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                closeSDL(EXIT_SUCCESS);
            }
        }

        SDL_Rect topLeftViewPort;
        topLeftViewPort.x = 0;
        topLeftViewPort.y = 0;
        topLeftViewPort.w = WIDTH / 2;
        topLeftViewPort.h = HEIGHT / 2;
        SDL_RenderSetViewport(gRenderer, &topLeftViewPort);

        // Render texture to screen
        SDL_RenderCopy(gRenderer, texture_1, NULL, NULL);

        SDL_Rect topRightViewPort;
        topRightViewPort.x = WIDTH / 2;
        topRightViewPort.y = 0;
        topRightViewPort.w = WIDTH / 2;
        topRightViewPort.h = HEIGHT / 2;

        SDL_RenderSetViewport(gRenderer, &topRightViewPort);

        // Render texture to screen
        SDL_RenderCopy(gRenderer, texture_2,  NULL, NULL);

        SDL_Rect bottomViewPort;
        bottomViewPort.x = 0;
        bottomViewPort.y = HEIGHT / 2;
        bottomViewPort.w = WIDTH;
        bottomViewPort.h = HEIGHT / 2;

        SDL_RenderSetViewport(gRenderer, &bottomViewPort);

        // Render Texture to screen
        SDL_RenderCopy(gRenderer, texture_3, NULL, NULL);

        SDL_RenderPresent(gRenderer);
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

    if (!(IMG_Init(IMG_FLAG)) & IMG_FLAG) {
        fprintf(stderr, "Erro na inicializacao do pacote IMG: %s\n", IMG_GetError());\
        return true;
    }

    return false;
}

void closeSDL(int status) {
    SDL_DestroyTexture(texture_1);
    texture_1 = NULL;

    SDL_DestroyTexture(texture_2);
    texture_2 = NULL;

    SDL_DestroyTexture(texture_3);
    texture_3 = NULL;

    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    IMG_Quit();
    SDL_Quit();

    exit(status);
}

bool loadMedia() {

    texture_1 = generateTexture("../Images/png/image_1.png");

    if (texture_1 == NULL) {
        fprintf(stderr,"Deu erro ao gerar a textura: %s\n", IMG_GetError());
        return true;
    }

    texture_2 = generateTexture("../Images/png/image_2.png");

    if (texture_2 == NULL) {
        fprintf(stderr, "Deu erro ao gerar a textura %s\n", IMG_GetError());
        return true;
    }

    texture_3 = generateTexture("../Images/png/image_3.png");

    if (texture_3 == NULL) {
        fprintf(stderr, "Deu erro ao gerar a textura %s\n", IMG_GetError());
        return true;
    }

    return false;
}

SDL_Texture* generateTexture(char path[]) {
    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load(path);
    if (loadedSurface == NULL) {
        fprintf(stderr, "Erro ao carregar a imagem: %s\n", IMG_GetError());
    }

    newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    if (newTexture == NULL) {
        fprintf(stderr, "Nao foi possivel criar a textura: %s\n", IMG_GetError());
    }

    SDL_FreeSurface(loadedSurface);

    return newTexture;
}