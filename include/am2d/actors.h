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

#ifndef AM2D_ACTORS_H
#define AM2D_ACTORS_H

#include <am2d/sprites.h>
#include <stddef.h>

typedef struct {
    am2d_sprite *sprite;
    float x, y, alpha;
    float vel_x, vel_y, vel_alpha;
    float acc_x, acc_y, acc_alpha;
    enum am2d_flip flip;
    size_t animation_number;
    int frame_number;
} am2d_actor;

extern struct am2d_actor_queue {
    am2d_actor *actor;
    struct am2d_actor_queue *next;
} *am2d_actor_queue;

am2d_actor *am2d_actor_new(am2d_sprite *);
void am2d_actor_delete(am2d_actor *);
void am2d_actor_setlocation(am2d_actor *, float, float);
void am2d_actor_setangle(am2d_actor *, float);
void am2d_actor_setvelocity(am2d_actor *, float, float, float);
void am2d_actor_setacceleration(am2d_actor *, float, float, float);
void am2d_actor_setflip(am2d_actor *, enum am2d_flip);
void am2d_actor_setanimation(am2d_actor *, size_t, int);
void am2d_actor_draw(am2d_actor *);
void am2d_actor_show(am2d_actor *);
void am2d_actor_hide(am2d_actor *);

#endif
