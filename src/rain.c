#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define GROUND_Y SCREEN_HEIGHT * 0.75

void pause();
void drawRainDrops(int numberOfDrop, int sizeOfDrop, SDL_Renderer *renderer);
void rain(SDL_Renderer *renderer);
void SDL_Ellipse(SDL_Renderer* r, int x0, int y0, int radiusX, int radiusY);
void SDL_RenderFillCircle(SDL_Renderer * renderer, int x, int y, int radius);
void SDL_RenderFillHalfCircle(SDL_Renderer * renderer, int x, int y, int radius);

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
        while (run) {
            SDL_Event event;
            SDL_WaitEvent(&event);
            rain(renderer);
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

void rain(SDL_Renderer *renderer)
{
    SDL_Color black = {0, 0, 0, 255};
    SDL_Color white = {255, 255, 255, 255};
    SDL_SetRenderDrawColor(renderer, black.r, black.g, black.b, black.a);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, white.r, white.g, white.b, white.a);

    // draw ground
    SDL_RenderDrawLine(renderer, 0, GROUND_Y, SCREEN_WIDTH, GROUND_Y);
    
    // draw man
        int manX = 200;
        //head
        SDL_RenderFillCircle(renderer, manX, GROUND_Y - 90, 10);
        SDL_RenderDrawLine(renderer, manX, GROUND_Y - 80, manX, GROUND_Y - 30);
        //hand
        SDL_RenderDrawLine(renderer, manX, GROUND_Y - 70, manX + 10, GROUND_Y - 60);
        SDL_RenderDrawLine(renderer, manX, GROUND_Y - 65, manX + 10, GROUND_Y - 55);
        SDL_RenderDrawLine(renderer, manX + 10, GROUND_Y - 60, manX + 20, GROUND_Y - 70);
        SDL_RenderDrawLine(renderer, manX + 10, GROUND_Y - 55, manX + 20, GROUND_Y - 70);
        //legs
        SDL_RenderDrawLine(renderer, manX, GROUND_Y - 30, manX + 10, GROUND_Y);
        SDL_RenderDrawLine(renderer, manX, GROUND_Y - 30, manX - 10, GROUND_Y);
        //umbrella
        // SDL_RenderDrawPieslice(manX + 20, GROUND_Y - 120, 0, 180, 40);
        SDL_RenderFillHalfCircle(renderer, manX + 20, GROUND_Y - 120, 40);
        SDL_RenderDrawLine(renderer, manX + 20, GROUND_Y - 120, manX + 20, GROUND_Y - 70);


    SDL_RenderPresent(renderer);
}

