#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

//
// Created by eec on 14/06/25.
//

#define WIDTH 600
#define HEIGHT 800

// The window we'll be rendering to
SDL_Window *gWindow = NULL;

// The surface contained by the window
SDL_Surface *gScreenSurface = NULL;

// The image we will load and show on the screen
SDL_Surface *gHelloWorld = NULL;


// Start ups SDL and create window
bool init();

// Loads Media
bool loadMedia();

// Frees media and shut down SDL
void closeSDL(int status);

int main() {
    // Start up SDL and create Window
    if (init()) {
        printf("Teve alguma falha");
        closeSDL(EXIT_FAILURE);
    } else {
        if (!loadMedia()) {
            printf("Teve algum erro ao carregar a imagem");
            closeSDL(EXIT_FAILURE);
        } else {
            // Apply the image
            SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);

            // update the surface
            SDL_UpdateWindowSurface(gWindow);

            // Hack to get window to stay up
            SDL_Event e;
            bool quit = false;
            while( quit == false ) {
                while( SDL_PollEvent( &e ) ) {
                    if( e.type == SDL_QUIT )
                        quit = true;
                }
            }
        }
    }

    closeSDL(EXIT_SUCCESS);
    return 0;
}

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Erro ao inicar o SDL:  %s\n", SDL_GetError());
        return true;
    }

    gWindow = SDL_CreateWindow("SDL tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

    if (!gWindow) {
        fprintf(stderr, "Erro ao inciar a janela: %s\n", SDL_GetError());
        return true;
    }

    gScreenSurface = SDL_GetWindowSurface(gWindow);

    return false;
}

bool loadMedia() {
    bool success = true;

    // Load splash image
    gHelloWorld = SDL_LoadBMP("../Images/image_1.bmp");
    if (gHelloWorld == NULL) {
        printf("Nao foi possivel renderizar a imagem! SDL_ERROR %s\n", SDL_GetError());
        success = false;
    }

    return success;
}

void closeSDL(int status) {
    // Deallocate surface
    SDL_FreeSurface(gHelloWorld);
    gHelloWorld = NULL;

    // Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    // Quit SDL SubSystems
    SDL_Quit();

    exit(status);
}