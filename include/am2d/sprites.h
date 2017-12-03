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

#ifndef AM2D_SPRITES_H
#define AM2D_SPRITES_H

#include <am2d/context.h>
#include <SDL2/SDL.h>
#include <stddef.h>

enum am2d_animation_type {
    AM2D_ANIM_STATIC,
    AM2D_ANIM_ONCE,
    AM2D_ANIM_LOOP
};

enum am2d_flip {
    AM2D_NOFLIP = SDL_FLIP_NONE,
    AM2D_HFLIP = SDL_FLIP_HORIZONTAL,
    AM2D_VFLIP = SDL_FLIP_VERTICAL
};

typedef struct {
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    int frame_width, frame_height;
    size_t animation_count;
    struct am2d_animation {
        enum am2d_animation_type type;
        int frame_count, frame_number;
    } animation[];
} am2d_sprite;

am2d_sprite *am2d_sprite_new(am2d_context *, const char *);
void am2d_sprite_delete(am2d_sprite *);
void am2d_sprite_draw(am2d_sprite *, size_t, int, int, float, enum am2d_flip);

#endif
