#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
//
// Created by eec on 14/06/25.
//
#define WIDTH 600
#define  HEIGHT 800

enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

//Starts up SDL and creates window
bool init();

//Frees media and shuts down SDL
void closeSDL(int status);

//Loads media
bool load_media();

//Loads individual image
SDL_Surface* loadSurface(char path[]);

//The window we'll be rendering to
SDL_Window *gWindow = NULL;


//The surface contained by the window
SDL_Surface *gSurface = NULL;

//The images that correspond to a keypress
SDL_Surface* gKeyPressSurfaces[ KEY_PRESS_SURFACE_TOTAL ];

//Current displayed image
SDL_Surface* gCurrentSurface = NULL;

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
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
                        break;
                    case SDLK_DOWN:
                        gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
                        break;
                    case SDLK_LEFT:
                        gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
                        break;
                    case SDLK_RIGHT:
                        gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
                        break;
                    case SDLK_ESCAPE:
                        closeSDL(EXIT_SUCCESS);
                    default:
                        gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
                        break;
                }
            }
        }

        //Apply the image stretched
        SDL_Rect stretchRect;
        stretchRect.x = 0;
        stretchRect.y = 0;
        stretchRect.w = WIDTH;
        stretchRect.h = HEIGHT;
        SDL_BlitScaled( gCurrentSurface, NULL, gSurface, &stretchRect );
        SDL_UpdateWindowSurface( gWindow );

    }
}

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr,"Erro no SDL: %s\n", SDL_GetError());
        return true;
    }

    gWindow = SDL_CreateWindow("04-optimized_surface_loading_and_soft_streching", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

    if (!gWindow) {
        fprintf(stderr,"Erro na criação da janela: %s\n", SDL_GetError());
        return true;
    }



    gSurface = SDL_GetWindowSurface(gWindow);

    return false;
}

bool load_media() {

    gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("../Images/bmp/image_1.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL) {
        fprintf(stderr, "Deu erro ao carregar a imagem!\n");
        return true;
    }

    gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("../Images/bmp/image_2.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL) {
        fprintf(stderr, "Deu erro ao carregar a imagem!\n");
        return true;
    }

    gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("../Images/bmp/image_3.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL) {
        fprintf(stderr, "Deu erro ao carregar a imagem!\n");
        return true;
    }

    gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("../Images/bmp/image_4.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL) {
        fprintf(stderr, "Deu erro ao carregar a imagem\n");
        return true;
    }

    gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("../Images/bmp/image_5.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL) {
        fprintf(stderr, "Deu erro ao carregar a imagem\n");
        return true;
    }

    return false;
}

SDL_Surface* loadSurface(char path[]) {
    //The final optimized image
    SDL_Surface* optimizedSurface = NULL;

    // load image at specified path
    SDL_Surface* loadSurface = SDL_LoadBMP(path);

    if (loadSurface == NULL) {
        printf( "Unable to load image %s! SDL Error: %s\n", path, SDL_GetError() );
    }
    else {

        //Convert surface to screen format
        optimizedSurface = SDL_ConvertSurface( loadSurface, gSurface->format, 0 );
        if( optimizedSurface == NULL )
        {
            printf( "Unable to optimize image %s! SDL Error: %s\n", path, SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadSurface );
    }

    return optimizedSurface;
}

void closeSDL(int status) {
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    SDL_Quit();

    exit(status);
}

