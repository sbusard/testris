/*
 * TEsTris
 *
 * Created by Simon Busard on 22.08.2007
 *
 * config.h
 * --------
 * Prototype - Game configuration functions
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

#ifndef __CONFIG__
#define __CONFIG__

#include "constants.h"

// Define table of possible configurations
// First element is command string,
// Second element is config to set,
// Third element is default value
#define CONF_TBL_L 28
#define CONF_TBL_NAMES  {   "disp_bloc_width",	    \
                            "disp_bloc_height",	    \
                            "disp_blocs_space",	    \
                            "disp_panel_width",	    \
                            "disp_panel_height",    \
                            "disp_windows_width",   \
                            "show_next_piece",	    \
                            "show_colors",	        \
                            "show_ghost",	        \
                            "show_highscores",	    \
                            "set_number_highscores",\
                            "set_lines_by_level",   \
                            "set_score_coefficient",\
                            "set_blinks_lines",	    \
                            "set_blinks_delay",	    \
                            "set_init_interval",    \
                            "set_interval_coefficient",	\
                            "set_key_repeat_delay", \
                            "set_key_repeat_interv",\
                            "set_speed_cmd_interv", \
                            "set_nb_undo",	        \
                            "set_music_enabled",    \
                            "set_music_id",	        \
                            "set_music_initial_volume",	\
                            "use_undo",		        \
                            "use_speed_cmd",        \
                            "enable_auto_pause",    \
                            "enable_mouse"          }
#define CONF_TBL_VALUES {   &(BLC_L),	    \
			    &(BLC_H),	    \
			    &(BLC_SP),	    \
			    &(PNL_LB),	    \
			    &(PNL_HB),	    \
			    &(WIN_L),	    \
			    &(SHOW_NEXT_PC),\
			    &(SHOW_COLORS), \
			    &(SHOW_GHOST),  \
			    &(SHOW_HGSCRS), \
			    &(NB_HGSCRS),   \
			    &(LN_BY_LVL),   \
			    &(SC_COEF),	    \
			    &(LN_NBCLIC),   \
			    &(LN_DELAY),    \
			    &(INTERV),	    \
			    &(INTERV_COEF), \
			    &(TCH1),	    \
			    &(TCH2),	    \
			    &(TCHSHIFT),    \
			    &(NB_UNDO),	    \
			    &(PLAY_MUSIC),  \
			    &(MUSIC_ID),    \
			    &(MUSIC_INIT_VOL), \
			    &(USE_UNDO),    \
			    &(USE_SHIFT),   \
                &(ENABLE_AUTOPAUSE),\
                &(ENABLE_MOUSE) }
#define CONF_TBL_DEFAULT    {	DEF_BLC_L,  	    \
				DEF_BLC_H,	    \
				DEF_BLC_SP,	    \
				DEF_PNL_LB,	    \
				DEF_PNL_HB,	    \
				DEF_WIN_L,	    \
	    		DEF_SHOW_NEXT_PC,   \
				DEF_SHOW_COLORS,    \
				DEF_SHOW_GHOST,	    \
				DEF_SHOW_HGSCRS,    \
	    		DEF_NB_HGSCRS,	    \
				DEF_LN_BY_LVL,	    \
		    	DEF_SC_COEF,	    \
				DEF_LN_NBCLIC,	    \
				DEF_LN_DELAY,	    \
				DEF_INTERV,	    \
				DEF_INTERV_COEF,    \
				DEF_TCH1,	    \
				DEF_TCH2,	    \
				DEF_TCHSHIFT,	    \
				DEF_NB_UNDO,	    \
				DEF_PLAY_MUSIC,	    \
				DEF_MUSIC_ID,	    \
				DEF_MUSIC_INIT_VOL, \
				DEF_USE_UNDO,	    \
				DEF_USE_SHIFT,      \
                DEF_ENABLE_AUTOPAUSE,   \
                DEF_ENABLE_MOUSE    }				


/*
 * Load configuration stocked in file TEsTris.conf in config
 */
void conf_load(struct Var_conf *config);

#endif
