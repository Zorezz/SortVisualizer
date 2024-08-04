#include <stdio.h>
#include <stdbool.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 910
#define SCREEN_HEIGHT 750
#define ARRAY_LENGTH 130
#define rectSize 7

int arr1[ARRAY_LENGTH];
int arr2[ARRAY_LENGTH];

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

bool complete = false;

int main(int argc, char *argv[]) {


    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Could not init SDL: %s\n", SDL_GetError());
        exit(1);
    }

    window = SDL_CreateWindow(
        "Sorting Visualizer",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        910,
        750,
        SDL_WINDOW_OPENGL
    );

    if (!window) {
        printf("Failed to create window: %s\n", SDL_GetError());
        exit(1);
    }

    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED
    );
    if (!renderer) {
        printf("Renderer could not be created: %s", SDL_GetError());
        exit(1);
    }

    randomizeArray();
    loadArray();
    //debugPrintArr(arr2);

    // main loop
    bool should_quit = false;
    while (!should_quit) {
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT:
                    should_quit = true;
                    break;
                default:
                    break;
            }
            insertSort(arr1, ARRAY_LENGTH);
        }
   }
}

void visualize() {
            // draw the array
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            SDL_RenderClear(renderer);

            int j = 0;

            for (int i = 0; i <= SCREEN_WIDTH - rectSize; i += rectSize) {
                SDL_PumpEvents();

                SDL_Rect rect = { i, 0, rectSize, arr1[j] };
                SDL_SetRenderDrawColor(renderer, 170, 183, 184, 0);
                SDL_RenderDrawRect(renderer, &rect);
                j++;
            }
            SDL_RenderPresent(renderer);
}

void loadArray() {
    memcpy(arr1, arr2, sizeof(int) * ARRAY_LENGTH);
}

void randomizeArray() {
    unsigned int seed = (unsigned)time(NULL);
    srand(seed);
    for (int i = 0; i < ARRAY_LENGTH; i++) {
        int randNum = rand() % (SCREEN_HEIGHT);
        arr2[i] = randNum;
    }
}

void debugPrintArr(int arr[]) {
    for (int i = 0; i < ARRAY_LENGTH; i++) {
        printf("%d ", arr[i]);
    }
}

void insertSort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;

            visualize();
            SDL_Delay(5);
        }
        arr[j + 1] = key;
    }
}


