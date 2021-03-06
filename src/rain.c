#include <rain.h>

int main(int argc, char *argv[])
{

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    int statut = EXIT_FAILURE;
    SDL_Color orange = {255, 127, 40, 255};
    SDL_Color black = {0, 0, 0, 255};
    SDL_Color white = {255, 255, 255, 255};
    bool init_error = false;
    SDL_bool run = SDL_TRUE;
    srand(time(NULL));

    if (0 != SDL_Init(SDL_INIT_VIDEO))
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        return -1;
    }

    window = SDL_CreateWindow("Rain", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 700, SDL_WINDOW_FULLSCREEN_DESKTOP);

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
    if (0 != SDL_SetRenderDrawColor(renderer, black.r, black.g, black.b, black.a))
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

        Man* man = NULL;
        man = malloc(sizeof(*man));
        (*man).manX = 200;
        (*man).manLegs = 0;
        (*man).manLegsDirection = 1;
        while (run) {
            SDL_Event event;
            SDL_PollEvent(&event);

            rain(renderer, man);

            SDL_Delay(75);
            switch (event.type) {
                case SDL_KEYDOWN:
                    run = SDL_FALSE;
                    break;
            }
        }
        SDL_DestroyWindow(window);
    }

    SDL_Quit();
    return 0;
}

void rain(SDL_Renderer *renderer, Man* man) {
    SDL_Color black = {0, 0, 0, 255};
    SDL_Color white = {255, 255, 255, 255};

    // clear window
    SDL_SetRenderDrawColor(renderer, black.r, black.g, black.b, black.a);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, white.r, white.g, white.b, white.a);

    // draw ground
    SDL_RenderDrawLine(renderer, 0, GROUND_Y, SCREEN_WIDTH, GROUND_Y);
    // draw man
    drawMan(renderer, man);
    // draw rain
    drawRain(renderer, (*man).manX);
    

    SDL_RenderPresent(renderer);
}

void drawMan(SDL_Renderer *renderer, Man* man) {
        // move man
            (*man).manX = ((*man).manX + 2) % SCREEN_WIDTH;
            if ((*man).manLegs >= 20) {
                (*man).manLegsDirection = -1;
            } else if ((*man).manLegs <= 0) {
                (*man).manLegsDirection = 1;
            } 
            // change plus to minus for matrix effect ;)
            (*man).manLegs = ((*man).manLegs + ((*man).manLegsDirection * 2));
            int manX = (*man).manX;
            int manLegs = (*man).manLegs;
        // draw man
            //head
            SDL_RenderFillCircle(renderer, manX, GROUND_Y - 90, 10);
            SDL_RenderDrawLine(renderer, manX, GROUND_Y - 80, manX, GROUND_Y - 30);
            //hand
            SDL_RenderDrawLine(renderer, manX, GROUND_Y - 70, manX + 10, GROUND_Y - 60);
            SDL_RenderDrawLine(renderer, manX, GROUND_Y - 65, manX + 10, GROUND_Y - 55);
            SDL_RenderDrawLine(renderer, manX + 10, GROUND_Y - 60, manX + 20, GROUND_Y - 70);
            SDL_RenderDrawLine(renderer, manX + 10, GROUND_Y - 55, manX + 20, GROUND_Y - 70);
            //legs
            SDL_RenderDrawLine(renderer, manX, GROUND_Y - 30, manX + manLegs, GROUND_Y);
            SDL_RenderDrawLine(renderer, manX, GROUND_Y - 30, manX - manLegs, GROUND_Y);
            //umbrella
            SDL_RenderFillHalfCircle(renderer, manX + 20, GROUND_Y - 120, 40);
            SDL_RenderDrawLine(renderer, manX + 20, GROUND_Y - 120, manX + 20, GROUND_Y - 70);
}

void drawRain(SDL_Renderer *renderer, int manX) {
    int rx = 0;
    int ry = 0;
    int dropLength = 4;
    for (int i = 0; i < 400; i++) {
        rx = rand() % SCREEN_WIDTH;
        ry = rand() % SCREEN_HEIGHT;
        if (ry < GROUND_Y - dropLength) {
            if (ry < GROUND_Y - 120 - dropLength || (ry > GROUND_Y - 120 - dropLength && (rx < manX - 20 || rx > manX + 60))) {
                SDL_RenderDrawLine(renderer, rx, ry, rx + 1, ry + dropLength);
            }
        }
    }
}