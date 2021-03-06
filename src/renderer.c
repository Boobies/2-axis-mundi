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

#include <am2d/actors.h>
#include <am2d/renderer.h>
#include <SDL2/SDL.h>

void am2d_render(am2d_context *context) {
    SDL_RenderClear(context->renderer);
    for (struct am2d_actor_queue *p = am2d_actor_queue; p != NULL; p = p->next)
        am2d_actor_draw(p->actor);
    SDL_RenderPresent(context->renderer);
}
