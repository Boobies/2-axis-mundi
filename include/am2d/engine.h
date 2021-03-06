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

#ifndef AM2D_ENGINE_H
#define AM2D_ENGINE_H

#include <am2d/actors.h>
#include <am2d/context.h>
#include <am2d/input.h>
#include <am2d/physics.h>
#include <am2d/renderer.h>
#include <am2d/sprites.h>

am2d_context *am2d_new(const char *, int, int);
void am2d_delete(am2d_context *);
void am2d_run(am2d_context *);

#endif
