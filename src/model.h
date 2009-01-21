/*
 * TEsTris
 *
 * Created by Simon Busard on 22.08.2007
 *
 * model.h
 * -------
 * Prototype - Model functions
 */

/* 
 * Copyright (C) 2008 Busard Simon
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef MODEL
#define MODEL

#include "pieces.h"

struct row {
	struct row* next;
	struct row* prev;
	enum Color* row;
};

struct model {
	struct row* first;
	struct row* last;
	int height;
	int width;
};

/*
 * Init a model with width x height cells containing def
 */
struct model* model_init(int width, int height, enum Color def);

/*
 * Free memory used by model. Model remains then unavailable
 */
void model_free(struct model* model);

#endif
