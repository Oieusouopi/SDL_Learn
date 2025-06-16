#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
//
// Created by eec on 14/06/25.
//
#define WIDTH 600
#define  HEIGHT 800
#define IMG_FLAG IMG_INIT_PNG

//Starts up SDL and creates window
bool init();

//Frees media and shuts down SDL
void closeSDL(int status);

//Loads media
bool load_media();

// Load image with texture
SDL_Texture* loadTexture(char path[]);

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

// The renderer
SDL_Renderer* gRenderer = NULL;

//The surface contained by the window
SDL_Surface* gSurface = NULL;

// The load Texture
SDL_Texture* gTexture = NULL;

int main() {
    if (init()) {
        fprintf(stderr, "Deu algum erro");
        closeSDL(EXIT_FAILURE);
    }

    if (load_media()) {
        fprintf(stderr, "Deu algum erro");
        closeSDL(EXIT_FAILURE);
    }

    while (true) {

        SDL_Event event;
        while (SDL_PollEvent( &event )) {
            if (event.type == SDL_QUIT) {
                closeSDL(EXIT_SUCCESS);
            }
        }

        // Limpar a tela
        SDL_RenderClear(gRenderer);

        //Renderizar textura na tela
        SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

        // atualizar a tela
        SDL_RenderPresent(gRenderer);
    }
}

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr,"Erro no SDL: %s\n", SDL_GetError());
        return true;
    }

    gWindow = SDL_CreateWindow("05_extension_libraries_and_loading_other_image_formats", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

    if (!gWindow) {
        fprintf(stderr,"Erro na criação da janela: %s\n", SDL_GetError());
        return true;
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

    if (!gRenderer) {
        fprintf(stderr, "Erro ao criar o renderizador: %s\n", SDL_GetError());
        return true;
    }

    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

    if (!(IMG_Init(IMG_FLAG) & IMG_FLAG)) {
        fprintf(stderr, "Erro na inicializacao do pacote IMG: %s\n", IMG_GetError());\
        return true;
    }

    gSurface = SDL_GetWindowSurface(gWindow);

    return false;
}

bool load_media() {

    gTexture = loadTexture("../Images/png/image_1.png");

    if (!gTexture) {
        fprintf(stderr, "Erro ao carregar a textura! %s\n", IMG_GetError());
        return true;
    }

    return false;
}

SDL_Texture* loadTexture(char path[]) {
    // Textura final
    SDL_Texture* newTexture = NULL;

    // Carregar imagem no caminho especificado
    SDL_Surface* loadedSurface = IMG_Load(path);
    if (loadedSurface == NULL) {
        fprintf(stderr, "Não foi possivel carregar a imagem %s ! Erro SDL_IMAGE: %s\n", path, SDL_GetError());
    }

    // Criar textura a partir de pixels de superficie
    newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    if (newTexture == NULL) {
        fprintf(stderr, "Não foi possivel carregar a textura da imagem %s\n", IMG_GetError());
    }

    // Free Surface antiga
    SDL_FreeSurface(loadedSurface);

    return newTexture;
}

void closeSDL(int status) {
    // Imagem Carregada
    SDL_DestroyTexture(gTexture);
    gTexture = NULL;

    // Destruir janela
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gRenderer = NULL;
    gWindow = NULL;

    // Fechar subsistemas SDL
    IMG_Quit();
    SDL_Quit();

    exit(status);
}

