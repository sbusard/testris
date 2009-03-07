/*
 * TEsTris
 *
 * Created by Simon Busard 22.08.2007
 *
 * undo.h
 * ------
 * Prototype - Undo commands
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

#ifndef UNDO
#define UNDO

#include "constants.h"
#include "model.h"

// Structure represeting an undo item.  It contains a copy
// of the model and the piece corresponding.
// It contains also pointers to previous and next items.
struct Undo_i {
    struct Undo_i* next;
    struct Undo_i* prev;

    int level;
    int score;
    int lines;

    struct model *model;
    enum Piece_bloc piece;
};

// Structure containing all undo items. It contains a pointer
// to first and last items and a counter counting number of valid items.
struct Undo {
    struct Undo_i* first;
    struct Undo_i* last;
    int counter;
};

/*
 * Return initialized structure containing historic
 */
struct Undo * undo_init();

/*
 * Free structure containing historic
 */
void undo_free(struct Var_conf *config, struct Undo *undo_historic);

/*
 * Save current model and piece in undo historic
 */
void undo_save(struct Var_conf *config, struct Undo *undo_historic);

/*
 * Load last model and piece in model
 */
void undo_load(struct Var_conf *config, struct Undo *undo_historic);

#endif