void drawRainDrops(int numberOfDrop, int sizeOfDrop, SDL_Renderer *renderer)
{
    int randomOffset;
    int count = 0;
    int yOffset = 2;
    SDL_Rect *rects[numberOfDrop];
    SDL_Rect *rectsTrail[numberOfDrop];
    for (int i = 0; i < numberOfDrop; i++)
    {
        randomOffset = (rand() % (1980 - 0 + 1)) / 10 * 10 + 0;
        SDL_Rect *r;
        r = malloc(sizeof(*r));
        (*r).x = randomOffset;
        (*r).y = 30;
        (*r).w = 4;
        (*r).h = 20;
        SDL_Rect *rt;
        rt = malloc(sizeof(*r));
        (*rt).x = randomOffset;
        (*rt).h = 3;
        (*rt).y = 30 - (*rt).h;
        (*rt).w = 4;
        // SDL_Rect rect = {randomOffset, 30, 4, 20};
        rects[i] = r;
        rectsTrail[i] = rt;
    }
    while (count++ < 600)
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
        SDL_Delay(1000 / 60);
        SDL_RenderPresent(renderer);
        SDL_Color orange = {255, 127, 40, 255};
        SDL_SetRenderDrawColor(renderer, orange.r, orange.g, orange.b, orange.a);
        SDL_RenderClear(renderer);
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

// source: https://stackoverflow.com/questions/38334081/howto-draw-circles-arcs-and-vector-graphics-in-sdl
void SDL_Ellipse(SDL_Renderer* r, int x0, int y0, int radiusX, int radiusY) {
    float pi  = 3.14159265358979323846264338327950288419716939937510;
    float pih = pi / 2.0; //half of pi

    //drew  28 lines with   4x4  circle with precision of 150 0ms
    //drew 132 lines with  25x14 circle with precision of 150 0ms
    //drew 152 lines with 100x50 circle with precision of 150 3ms
    const int prec = 27; // precision value; value of 1 will draw a diamond, 27 makes pretty smooth circles.
    float theta = 0;     // angle that will be increased each loop

    //starting point
    int x  = (float)radiusX * cos(theta);//start point
    int y  = (float)radiusY * sin(theta);//start point
    int x1 = x;
    int y1 = y;

    //repeat until theta >= 90;
    float step = pih/(float)prec; // amount to add to theta each time (degrees)
    for(theta=step;  theta <= pih;  theta+=step)//step through only a 90 arc (1 quadrant)
    {
        //get new point location
        x1 = (float)radiusX * cosf(theta) + 0.5; //new point (+.5 is a quick rounding method)
        y1 = (float)radiusY * sinf(theta) + 0.5; //new point (+.5 is a quick rounding method)

        //draw line from previous point to new point, ONLY if point incremented
        if( (x != x1) || (y != y1) )//only draw if coordinate changed
        {
            SDL_RenderDrawLine(r, x0 + x, y0 - y,    x0 + x1, y0 - y1 );//quadrant TR
            SDL_RenderDrawLine(r, x0 - x, y0 - y,    x0 - x1, y0 - y1 );//quadrant TL
            SDL_RenderDrawLine(r, x0 - x, y0 + y,    x0 - x1, y0 + y1 );//quadrant BL
            SDL_RenderDrawLine(r, x0 + x, y0 + y,    x0 + x1, y0 + y1 );//quadrant BR
        }
        //save previous points
        x = x1;//save new previous point
        y = y1;//save new previous point
    }
    //arc did not finish because of rounding, so finish the arc
    if(x!=0)
    {
        x=0;
        SDL_RenderDrawLine(r, x0 + x, y0 - y,    x0 + x1, y0 - y1 );//quadrant TR
        SDL_RenderDrawLine(r, x0 - x, y0 - y,    x0 - x1, y0 - y1 );//quadrant TL
        SDL_RenderDrawLine(r, x0 - x, y0 + y,    x0 - x1, y0 + y1 );//quadrant BL
        SDL_RenderDrawLine(r, x0 + x, y0 + y,    x0 + x1, y0 + y1 );//quadrant BR
    }
}

// source: https://gist.github.com/Gumichan01/332c26f6197a432db91cc4327fcabb1c
void SDL_RenderFillCircle(SDL_Renderer * renderer, int x, int y, int radius) {
    int offsetx, offsety, d;
    int status;

    offsetx = 0;
    offsety = radius;
    d = radius -1;
    status = 0;

    while (offsety >= offsetx) {

        status += SDL_RenderDrawLine(renderer, x - offsety, y + offsetx,
                                     x + offsety, y + offsetx);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y + offsety,
                                     x + offsetx, y + offsety);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y - offsety,
                                     x + offsetx, y - offsety);
        status += SDL_RenderDrawLine(renderer, x - offsety, y - offsetx,
                                     x + offsety, y - offsetx);

        if (status < 0) {
            status = -1;
            break;
        }

        if (d >= 2*offsetx) {
            d -= 2*offsetx + 1;
            offsetx +=1;
        }
        else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }

}

void SDL_RenderFillHalfCircle(SDL_Renderer * renderer, int x, int y, int radius) {
    int offsetx, offsety, d;
    int status;

    offsetx = 0;
    offsety = radius;
    d = radius -1;
    status = 0;

    while (offsety >= offsetx) {

        status += SDL_RenderDrawLine(renderer, x - offsetx, y - offsety,
                                     x + offsetx, y - offsety);
        status += SDL_RenderDrawLine(renderer, x - offsety, y - offsetx,
                                     x + offsety, y - offsetx);


        if (status < 0) {
            status = -1;
            break;
        }

        if (d >= 2*offsetx) {
            d -= 2*offsetx + 1;
            offsetx +=1;
        }
        else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }

    }
}