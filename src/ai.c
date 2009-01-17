/*
 * TEsTris
 *
 * Created by Simon Busard on 22.08.2007
 *
 * ai.c
 * ----
 * Artificial intelligence functions
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

#include "ai.h"
#include "game.h"
#include "constants.h"
#include "pieces.h"

/* ----- [ ai_start ] ------------------------------------------------------- */
void *ai_start(void *arg)
{
    struct Var_conf *config = (struct Var_conf *) arg;
    SDL_Rect pos;
    int turning = 0;
    int i = 0,j = 0;
    int old_autopause = ENABLE_AUTOPAUSE;

    // Disable auto pause
    ENABLE_AUTOPAUSE = 0;

	// Init copy of model
    enum Color **model_tmp = malloc(sizeof(enum Color*) * PNL_HB);
    for(i = 0;i < PNL_HB;i++)
    {
		model_tmp[i] = malloc(sizeof(enum Color) * PNL_LB);
		for(j = 0;j < PNL_LB;j++)
			model_tmp[i][j] = config->model[i][j];
    }

    printf("AI launched\n");

    while((config->state == J_PLAY || config->state == J_PAUSE) 
	  && config->ai_started)
    {
        if(config->state == J_PLAY)
	{
	    ai_best_pos(config,model_tmp,&pos,&turning);
	    for(i = 0; i < turning;i++)
	    {
		SDL_Event event;
		event.type = SDL_KEYDOWN;
		event.key.keysym.sym = SDLK_UP;
		if(SDL_PushEvent(&event) != 0)
		    fprintf(stderr,
			"[ERROR] Cannot push keydown event in %s at line %d.\n",
			__FILE__,__LINE__);
		//turn(config,config->model,&(config->pc_cur_id),&(config->piece_pos),
		//HORLO,1,1);
		//SDL_Delay(INTERV_NEW/5);
		SDL_Delay(50);
	    }
	    ai_go(config,pos);
	}
	//SDL_Delay(INTERV_NEW/5);
	SDL_Delay(100);
    }

	// Free copy of model
	for(i = 0;i < PNL_HB;i++)
		free(model_tmp[i]);
	free(model_tmp);

    // Enable auto pause
    ENABLE_AUTOPAUSE = old_autopause;
}

/* ----- [ ai_go ] ---------------------------------------------------------- */
void ai_go(struct Var_conf *config,SDL_Rect pos)
{
    enum Piece_bloc pc = config->pc_cur_id;
    while(pos.x != config->piece_pos.x && config->pc_cur_id == pc)
    {
	SDL_Event event;
	event.type = SDL_KEYDOWN;
	enum Direction dir = (pos.x > config->piece_pos.x) ? RIGHT : LEFT;
	SDLKey sym = (dir == RIGHT) ? SDLK_RIGHT : SDLK_LEFT;
	event.key.keysym.sym = sym;
	if(SDL_PushEvent(&event) != 0)
		fprintf(stderr,
			"[ERROR] Cannot push keydown event in %s at line %d.\n",
			__FILE__,__LINE__);
	//move(config,(pos.x > config->piece_pos.x) ? RIGHT : LEFT);
	//SDL_Delay(INTERV_NEW/5);
	SDL_Delay(50);
    }
    if(config->pc_cur_id == pc)
    {
	SDL_Event event;
	event.type = SDL_KEYDOWN;
	event.key.keysym.sym = SDLK_SPACE;
	if(SDL_PushEvent(&event) != 0)
	    fprintf(stderr,
		    "[ERROR] Cannot push keydown event in %s at line %d.\n",
		    __FILE__,__LINE__);

	SDL_Event event2;
	event2.type = SDL_KEYUP;
	event2.key.keysym.sym = SDLK_SPACE;
	if(SDL_PushEvent(&event2) != 0)
	    fprintf(stderr,
		    "[ERROR] Cannot push keyup event in %s at line %d.\n",
		    __FILE__,__LINE__);


	//drop(config);
    }
}

