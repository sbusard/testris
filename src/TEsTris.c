/*
 * TEsTris
 *
 * Created by Simon Busard on 22.08.2007
 *
 * TEsTris.c
 * ---------
 *  Screen of the game
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

#include <SDL/SDL.h>
#include <time.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include "constants.h"
#include "game.h"
#include "display.h"
#include "config.h"
#include "music.h"
#include "events.h"

/* ----- [ main ] ----------------------------------------------------------- */
int main(int argc,char *argv[])
{
    // Configuration
    struct Var_conf *config = malloc(sizeof(struct Var_conf));
    config->screen = NULL;
    config->panel = NULL;
    config->state = J_PLAY;

    // Load configuration
    conf_load(config);
    
    config->interv = INTERV;

    SDL_Event event;
    int cont = 1;

    // Init to use rand()
    srand(time(NULL));

    // Init SDL_ttf library
    if(TTF_Init() == -1)
	fprintf(stderr,"[ERROR] Cannot initialize TTF library.\n");

    // Init music library
    music_init(config);

    disp_init(config);
    disp_window(config);

    // Keys repeat
    SDL_EnableKeyRepeat(TCH1,TCH2);	

    // Waiting events
    while(cont)
    {
	if(SDL_WaitEvent(&event))
	{
	    switch(event.type)
	    {
		case SDL_QUIT:
		    cont = 0;
		    break;
		case SDL_KEYDOWN:
		    switch(event.key.keysym.sym)
		    {
			case SDLK_ESCAPE:
			case SDLK_q:
			    cont = 0;
			    break;
			case SDLK_n:
			case SDLK_j:
			    config->state = J_PLAY;
			    while(config->state == J_PLAY) play(config);
			    if(config->state == J_QUIT) cont = 0;
			    break;
			default:
			    break;
			}
		    break;
	    }
	}
    }

    // Closing
    SDL_FreeSurface(config->panel);
    SDL_FreeSurface(config->screen);
    free(config);
    disp_bloc_free();
    music_free();
    SDL_Quit();
    TTF_Quit();
    return EXIT_SUCCESS;
}

