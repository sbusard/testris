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
#include <stdio.h>
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
		current->values = malloc(sizeof(enum Color) * width);

		int j = 0;
		for(j = 0;j < width;j++)
		{
			current->values[j] = def;
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
		free(current->values);
		free(current);
		current = next;
	}
}

enum Color model_get(struct model* model, int i, int j)
{
	// Out of bound of model
	if(i >= model->height || j >= model->width)
	{
		return -1;
	}

	// Get right row
	int k = i;
	struct row* current = model->first;
	while(k > 0)
	{
		current = current->next;
		k--;
	}

	// Return right value
	return current->values[j];
}

int model_set(struct model* model, int i, int j, enum Color value)
{
	// Out of bound of model
	if(i >= model->height || j >= model->width)
	{
		return -1;
	}

	// Get right row
	int k = i;
	struct row* current = model->first;
	while(k > 0)
	{
		current = current->next;
		k--;
	}

	// Set value
	current->values[j] = value;

	// Return success
	return 1;
}

struct model* model_clone(struct model* model)
{
	struct model* newMod = malloc(sizeof(struct model));
	newMod->height = model->height;
	newMod->width = model->width;
	struct row* prev = NULL;
	struct row* current = NULL;

	struct row* oldCur = model->first;

	int i = 0;

	for(i = 0;i < model->height;i++)
	{
		current = malloc(sizeof(struct row));
		if(i == 0)
			newMod->first = current;
		current->prev = prev;
		if(prev != NULL)
			current->prev->next = current;
		current->next = NULL;
		current->values = malloc(sizeof(enum Color) * model->width);

		int j = 0;
		for(j = 0;j < model->width;j++)
		{
			current->values[j] = oldCur->values[j];
		}

		if(i == model->height - 1)
		{
			newMod->last = current;
		}

		prev = current;
		current = current->next;
		oldCur = oldCur->next;
	}
	
	return model;

}

int main(int argc, char* argv[])
{
	struct model* model = model_init(12,24,CL_MPT);
	printf("%d\n",model_get(model,18,9));
	model_set(model,18,9,CL_GREEN1);
	printf("%d\n",model_get(model,18,9));
	struct model* newMod = model_clone(model);
	printf("%d\n",model_get(newMod,18,9));
	model_free(model);

	return EXIT_SUCCESS;
}
