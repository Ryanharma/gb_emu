#include "vram.h"

/* We will use this renderer to draw into this window every frame. */

int start_canvas(SDL_Window *window, SDL_Renderer *renderer) {
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        SDL_Log("Couldn't Initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    if (!SDL_CreateWindowAndRenderer("gbemu", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_Log("Couldn't create gbemu renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    // SDL_RenderClear(renderer);  /* start with a blank canvas. */
    return SDL_APP_SUCCESS;
}

void render_frame(SDL_Renderer *renderer, SDL_FPoint *pixels) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    for (int i = 0; i < SDL_arraysize(pixels); i++) {
        SDL_RenderPoint(renderer, pixels[i].x, pixels[i].y);
    }
}