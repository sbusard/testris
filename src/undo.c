/*
 * TEsTris
 *
 * Created by Simon Busard 22.08.2007
 *
 * undo.c
 * ------
 * Undo commands
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

#include "undo.h"
#include "constants.h"

/*
 * Free a simple historic structure
 */
static void undo_free_historic(struct Var_conf *config,struct Undo_i *item);

/* ----- [ undo_init ] ------------------------------------------------------ */
struct Undo* undo_init()
{
    struct Undo *undo = NULL;
    undo = malloc(sizeof(struct Undo));
    undo->first = NULL;
    undo->last = NULL;
    undo->counter = 0;

    return undo;
}

/* ----- [ undo_free ] ------------------------------------------------------ */
void undo_free(struct Var_conf *config,struct Undo *undo_historic)
{
    struct Undo_i* cur_item = undo_historic->first;
    struct Undo_i* next_item = NULL;


    while(cur_item != NULL)
    {
	next_item = cur_item->next;
	undo_free_historic(config,cur_item);
	cur_item = next_item;
    }

    free(undo_historic);	
}

/* ----- [ undo_save ] ------------------------------------------------------ */
void undo_save(struct Var_conf *config, struct Undo *undo_historic)
{
    struct Undo_i *item = NULL, *del = NULL;
    int i = 0, j = 0;

    // Malloc item
    item = malloc(sizeof(struct Undo_i));
    
    // Clone model
	item->model = model_clone(config->model);

    // Copy piece
    item->piece = config->pc_cur_id;

    // Copy level and score
    item->score = config->score;
    item->level = config->level;
    item->lines = config->lines;

    // Initialize references
    item->next = NULL;
    item->prev = NULL;

    // Update references
    if(undo_historic->counter > 0) // Already some historics
    {
	item->prev = undo_historic->first;
	undo_historic->first->next = item;

	undo_historic->first = item;

	if(undo_historic->counter++ == NB_UNDO)
	{
	    del = undo_historic->last;
	    undo_historic->last = del->next;
	    del->next->prev = NULL;

	    undo_free_historic(config,del);
	    
	    undo_historic->counter--;
	}
    }
    else // No historic yet
    {
	undo_historic->first = item;
	undo_historic->last = item;

	undo_historic->counter++;
    }
}

/* ----- [ undo_load ] ------------------------------------------------------ */
void undo_load(struct Var_conf *config, struct Undo *undo_historic)
{
    int i = 0, j = 0;
    struct Undo_i *del = NULL;

    if(undo_historic->counter > 0)
    {
	// Get historic
	del = undo_historic->first;

        // Copy model
	for(i = 0;i < PNL_HB;i++)
	    for(j = 0;j < PNL_LB;j++)
	        model_set(config->model,i,j,model_get(del->model,i,j));

	// Copy piece
        config->pc_next_id = config->pc_cur_id;
	config->pc_cur_id = del->piece;

	// Copy level and score
	config->level = del->level;
	config->score = del->score;
	config->lines = del->lines;

        // Restart position
	config->piece_pos.x = (PNL_LB / 2) - (PC_NB_LBLC / 2);
        config->piece_pos.y = 1;

	// Update references
        undo_historic->first = del->prev;
        if(--(undo_historic->counter) > 0)
	    del->prev->next = NULL;

	// Free historic
        undo_free_historic(config,del);
    }
}

/* ----- [ undo_free_historic ] --------------------------------------------- */
static void undo_free_historic(struct Var_conf *config,struct Undo_i *item)
{
	model_free(item->model);
    free(item);
}

