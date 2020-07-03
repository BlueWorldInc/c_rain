#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

void pause();

int main(int argc, char* argv[])
{

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    int statut = EXIT_FAILURE;
    SDL_Color orange = {255, 127, 40, 255};
    bool init_error = false;
    
    if (0 != SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        return -1;
    }

    window = SDL_CreateWindow("Rain", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, SDL_WINDOW_SHOWN);
    
    if (NULL == window) {
        fprintf(stderr, "Erreur de creation de la fenetre : %s\n", SDL_GetError());

    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(NULL == renderer) {
        fprintf(stderr, "Erreur SDL_CreateRenderer : %s", SDL_GetError());
        init_error = true;
    }
    if(0 != SDL_SetRenderDrawColor(renderer, orange.r, orange.g, orange.b, orange.a))
    {
        fprintf(stderr, "Erreur SDL_SetRenderDrawColor : %s", SDL_GetError());
        init_error = true;
    }
    
    if(0 != SDL_RenderClear(renderer)) {
        fprintf(stderr, "Erreur SDL_SetRenderDrawColor : %s", SDL_GetError());
        init_error = true;
    }
    if (!init_error) {
        SDL_Delay(500);
        SDL_RenderPresent(renderer);
        // SDL_Surface *ecran = NULL;
        // ecran = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE);
        // SDL_FillRect(surface, NULL, couleur);
        pause();
        SDL_DestroyWindow(window);
    }

    SDL_Quit();
    return 0;
}

void pause() {
    int continuer = 1;
    SDL_Event event;
 
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
        }
    }
}