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

#include <am2d/sprites.h>
#include <assert.h>
#include <json.h>
#include <SDL2/SDL_image.h>

am2d_sprite *am2d_sprite_new(am2d_context *context, const char *jsonfile) {
    am2d_sprite *sprite;
    json_value *desc;
    char *imagefile, *str;
    SDL_Surface *image;
    size_t animation_count;

    FILE *f = fopen(jsonfile, "r");
    desc = json_parse(f);
    fclose(f);

    animation_count = json_array_length(json_object_get(desc, "animations"));

    if ((sprite = malloc(sizeof *sprite + animation_count * sizeof (struct am2d_animation))) == NULL)
        return NULL;

    imagefile = json_string_get(json_object_get(desc, "file"));
    if ((image = IMG_Load(imagefile)) == NULL || (sprite->texture = SDL_CreateTextureFromSurface(sprite->renderer = context->renderer, image)) == NULL) {
        SDL_FreeSurface(image);
        free(sprite);
        free(desc);
        return NULL;
    }
    SDL_FreeSurface(image);

    sprite->frame_width = json_number_get(json_array_get(json_object_get(desc, "resolution"), 0));
    sprite->frame_height = json_number_get(json_array_get(json_object_get(desc, "resolution"), 1));

    sprite->animation_count = animation_count;
    for (size_t i = 0; i < animation_count; ++i) {

        str = json_string_get(json_object_get(json_array_get(json_object_get(desc, "animations"), i), "type"));
        if (strcmp(str, "static") == 0)
            sprite->animation[i].type = AM2D_ANIM_STATIC;
        else if (strcmp(str, "once") == 0)
            sprite->animation[i].type = AM2D_ANIM_ONCE;
        else if (strcmp(str, "loop") == 0)
            sprite->animation[i].type = AM2D_ANIM_LOOP;

        sprite->animation[i].frame_count = json_number_get(json_object_get(json_array_get(json_object_get(desc, "animations"), i), "frames"));
    }

    free(desc);

    return sprite;
}

void am2d_sprite_delete(am2d_sprite *sprite) {
    SDL_DestroyTexture(sprite->texture);
    free(sprite);
}
