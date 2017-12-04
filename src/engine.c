/*
 * Copyright 2017 Bogdan Barbu
 *
 * This file is part of 2 Axis Mundi.
 *
 * 2 Axis Mundi is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * 2 Axis Mundi is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with 2 Axis Mundi.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <am2d/engine.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdlib.h>

#define MS_PER_FRAME 30

am2d_context *am2d_new(const char *title, int width, int height) {
    am2d_context *context = NULL;
    Uint32 init = SDL_INIT_VIDEO;

    if (SDL_WasInit(init) != init) {
        if (SDL_Init(init) != 0)
            goto done; 
        atexit(SDL_Quit);
    }

    if ((context = malloc(sizeof *context)) == NULL)
        goto done;

    context->running = false;

    if ((context->window = SDL_CreateWindow(context->title = title,
                                            SDL_WINDOWPOS_CENTERED,
                                            SDL_WINDOWPOS_CENTERED,
                                            context->width = width,
                                            context->height = height,
                                            SDL_WINDOW_SHOWN)) == NULL ||
        (context->renderer = SDL_CreateRenderer(context->window, -1, SDL_RENDERER_ACCELERATED)) == NULL) {
        am2d_delete(context);
        context = NULL;
    }

done:
    return context;
}

void am2d_delete(am2d_context *context) {
    SDL_DestroyRenderer(context->renderer);
    SDL_DestroyWindow(context->window);
    free(context);
}

void am2d_run(am2d_context *context) {
    unsigned int time;

    for (context->running = true; context->running; ) {
        time = SDL_GetTicks();
        am2d_handleinput(context);
        am2d_update(context);
        am2d_render(context);
        SDL_Delay(time + MS_PER_FRAME - SDL_GetTicks());
    }
}
