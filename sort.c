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
SDL_Surface* screenSurface = NULL;

bool complete = false;

int main (int argc, char* argv[]) {

    while(1) {
        printf("\n");
        if(controls()) {
            execute();
        }
        else {
            printf("EXITING PROGRAM\n");
            break;
        }
    }

    return 0;
}

// initialize SDL
int init() {
    int success = 1;

    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = 0;
    }
    else {
        window = SDL_CreateWindow( "Sorting Visualizer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );\
        if ( window == NULL ) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = 0;
        }
        else {
            renderer = SDL_CreateRenderer(window, -1, 0);
            if ( renderer == NULL ) {
                printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
                success = false;
            }
        }
    }
    return success;
}

// closing function to kill window and renderer
void close() {
    SDL_DestroyRenderer(renderer);
    renderer = NULL;

    SDL_DestroyWindow(window);
    window = NULL;

    SDL_Quit();
}

void visualize(int x, int y, int z) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    int j = 0;

    for (int i = 0; i <= SCREEN_WIDTH - rectSize; i += rectSize){
        SDL_PumpEvents();

        SDL_Rect rect = { i, 0, rectSize, arr1[j] };
        if (complete) {
            SDL_SetRenderDrawColor(renderer, 100, 180, 100, 0);
            SDL_RenderDrawRect(renderer, &rect);
        }
        else if (j == x || j == z) {
            SDL_SetRenderDrawColor(renderer, 100, 180, 100, 0);
            SDL_RenderFillRect(renderer, &rect);
        }
        else if (j == y) {
            SDL_SetRenderDrawColor(renderer, 165, 105, 189, 0);
            SDL_RenderFillRect(renderer, &rect);
        }
        else {
            SDL_SetRenderDrawColor(renderer, 170, 183, 184, 0);
            SDL_RenderDrawRect(renderer, &rect);
        }
        j++;
    }
    SDL_RenderPresent(renderer);
}

void insertSort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void execute() {
    if(!init()) {
        printf("SDL Initialization Failed\n");
    }
    else {
        randomizeArray();
        loadArray();

        SDL_Event e;
        int quit = false;
        while (!quit) {
            while (SDL_PollEvent(&e) != 0)
            {
                if (e.type == SDL_QUIT)
                {
                    quit = 1;
                    complete = false;
                }
                else if(e.type == SDL_KEYDOWN) {
                    switch(e.key.keysym.sym) {
                        case(SDLK_q):
                            quit = 1;
                            complete = false;
                            printf("EXITING SORTING VISUALIZER\n");
                            break;
                        case(SDLK_0):
                            randomizeArray();
                            complete = false;
                            loadArray();
                            printf("NEW RANDOM LIST GENERATED\n");
                            break;
                    }
                }
            }
            visualize(-1, -1, -1);
        }
        close();
    }
}

void loadArray() {
    memcpy(arr1, arr2, sizeof(int)*ARRAY_LENGTH);
}

void randomizeArray() {
    unsigned int seed = (unsigned)time(NULL);
    srand(seed);
    for (int i = 0; i < ARRAY_LENGTH; i++) {
        int randNum = rand()%(SCREEN_HEIGHT);
        arr2[i] = randNum;
    }
}

int controls() {
    printf(
        "WARNING: Giving repetitive commands may cause latency and the visualizer may behave unexpectedly. Please give a new command only after the current command's execution is done.\n\n"
        "Available Controls inside Sorting Visualizer:-\n"
        "    Use 0 to Generate a different randomized list.\n"
        "    Use 1 to start Selection Sort Algorithm.\n"
        "    Use 2 to start Insertion Sort Algorithm.\n"
        "    Use 3 to start Bubble Sort Algorithm.\n"
        "    Use 4 to start Merge Sort Algorithm.\n"
        "    Use 5 to start Quick Sort Algorithm.\n"
        "    Use 6 to start Heap Sort Algorithm.\n"
        "    Use q to exit out of Sorting Visualizer\n\n"
        "PRESS ENTER TO START SORTING VISUALIZER...\n\n"
        "Or type -1 and press ENTER to quit the program."
    );

    int input;
    scanf("%d", &input);

    if(input == -1) {
        return 0;
    }

    return 1;
}
