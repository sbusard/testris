/*
 * TEsTris
 *
 * Created by Simon Busard on 21.02.2008
 *
 * display.h
 * ---------
 * Prototype - Display functions
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

#ifndef DISPLAY
#define DISPLAY

#include "constants.h"
#include <SDL/SDL.h>

/*
 * Initialize video mode and other display functions
 */
void disp_init(struct Var_conf *config);

/*
 * Display the window of the game
 */
void disp_window(struct Var_conf *config);

/*
 * Display the game panel
 */
void disp_gamepanel(struct Var_conf *config);

/*
 * Display next piece
 */
void disp_next_pc(struct Var_conf *config);

/*
 * Display pause
 */
void disp_pause(struct Var_conf *config,int pause);

/*
 * Display game over message
 */
void disp_gameover(struct Var_conf *config);

/*
 * Display scores
 */
void disp_scores(struct Var_conf *config);

/*
 * Display high scores
 */
void disp_highscores(struct Var_conf *config);

/*
 * Return surface containing text in color with size
 */
SDL_Surface* disp_text(char *text,SDL_Color color,int size);

/*
 * Initialize blocs definition
 */
void disp_bloc_init(struct Var_conf *config);

/*
 * Free memory related to blocs
 */
void disp_bloc_free();

#endif
