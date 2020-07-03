#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <SDL2/SDL.h>

void pause();
void drawRainDrops(int numberOfDrop, int sizeOfDrop, SDL_Renderer *renderer);

int main(int argc, char *argv[])
{

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    int statut = EXIT_FAILURE;
    SDL_Color orange = {255, 127, 40, 255};
    bool init_error = false;
    srand(time(NULL));

    if (0 != SDL_Init(SDL_INIT_VIDEO))
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        return -1;
    }

    window = SDL_CreateWindow("Rain", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 700, SDL_WINDOW_SHOWN);

    if (NULL == window)
    {
        fprintf(stderr, "Erreur de creation de la fenetre : %s\n", SDL_GetError());
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (NULL == renderer)
    {
        fprintf(stderr, "Erreur SDL_CreateRenderer : %s", SDL_GetError());
        init_error = true;
    }
    if (0 != SDL_SetRenderDrawColor(renderer, orange.r, orange.g, orange.b, orange.a))
    {
        fprintf(stderr, "Erreur SDL_SetRenderDrawColor : %s", SDL_GetError());
        init_error = true;
    }

    if (0 != SDL_RenderClear(renderer))
    {
        fprintf(stderr, "Erreur SDL_SetRenderDrawColor : %s", SDL_GetError());
        init_error = true;
    }
    if (!init_error)
    {
        SDL_Delay(500);

        //rectangle
        // SDL_Rect rect = {100, 100, 100, 100};
        // SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        // SDL_RenderFillRect(renderer, &rect);

        drawRainDrops(50, 2, renderer);

        //affichage
        // SDL_RenderPresent(renderer);

        pause();

        SDL_DestroyWindow(window);
    }

    SDL_Quit();
    return 0;
}

void drawRainDrops(int numberOfDrop, int sizeOfDrop, SDL_Renderer *renderer)
{
    int randomOffset;
    int count = 0;
    int yOffset = 1;
    SDL_Rect* rects[numberOfDrop];
    SDL_Rect* rectsTrail[numberOfDrop];
    for (int i = 0; i < numberOfDrop; i++) {
        randomOffset = (rand() % (500 - 0 + 1)) / 10 * 10 + 0;
        SDL_Rect* r;
        r = malloc(sizeof(*r));
        (*r).x = randomOffset;
        (*r).y = 30;
        (*r).w = 4;
        (*r).h = 20;
        SDL_Rect* rt;
        rt = malloc(sizeof(*r));
        (*rt).x = randomOffset;
        (*rt).h = 3;
        (*rt).y = 30 - (*rt).h;
        (*rt).w = 4;
        // SDL_Rect rect = {randomOffset, 30, 4, 20};
        rects[i] = r;
        rectsTrail[i] = rt;
    }
    while (count++ < 500)
    {
        for (int i = 0; i < numberOfDrop; i++)
        {
            (*rectsTrail[i]).y += yOffset;
            SDL_SetRenderDrawColor(renderer, 20, 20, 20, 0);
            SDL_RenderFillRect(renderer, rectsTrail[i]);
            (*rects[i]).y += yOffset;
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderFillRect(renderer, rects[i]);
            // printf("%d\n", (*rects[i]).x);
        }
        SDL_RenderPresent(renderer);
        SDL_Color orange = {255, 127, 40, 255};
        SDL_SetRenderDrawColor(renderer, orange.r, orange.g, orange.b, orange.a);
        SDL_RenderClear(renderer);
        SDL_Delay(1000/60);
    }
}

void pause()
{
    int continuer = 1;
    SDL_Event event;

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            continuer = 0;
        }
    }
}