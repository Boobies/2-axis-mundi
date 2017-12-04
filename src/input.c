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

#include <am2d/input.h>
#include <SDL2/SDL.h>

static void (*keyhandler[8])(void) = { NULL };

static inline void handle(enum am2d_key key) {
    if (keyhandler[key] != NULL)
        keyhandler[key]();
}

void am2d_handleinput(am2d_context *context) {
    SDL_Event event;

    if (SDL_PollEvent(&event) == SDL_TRUE)
        switch (event.type) {
        case SDL_QUIT:
            context->running = false;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
            case SDLK_UP:
                handle(AM2D_KEY_PRESS_UP);
                break;
            case SDLK_DOWN:
                handle(AM2D_KEY_PRESS_DOWN);
                break;
            case SDLK_LEFT:
                handle(AM2D_KEY_PRESS_LEFT);
                break;
            case SDLK_RIGHT:
                handle(AM2D_KEY_PRESS_RIGHT);
                break;
            }
            break;
        case SDL_KEYUP:
            switch (event.key.keysym.sym) {
            case SDLK_UP:
                handle(AM2D_KEY_RELEASE_UP);
                break;
            case SDLK_DOWN:
                handle(AM2D_KEY_RELEASE_DOWN);
                break;
            case SDLK_LEFT:
                handle(AM2D_KEY_RELEASE_LEFT);
                break;
            case SDLK_RIGHT:
                handle(AM2D_KEY_RELEASE_RIGHT);
                break;
            }
            break;
        }
}

void am2d_key_bind(enum am2d_key key, void (*callback)(void)) {
    keyhandler[key] = callback;
}

void am2d_key_unbind(enum am2d_key key) {
    keyhandler[key] = NULL;
}
