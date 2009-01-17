/*
 * TEsTris
 *
 * Created by Simon Busard on 22.08.2007
 *
 * game.h
 * ------
 * Prototype - Game functions
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

#ifndef GAME
#define GAME

/*
 * Do a step with the piece
 */
Uint32 step(Uint32 interv,void *param);

/*
 * Move current piece to the direction
 * Return 1 if piece was moved, 0 otherwise
 */
int move(struct Var_conf *config,enum Direction direction);

/*
 * Drop piece on the heap
 */
void drop(struct Var_conf *config);

/*
 * Add a piece in the game
 */
void add(struct Var_conf *config);

/*
 * Check full lines and remove them
 */
void check(struct Var_conf *config);

/*
 * Remove complete lines from model and blink them if blink is not 0.
 * Return the number of lines removed
 */
int remove_lines(struct Var_conf *config,enum Color **model, int blink);

/*
 * Turn the current piece
 */
void turn(struct Var_conf *config,
	  enum Color **model,
	  enum Piece_bloc *piece_id,
	  SDL_Rect *position,
	  enum Rotation rotation,
	  int ghost,
	  int disp);

/*
 * Undo last drop
 */
void undo(struct Var_conf *config);

/*
 * Manage end of the game
 */
void lost(struct Var_conf *config);

/*
 * Check if piece can be at position pos in the model
 */
int check_pc(struct Var_conf *config,
	     enum Color **model,
	     enum Color **piece,
	     SDL_Rect pos);

/*
 * Put the current piece in the model
 */
void takeoff(struct Var_conf *config,
	     enum Color **model,
	     enum Piece_bloc *pc_id,
	     SDL_Rect position,
	     int empty);

/*
 * Initialize different useful pieces in config
 */
void pc_init(struct Var_conf *config);

/*
 * Free memory allocated for pieces in config
 */
void pc_free(struct Var_conf *config);

#endif
