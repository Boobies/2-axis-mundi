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

#include <assert.h>
#include <am2d/actors.h>
#include <am2d/sprites.h>

struct am2d_actor_queue *am2d_actor_queue = NULL;

am2d_actor *am2d_actor_new(am2d_sprite *sprite) {
    am2d_actor *actor;

    if ((actor = malloc(sizeof *actor)) == NULL)
        return NULL;

    actor->sprite = sprite;
    am2d_actor_setlocation(actor, 0, 0);
    am2d_actor_setangle(actor, 0);
    am2d_actor_setflip(actor, AM2D_NOFLIP);
    am2d_actor_setanimation(actor, 0, 0);

    return actor;
}

void am2d_actor_delete(am2d_actor *actor) {
    assert(actor != NULL);

    free(actor);
}

void am2d_actor_setlocation(am2d_actor *actor, int x, int y) {
    assert(actor != NULL);

    actor->x = x;
    actor->y = y;
}

void am2d_actor_setangle(am2d_actor *actor, float alpha) {
    assert(actor != NULL);

    actor->alpha = alpha;
}

void am2d_actor_setflip(am2d_actor *actor, enum am2d_flip flip) {
    assert(actor != NULL);

    actor->flip = flip;
}

void am2d_actor_setanimation(am2d_actor *actor, size_t animation_number, int frame_number) {
    assert(actor != NULL);
    assert(animation_number < actor->sprite->animation_count);
    assert(frame_number < actor->sprite->animation[animation_number].frame_count);

    actor->animation_number = animation_number;
    actor->frame_number = frame_number;
}

void am2d_actor_draw(am2d_actor *actor) {
    assert(actor != NULL);

    SDL_Rect src = { actor->frame_number * actor->sprite->frame_width, actor->animation_number * actor->sprite->frame_height, actor->sprite->frame_width, actor->sprite->frame_height },
             dst = { actor->x, actor->y, actor->sprite->frame_width, actor->sprite->frame_height };

    SDL_RenderCopyEx(actor->sprite->renderer, actor->sprite->texture, &src, &dst, actor->alpha, NULL, actor->flip);

    switch (actor->sprite->animation[actor->animation_number].type) {
    case AM2D_ANIM_STATIC:
        break;
    case AM2D_ANIM_ONCE:
        if (actor->frame_number < actor->sprite->animation[actor->animation_number].frame_count - 1)
            ++actor->frame_number;
        break;
    case AM2D_ANIM_LOOP:
        actor->frame_number = (actor->frame_number + 1) % actor->sprite->animation[actor->animation_number].frame_count;
        break;
    }
}

void am2d_actor_show(am2d_actor *actor) {
    struct am2d_actor_queue *node;

    assert(actor != NULL);

    if ((node = malloc(sizeof *actor)) == NULL)
        return;

    node->actor = actor;
    node->next = am2d_actor_queue;
    am2d_actor_queue = node;
}

void am2d_actor_hide(am2d_actor *actor) {
    assert(actor != NULL);
    struct am2d_actor_queue *p = am2d_actor_queue;

    if (am2d_actor_queue->actor == actor) {
        am2d_actor_queue = am2d_actor_queue->next;
        free(p);
        return;
    }
    for (struct am2d_actor_queue *p = am2d_actor_queue; p != NULL; p = p->next)
        if (p->next->actor == actor) {
            p->next = p->next->next;
            free(p->next);
            break;
        }
}
