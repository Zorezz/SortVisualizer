#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define SCREEN_WIDTH 910
#define SCREEN_HEIGHT 750
#define ARRAY_LENGTH 130

const int rectSize = 7;

int arr1[ARRAY_LENGTH];
int arr2[ARRAY_LENGTH];

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

bool finished = false;

int main (int argc, char* argv[]) {
    int succ = init();
    if (succ == 0) {
        printf("BIG FAILURE");
        return 0;
    }
    return 0;
}

// initialize SDL
int init() {
    int success = 1;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Initialize SDL failed, Error: %s", SDL_GetError());
        success = 0;
    }
    else {
        if (!(SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))) {
            printf("Linear Texture Filtering not enabled.\n");
        }

        window=SDL_CreateWindow("Sorting Visualizer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            printf("Unable to create window. Error: %s", SDL_GetError());
            success = 0;
        }
        else {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (renderer == NULL) {
                printf("Unable to create renderer. Error: %s", SDL_GetError());
                success = 0;
            }
        }
    }

    return success;
}