/* ----- [ ai_best_pos ] ---------------------------------------------------- */
void ai_best_pos(struct Var_conf *config,enum Color **model_tmp,
				 SDL_Rect *position, int *turning)
{
    enum Piece_bloc piece_id = config->pc_cur_id;
    enum Piece_bloc piece_next_id = config->pc_next_id;
    SDL_Rect pos;
    SDL_Rect next_pos;
    int score_tmp;
    int i = 0, j = 0, k = 0, l = 0;
    int sum = 0;
    int max_score = 0;
    // Init table of scores
    int scores[4*4][((int)PNL_LB+4)*((int)PNL_LB+4)];
    for(i = 0;i < 4*4;i++)
		for(j = 0;j < (PNL_LB+4)*(PNL_LB+4);j++)
	    	scores[i][j] = 0;
    // Init position
    pos.x = 0;
    pos.y = config->piece_pos.y;

    // Checking each configuration
    //	    checking each position
    //		checking holes
    //		checking lines
    //	    checking each rotation
    //		checking holes
    //		checking lines
    for(i = 0;i < 4;i++)
    {
	for(j = 0;j < PNL_LB+4;j++)
	{
	    // Update position
	    pos.x = j-4;
	    pos.y = config->piece_pos.y;

	    score_tmp = ai_score_pos(config,model_tmp,piece_id,pos);

	    for(k = 0;k < 4;k++)
		for(l = 0;l < PNL_LB+4;l++)
		    scores[i*4+k][(int)(j*(PNL_LB+4)+l)] = score_tmp;

	    // Get dropped position
	    if(check_pc(config,model_tmp,config->pieces[piece_id],pos))
	    {
		while(check_pc(config,model_tmp,config->pieces[piece_id],pos)
		      && pos.y != PNL_HB)
		    pos.y++;
		    pos.y--;

		// Take off piece in temporary model
		takeoff(config,model_tmp,&piece_id,pos,0);

		// Remove lines
		remove_lines(config,model_tmp,0);

		// Get next piece
		piece_next_id = config->pc_next_id;

		// For all turns
		for(k = 0;k < 4;k++)
		{
		    // For all positions
		    for(l = 0;l < (PNL_LB+4);l++)
		    {
			// Get new position
			next_pos.x = l-4;
			next_pos.y = 1;

			// Calculate score for new piece position
			score_tmp = ai_score_pos(config,model_tmp,
						 piece_next_id,next_pos);
			scores[i*4+k][(int)(j*(PNL_LB+4)+l)] += score_tmp;
		    }
		    // Turn new piece
		    next_pos.x = config->piece_pos.x;
		    turn(config,model_tmp,&piece_next_id,&next_pos,HORLO,0,0);
		}

		// Copy model
		for(k = 0;k < PNL_HB;k++)
		    for(l = 0;l < PNL_LB;l++)
		    model_tmp[k][l] = config->model[k][l];
	    }
	}

	// Turn
	turn(config,model_tmp,&piece_id,&(config->piece_pos),
	     HORLO,0,0);    
    }

    // Get best position
    pos.x = 0;
    *turning = 0;
    max_score = scores[0][0];
    for(i = 0;i < 4;i++)
    {
	for(j = 0;j < PNL_LB+4;j++)
	{
	    for(k = 0;k < 4;k++)
		for(l = 0;l < (PNL_LB+4);l++)
		//printf("%d ",scores[i][j]);
		if(scores[i*4+k][(int)(j*(PNL_LB+4)+l)] > max_score)
		{
		    max_score = scores[i*4+k][(int)(j*(PNL_LB+4)+l)];
		    pos.x = j-4;
		    *turning = i;
		}
	}
	//printf("\n");
    }

    // Print scores table
    /*for(i = 0;i < 4;i++)
    {
	for(j = 0;j < PNL_LB+4;j++)
	{
	    for(k = 0;k < 4;k++)
	    {
		for(l = 0;l < PNL_LB+4;l++)
		{
		    if( 3 < j & j < 10) printf("%d ",scores[i*4+k][(int)(j*(PNL_LB+4)+l)]);
		}
		if( 3 < j & j < 10) printf("\n");
	    }
	    if( 3 < j & j < 10) printf("\n\n");
	}
	if( 3 < j & j < 10) printf("\n\n");
    }*/
    position->x = pos.x;
    //printf("i = %d j = %d \n",pos->x,*turning);
}

/* ----- [ ai_score_pos ] --------------------------------------------------- */
int ai_score_pos(struct Var_conf *config,
				 enum Color **model,
				 enum Piece_bloc piece_id,
				 SDL_Rect position)
{
    int score = 0;
    int k = 0, l = 0;
    int sum = 0, lines = 0;
    SDL_Rect pos;
    pos.x = position.x;
    pos.y = position.y;

    // Check if position is right
    if(!check_pc(config,model,config->pieces[piece_id],pos))
    {
	score -= 16*PNL_LB;
	return score;
    }
    // Get dropped position
    while(check_pc(config,model,config->pieces[piece_id],pos)
	  && pos.y != PNL_HB)
	pos.y++;
    pos.y--;
    // Check holes
    for(k = 0;k < PC_NB_LBLC;k++)
    {
	l = PC_NB_HBLC-1;
	while(l >= 0 && config->pieces[piece_id][l][k] == CL_MPT) l--;
	if(l <= -1) continue;
	else
	{
	    // Holes
	    if((pos.x+k >= 0 && pos.x+k < PNL_LB &&
		pos.y+l+1 >= 0 && pos.y+l+1 < PNL_HB)
	       && (model[pos.y+l+1][pos.x+k] == CL_MPT))
		score -= 72;
	}
    }
    // Check lines
    lines = 0;
    for(k = 0;k < PC_NB_HBLC;k++)
    {
	sum = 0;
	for(l = 0;l < PNL_LB;l++)
	    if((pos.y+k >= 0 && pos.y+k < PNL_HB) &&
		(config->model[pos.y+k][l] != CL_MPT
	     || (l-pos.x >= 0 && l-pos.x < PC_NB_LBLC 
			 && config->pieces[piece_id][k][l-pos.x] != CL_MPT)))
		sum++;
	// Lines
	if(sum >= PNL_LB) lines++;
    }
    score += lines*lines*PNL_LB;
    // Height is very bad
    score += 4*pos.y;

    return score;
}
