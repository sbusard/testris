/*
 * TEsTris
 *
 * Created by Simon Busard on 22.08.2007
 *
 * ai.h
 * ----
 * Prototype - Artificial intelligence functions
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

#ifndef __AI__ 
#define __AI__

#include "constants.h"
#include <SDL/SDL.h>

/*
 * Start artificial intelligence
 */
void *ai_start(void *arg);

/*
 * Put the current piece at position pos
 */
void ai_go(struct Var_conf *config,SDL_Rect pos);

/*
 * Get best position for current piece
 */
void ai_best_pos(struct Var_conf *config,enum Color **model_tmp,
		 SDL_Rect *pos,int *turning);

/*
 * Return score of piece piece_id in model at position position
 */
int ai_score_pos(struct Var_conf *config,
				 enum Color **model,
				 enum Piece_bloc piece_id,
				 SDL_Rect position);
#endif
