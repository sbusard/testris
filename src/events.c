/*
 * TEsTris
 *
 * Created by Simon Busard on 22.08.2007
 *
 * events.c
 * --------
 * Events managment functions
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

#include "events.h"
#include "constants.h"
#include "game.h"
#include "music.h"
#include "undo.h"
#include "ai.h"
#include "model.h"
#include <stdlib.h>

/* ----- [ play ] ----------------------------------------------------------- */
void play(struct Var_conf *config)
{
    // General init
    SDL_Event event;
    int cont = 1;
    int i = 0;
    int j = 0;

    // Button pressed indicators
    int space_pressed = 0;
    int shift_pressed = 0;
    int up_pressed = 0;
    int undo_pressed = 0;
    int mute_pressed = 0;

    // Mouse related
    int mouse_moved;
    int mouse_x = 0;
    SDL_Rect mouse_pos;
    SDL_Rect mouse_ghost_pos;

    // Music related
    int mute_state = OFF;
    config->music_vol = (int)MUSIC_INIT_VOL;

    // AI related
    pthread_t ai;

	// Some init for game
	config->dropping = 0;
	config->down_pressed = 0;

    // Mouse init
    config->mouse_pos.x = 0;
    config->mouse_pos.y = 0;

    // Pieces initialization
    pc_init(config);
    // Model initialization
	config->model = model_init(PNL_LB,PNL_HB,CL_MPT);
    config->pc_cur_id = PCMPTY;
    config->pc_next_id = PCMPTY;
	
    // State init
    config->state = J_PLAY;
    // Init timer
    if((config->timer = SDL_AddTimer(config->interv,step,config)) == NULL)
		fprintf(stderr,
			"[ERROR] Cannot initialize timer in %s at line %d.\n",
			__FILE__,
			__LINE__);

    // Bootstrap of the game
    add(config);
    add(config);

    disp_gamepanel(config);
    disp_next_pc(config);

    // Init scores
    config->score = 0;
    config->lines = 0;
    config->level = 0;
    disp_scores(config);
    config->interv = INTERV;

    // Init undo
    config->undo = undo_init();

    // Play music
    if(PLAY_MUSIC)
    {
		music_play(config);
		music_volume(config->music_vol);
    }

    // Display initial scores
    disp_scores(config);
    
    while(cont)
    {
	if(SDL_WaitEvent(&event))
	{
	    switch(event.type)
	    {
		// Window closed
		case SDL_QUIT:
		    config->state = J_QUIT;
		    cont = 0;
		    break;
		// Window lost focus
		case SDL_ACTIVEEVENT:
		    if (((event.active.state & SDL_APPINPUTFOCUS)
		          == SDL_APPINPUTFOCUS) && !event.active.gain)
			if(config->state == J_PLAY && ENABLE_AUTOPAUSE)
			{
			    if(!SDL_RemoveTimer(config->timer))
			        fprintf(stderr,
			    "[ERROR] Cannot remove timer in %s at line %d.\n",
					    __FILE__,__LINE__);
			    config->state = J_PAUSE;
			    disp_pause(config,1);
			}
		    break;
        // Mouse motion
        case SDL_MOUSEMOTION:
            if(ENABLE_MOUSE && config->state == J_PLAY)
            {
                config->mouse_pos.x = event.motion.x;
                config->mouse_pos.y = event.motion.y;
                if(event.motion.x >= (WIN_PNL_SP - PC_NB_LBLC/2 * BLC_L) 
                   & event.motion.x < (PNL_L + PC_NB_LBLC/2 * BLC_L)
                   )//& ((event.motion.x - WIN_PNL_SP) 
                     /// (BLC_L + BLC_SP) + 1 - PC_NB_LBLC/2) != mouse_pos.x
                   //& abs(event.motion.x - mouse_x) >= (BLC_L))
                {
                    mouse_moved = 1;
                    mouse_x = event.motion.x;
                    while(mouse_moved &&
                          (abs(mouse_x
                              - (int)(WIN_PNL_SP 
                                 + (((BLC_L + BLC_SP)
                                    * (config->piece_pos.x
                                       + (PC_NB_LBLC/2))) + (BLC_SP/2))
                                )
                             ) >= (BLC_L/2 + 2)))
                    {
                        mouse_moved = move(config,
                            (mouse_x < 
                                (int)(WIN_PNL_SP 
                                 + (((BLC_L + BLC_SP)
                                    * (config->piece_pos.x
                                       + (PC_NB_LBLC/2))) + (BLC_SP/2))
                                )) ? LEFT : RIGHT);
                    }

                    /*mouse_pos.y = config->piece_pos.y;
                    mouse_pos.x = (event.motion.x - WIN_PNL_SP) 
                                  / (BLC_L + BLC_SP) +1 - PC_NB_LBLC/2;
                    if(check_pc(config,config->model,
                                config->pieces[config->pc_cur_id],
                                mouse_pos))
                    {
                        config->piece_pos.x = mouse_pos.x;
                        mouse_ghost_pos.x = config->piece_pos.x;
                        mouse_ghost_pos.y = config->piece_pos.y;
                        // Piece ghost
                        while(check_pc(config,
                                   config->model,
                                   config->pieces[config->pc_cur_id],
                                   mouse_ghost_pos) 
                              && mouse_ghost_pos.y != PNL_HB)
                            mouse_ghost_pos.y++;
                        config->ghost_pos.x = mouse_ghost_pos.x;
                        config->ghost_pos.y = --mouse_ghost_pos.y;

                        disp_gamepanel(config);
                    }*/
                       
                    /*mouse_pos.x = (event.motion.x - WIN_PNL_SP) 
                                  / (BLC_L + BLC_SP) + 1 - PC_NB_LBLC/2;
                    SDL_Surface *bar;
                    SDL_Rect bar_pos;
                    SDL_Surface *bg;
                    SDL_Rect bg_pos;

                    bar_pos.y = WIN_PNL_SP + PNL_H + BLC_SP;
                    bar_pos.x = event.motion.x - (event.motion.x % (int)(BLC_SP + BLC_L)) + BLC_SP;
                    bar = SDL_CreateRGBSurface(SDL_HWSURFACE,BLC_L,BLC_SP,32,0,0,0,0);
                    SDL_FillRect(bar,NULL,SDL_MapRGB(config->screen->format,0,0,0));

                    bg_pos.x = WIN_PNL_SP;
                    bg_pos.y = bar_pos.y;
                    bg = SDL_CreateRGBSurface(SDL_HWSURFACE,PNL_L,BLC_SP,32,0,0,0,0);
                    SDL_FillRect(bg,NULL,SDL_MapRGB(config->screen->format,200,200,200));

                    SDL_BlitSurface(bg,NULL,config->screen,&bg_pos);
                    SDL_BlitSurface(bar,NULL,config->screen,&bar_pos);
                    
                    SDL_Flip(config->screen);*/



                }
            }
            break;
        // Mouse buttons
        case SDL_MOUSEBUTTONDOWN:
            if(ENABLE_MOUSE)
                switch(event.button.button)
                {
                    case SDL_BUTTON_LEFT:
                        if(config->state == J_PLAY)
                            drop(config);
                        break;
                    case SDL_BUTTON_RIGHT:
                        if(config->state == J_PLAY)
                            turn(config,
                                 config->model,
                                 &(config->pc_cur_id),
                                 &(config->piece_pos),
                                 HORLO,
                                 1,1);
                        break;
                    case SDL_BUTTON_WHEELDOWN:
                        if(config->state == J_PLAY)
                        {
                            if(!SDL_RemoveTimer(config->timer))
                                fprintf(stderr,
                        "[ERROR] Cannot remove timer in %s at line %d.\n",
                                __FILE__,__LINE__);
                
                            // Signal that down is pressed
                            config->down_pressed = 1;
                            
                            step(config->interv,config);
                            if((config->timer =
                                SDL_AddTimer(config->interv,step,config))
                                == NULL)
                                fprintf(stderr,
                    "[ERROR] Cannot initialize timer in %s at line %d.\n",
                                    __FILE__,__LINE__);
                        }
                        default:
                            break;
                    }
            break;
		// A key released			
		case SDL_KEYUP:
		    switch(event.key.keysym.sym)
		    {
		        case SDLK_d:
		        case SDLK_SPACE:
			   space_pressed = 0;
			    break;
			case SDLK_DOWN:
			    config->down_pressed = 0;
			    break;
			case SDLK_LSHIFT:
			    if(USE_SHIFT)
			        SDL_EnableKeyRepeat(TCH1,TCH2);
			    shift_pressed = 0;
			    break;
			case SDLK_UP:
			    up_pressed = 0;
			    break;
			case SDLK_z:
			case SDLK_u:
			    undo_pressed = 0;
			    break;
			case SDLK_m:
			    mute_pressed = 0;
			    break;
			default:
			    break;
		    }
		    break;
		// A key pressed
		case SDL_KEYDOWN:
		    switch(event.key.keysym.sym)
		    {
			case SDLK_ESCAPE:
			case SDLK_q:
			    // Saving scores
			    if(config->state == J_PLAY
			       || config->state == J_PAUSE)
				high_save(config->lines,config->score);
			    config->state = J_QUIT;
			    cont = 0;
			    break;
			case SDLK_s:
				// Saving scores
			    if(config->state == J_PLAY
			       || config->state == J_PAUSE)
				high_save(config->lines,config->score);
			    config->state = J_STOP;
			    cont = 0;
			    break;
			case SDLK_n:
				// Saving scores
			    if(config->state == J_PLAY
			       || config->state == J_PAUSE)
				high_save(config->lines,config->score);
			    config->state = J_PLAY;
			    cont = 0;
			    break;
			case SDLK_p:
			    if(config->state == J_PLAY)
			    {
				if(!SDL_RemoveTimer(config->timer))
				    fprintf(stderr,
		    "[ERROR] Cannot remove timer in %s at line %d.\n",
					    __FILE__,__LINE__);
				config->state = J_PAUSE;
				disp_pause(config,1);
			    }
			    else if(config->state == J_PAUSE)
			    {
				if((config->timer = 
			    SDL_AddTimer(config->interv,step,config))
			    == NULL)
				    fprintf(stderr,
		    "[ERROR] Cannot initialize timer in %s at line %d.\n",
				    __FILE__,__LINE__);
				config->state = J_PLAY;
				disp_pause(config,0);
			    }
			    break;
			case SDLK_DOWN:
			    if(config->state == J_PLAY)
			    {
				if(!SDL_RemoveTimer(config->timer))
				    fprintf(stderr,
		    "[ERROR] Cannot remove timer in %s at line %d.\n",
				    __FILE__,__LINE__);
	
				// Signal that down is pressed
				config->down_pressed = 1;
				
				step(config->interv,config);
				if((config->timer =
				    SDL_AddTimer(config->interv,step,config))
				    == NULL)
				    fprintf(stderr,
		"[ERROR] Cannot initialize timer in %s at line %d.\n",
					    __FILE__,__LINE__);
			    }
			    break;
			case SDLK_LEFT:
			    if(config->state == J_PLAY)
				move(config,LEFT);
			    break;
			case SDLK_RIGHT:
			    if(config->state == J_PLAY)
				move(config,RIGHT);
			    break;
			case SDLK_d:
			case SDLK_SPACE:
			    if(config->state == J_PLAY
			       && space_pressed == 0)
				drop(config);
			    space_pressed = 1;
			    break;
			case SDLK_UP:
			    if(config->state == J_PLAY && !up_pressed) 
				turn(config,
				     config->model,
				     &(config->pc_cur_id),
				     &(config->piece_pos),
				     HORLO,
				     1,1);
			    if(shift_pressed)
				up_pressed = 1;
			    break;
			case SDLK_LSHIFT:
			    if(config->state == J_PLAY && USE_SHIFT)
				SDL_EnableKeyRepeat(TCHSHIFT,TCHSHIFT);
			    shift_pressed = 1;
			    break;
			case SDLK_z:
			case SDLK_u:
			    if(config->state == J_PLAY && USE_UNDO
			       && !undo_pressed && config->undo->counter > 0)
				undo(config);
			    undo_pressed = 1;
			    break;
			case SDLK_m:
			    if(!mute_pressed && PLAY_MUSIC)
			    {
				mute_state = (mute_state == ON) ? OFF : ON;
				music_mute(config,mute_state);
			    }
			    break;
			case SDLK_v:
			    if(PLAY_MUSIC)
			    {
				config->music_vol +=
				    (config->music_vol >= MIX_MAX_VOLUME) ? 0
									  : 10;
				music_volume(config->music_vol);
			    }
			    break;
			case SDLK_c:
			    if(PLAY_MUSIC)
			    {
				config->music_vol +=
				    (config->music_vol <= 0) ? 0 : -10;
				music_volume(config->music_vol);
			    }
			case SDLK_a:
			    // Launch artificial intelligence
			    if(!config->ai_started)
			    {
				config->ai_started = 1;
				if(pthread_create(&ai,NULL,ai_start,config))
				    fprintf(stderr,
				"[ERROR] Cannot start AI in %s at line %d\n",
				__FILE__,__LINE__);
			    }
			    break;
			default:
			    break;
			}
			default:
			    break;
	    }

	    //SDL_Delay(20);
	}
    }

    // Closing and cleaning
    // Free graphical surfaces
    SDL_FillRect(config->panel,NULL,SDL_MapRGB(config->screen->format,0,0,0));
    SDL_BlitSurface(config->panel,NULL,config->screen,&config->pnl_pos);
    SDL_Flip(config->screen);
    // Reset scores
    config->score = 0;
    config->level = 0;
    config->lines = 0;
    config->interv = INTERV;
    disp_scores(config);
    // Remove timer
    SDL_RemoveTimer(config->timer);
    // Free pieces
    pc_free(config);
    // Free model
	model_free(config->model);
    // Free undo
    undo_free(config,config->undo);
    // Free AI
    config->ai_started = 0;
    // Stop music
    if(PLAY_MUSIC)
	music_stop(config);
    // Display empty screen
    disp_window(config);
}

