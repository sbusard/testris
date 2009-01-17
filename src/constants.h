/*
 * TEsTris
 *
 * Created by Simon Busard 22.08.2007
 *
 * constants.h
 * -----------
 * List of useful constants
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

#ifndef CONSTANTS
#define CONSTANTS

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <math.h>
#include "pieces.h"

/*----- Default settings ---------------------------------------------------- */

//Display settings
#define DEF_BLC_L 16		// Width of blocs in pixel
#define DEF_BLC_H DEF_BLC_L	// Height of blocs
#define DEF_BLC_SP 2		// Space between blocs
#define DEF_PNL_LB 12		// Width of the game panel in blocs
#define DEF_PNL_HB 21		// Height of the game panel in blocs
#define DEF_WIN_L 500		// Width of the game window

// Show settings
#define DEF_SHOW_NEXT_PC 1	// Whether show or not the next piece
#define DEF_SHOW_COLORS 0	// Whether show color of not pieces
#define DEF_SHOW_GHOST 1	// Whether show or not piece ghost
#define DEF_SHOW_HGSCRS 0	// Whether show or not highscores
#define DEF_NB_HGSCRS 10	// Number of highscores shown

// Game settings
#define DEF_LN_BY_LVL 10	// Number of lines to delete to update level
#define DEF_SC_COEF 99		// Multiplicative coefficent of score
#define DEF_LN_NBCLIC 0		// Number of blinks before deleting line
#define DEF_LN_DELAY 100	// Delay between blinks

// Interval settings
#define DEF_INTERV 900		// Basis number of ms 
				// between each step of the current piece
#define DEF_INTERV_COEF 1.25	// Coefficient for new interval
#define DEF_TCH1 200		// Number of ms before key repeat
#define DEF_TCH2 50		// Number of ms between each key repeat
#define DEF_TCHSHIFT 20		// Number of ms between all key repeat
				// when shift is hold

// Undo settings
#define DEF_USE_UNDO 0		// Whether use or not undo command
#define DEF_NB_UNDO 3		// Number of previous moves saved in historic

// Miscellenious
#define DEF_USE_SHIFT 1		// Whether use or not speed command
#define DEF_ENABLE_AUTOPAUSE 1 // Whether use or not auto pause
#define DEF_ENABLE_MOUSE 0  // Whether enable or not mouse playing

// Music
#define DEF_PLAY_MUSIC 1	// Whether play or not music
#define DEF_MUSIC_ID 1		// Id of music played
#define DEF_MUSIC_INIT_VOL 128	// Initial volume of music


/*----- Other settings ------------------------------------------------------ */

// Full lines settings
#define LN_NBCLIC (config->set_blinks_lines)	
#define LN_DELAY (config->set_blinks_delay)

// Intervalles
#define TCH1 (config->set_key_repeat_delay)
#define TCH2 (config->set_key_repeat_interv)
#define TCHSHIFT (config->set_speed_cmd_interv)
#define INTERV (config->set_init_interval)
#define INTERV_COEF (config->set_interval_coefficient)

// Show settings
#define SHOW_NEXT_PC (config->show_next_piece)
#define SHOW_COLORS (config->show_colors)	
#define SHOW_GHOST (config->show_ghost)
#define SHOW_HGSCRS (config->show_highscores)

#define USE_UNDO  (config->use_undo)
#define NB_UNDO (config->set_nb_undo)

#define USE_SHIFT (config->use_speed_cmd)

#define ENABLE_AUTOPAUSE (config->enable_auto_pause)

#define ENABLE_MOUSE (config->enable_mouse)

// Music settings
#define PLAY_MUSIC (config->set_music_enabled)
#define MUSIC_ID (config->set_music_id)
#define MUSIC_INIT_VOL (config->set_music_initial_volume)

// Speed settings
#define LEVEL config->level
#define INTERV_NEW ((INTERV) / pow(INTERV_COEF,LEVEL))
			// INTERV_NEW is the interval of time between
			// each step of the current piece

// Scores settings
#define LN_BY_LVL (config->set_lines_by_level)	
#define SC_COEF (config->set_score_coefficient)
			// Score is get like that :
			// 	score = SC_COEF * sum * sum * level
			// where sum is the number of simultaneous deleted
			// lines.

// Highscores settings
#define NB_HGSCRS (config->set_number_highscores)

// Text settings
#define FONT "fonts/arial.ttf" // Font used to display text
#define PGO_SIZE 30	// Size of words "PAUSE" and "GAME OVER"
#define SCR_SIZE 14	// Size of scores
#define SCR_POS_X (WIN_PNL_SP * 2 + PNL_L)
#define SCR_POS_Y (WIN_H/2)
#define SCR_BUF_SIZE 128

// Defines for display
#define BLC_L (config->disp_bloc_width)
#define BLC_H (config->disp_bloc_height)
#define BLC_SP (config->disp_blocs_space)
#define PNL_LB (config->disp_panel_width)
#define PNL_HB (config->disp_panel_height)
#define PNL_L ((BLC_L * PNL_LB) + (BLC_SP * (PNL_LB + 1))) // Panel width in px
#define PNL_H ((BLC_H * PNL_HB) + (BLC_SP * (PNL_HB + 1))) // Panel height in px
#define WIN_PNL_SP 25 	// Space between window and game panel
#define WIN_L (config->disp_window_width)
#define WIN_H (PNL_H + (WIN_PNL_SP * 2)) // Height of the window
#define BG_POS_X PNL_L + 2 * WIN_PNL_SP // Position of the next piece display
#define BG_POS_Y WIN_PNL_SP

#define GNL_BUF_SIZE 128 // Buffer size for general purpose


/*----- Structures and enumerations ----------------------------------------- */

// Game states
enum Game
{
    J_STOP,J_PLAY,J_QUIT,J_LOST,J_PAUSE
};
enum Direction
{
    LEFT,RIGHT
};
enum Rotation
{
    HORLO,AHORLO
};

/*
 * Structure containing configuration variables for the game.
 */
struct Var_conf
{
    SDL_Surface *screen;
    SDL_Surface *panel;
    SDL_Rect pnl_pos;

    enum Color **model;

    long interv;
    SDL_TimerID timer;
    enum Game state;
    enum Piece_bloc pc_cur_id;
    enum Piece_bloc pc_next_id;
    enum Color ***pieces;
    SDL_Rect piece_pos;
    SDL_Rect ghost_pos;

    struct Undo *undo;
    
    int score;
    int lines;
    int level;

    Mix_Music *music;
    int music_vol;

    int ai_started;

	int dropping;
	int down_pressed;

    SDL_Rect mouse_pos;

    // Configuration variables
    double disp_bloc_width;
    double disp_bloc_height;
    double disp_blocs_space;
    double disp_panel_width;
    double disp_panel_height;
    double disp_window_width;
    double show_next_piece;
    double show_colors;
    double show_ghost;
    double show_highscores;
    double set_number_highscores;
    double set_lines_by_level;
    double set_score_coefficient;
    double set_blinks_lines;
    double set_blinks_delay;
    double set_init_interval;
    double set_interval_coefficient;
    double set_key_repeat_delay;
    double set_key_repeat_interv;
    double set_speed_cmd_interv;
    double set_nb_undo;
    double set_music_enabled;
    double set_music_id;
    double set_music_initial_volume;
    double use_undo;
    double use_speed_cmd;
    double enable_auto_pause;
    double enable_mouse;
};
#endif
