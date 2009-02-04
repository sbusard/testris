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

#include "constants.h"
#include "pieces.h"

struct row {
	struct row* next;
	struct row* prev;
	enum Color* values;
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

/*
 * return current height of the model
 */
int model_height(struct model* model);

/*
 * return current width of the model
 */
int model_width(struct model* model);

/*
 * get value at jth position of ith row of model.
 * Return -1 if (i,j) do not belong to model
 */
enum Color model_get(struct model* model, int i, int j);

/*
 * set value at jth position of ith row of model to value.
 * Return -1 if (i,j) do not belong to model.  1 otherwise
 */
int model_set(struct model* model, int i, int j, enum Color value);

/*
 * add a new line full of def above all others
 */
int model_add_first(struct model *model,enum Color def);

/*
 * get a clone of model
 */
struct model* model_clone(struct model* model);

#endif
