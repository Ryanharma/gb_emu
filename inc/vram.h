// #pragma once

// #include <SDL3/SDL.h>
// #include <SDL3/SDL_main.h> // To render images on screen

// // Screen parameters in pixels (2 bits per pixel)
// #define SCREEN_WIDTH 160
// #define SCREEN_HEIGHT 144
// #define NUM_PIXEL SCREEN_WIDTH * SCREEN_HEIGHT

// typedef struct Screen {
//     SDL_Window *window;
//     SDL_Renderer *renderer;
//     SDL_FPoint points[NUM_PIXEL];
// } screen_t;

// int start_canvas(SDL_Window *window, SDL_Renderer *renderer); // Function that initialize the image rendering (draw the GB "tiles")
// void render_frame(SDL_Renderer *renderer, SDL_FPoint *pixels);