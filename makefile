#
# Copyright 2017 Bogdan Barbu
#
# This file is part of 2 Axis Mundi.
#
# 2 Axis Mundi is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# 2 Axis Mundi is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with 2 Axis Mundi.  If not, see <http://www.gnu.org/licenses/>.
#

AM_SRC_FILES = engine.c input.c physics.c renderer.c sprites.c
AM_OBJ_FILES = $(AM_SRC_FILES:.c=.o)
AM_LIB_FILE = libam2d_engine.a

SRC_FILES += $(AM_SRC_FILES)
LIB_FILES += $(AM_LIB_FILE)

include makebs/makebs.mk

INSTALL = $(INC_DIR) $(LIB_DIR)

$(LIB_DIR)/$(AM_LIB_FILE): $(AM_OBJ_FILES:%=$(OBJ_DIR)/%) | $(LIB_DIR)
	$(AR) $(ARFLAGS) $@ $?
