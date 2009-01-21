/*
 * TEsTris
 *
 * Created by Simon Busard on 22.08.2007
 *
 * model.c
 * -------
 * Model functions
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

#include <stdlib.h>
#include "model.h"

struct model* model_init(int width, int height, enum Color def)
{
	struct model* model = malloc(sizeof(struct model));
	model->height = height;
	model->width = width;
	struct row* prev = NULL;
	struct row* current = NULL;

	int i = 0;

	for(i = 0;i < height;i++)
	{
		current = malloc(sizeof(struct row));
		if(i == 0)
			model->first = current;
		current->prev = prev;
		if(prev != NULL)
			current->prev->next = current;
		current->next = NULL;
		current->row = malloc(sizeof(enum Color) * width);

		int j = 0;
		for(j = 0;j < width;j++)
		{
			current->row[j] = def;
		}

		if(i == height - 1)
		{
			model->last = current;
		}

		prev = current;
		current = current->next;
	}
	
	return model;
}

void model_free(struct model* model)
{
	struct row* current = model->first;
	struct row* next = current->next;

	while(next != NULL)
	{
		next = current->next;
		free(current->row);
		free(current);
		current = next;
	}
}

int main(int argc, char* argv[])
{
	struct model* model = model_init(12,24,CL_MPT);
	model_free(model);

	return EXIT_SUCCESS;
}
