#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <sdl_circle.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define GROUND_Y SCREEN_HEIGHT * 0.75

typedef struct Man Man;
struct Man {
    int manX;
    int manLegs;
    int manLegsDirection;
};

void rain(SDL_Renderer *renderer, Man* man);
void drawMan(SDL_Renderer *renderer, Man* man);
void drawRain(SDL_Renderer *renderer, int manX);

