/*
 * TEsTris
 *
 * Created by Simon Busard on 22.08.2007
 *
 * game.c
 * ------
 * Game functions
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
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include "constants.h"
#include "pieces.h"
#include "game.h"
#include "display.h"
#include "undo.h"
#include "music.h"
#include "ai.h"

/* ----- [ step ] ----------------------------------------------------------- */
Uint32 step(Uint32 interv,void *param)
{
    struct Var_conf *config = param;
    SDL_Rect pos;

    if(config->state == J_PLAY)
    {
	// No current piece
	if(config->pc_cur_id == PCMPTY)
	{
	    add(config);
	    if(config->state != J_LOST) disp_gamepanel(config);
	    return interv;
	}
	// A current piece
	else
	{
	    pos.x = config->piece_pos.x;
	    pos.y = config->piece_pos.y + 1;
			
	    // Check new position
	    if(check_pc(config,
			config->model,
			config->pieces[config->pc_cur_id],
			pos))
	    {
		config->piece_pos.y++;
		disp_gamepanel(config);
	    }
	    else
	    {
		// Take off current piece
		takeoff(config,config->model,&(config->pc_cur_id),
			config->piece_pos,1);
		disp_gamepanel(config);
		check(config);
	    }

	    return interv;
	}
    }
}

/* ----- [ move ] ----------------------------------------------------------- */
int move(struct Var_conf *config,enum Direction direction)
{
    SDL_Rect pos;
    int moved = 0;

    pos.x = (direction==LEFT)?config->piece_pos.x - 1:config->piece_pos.x + 1;
    pos.y = config->piece_pos.y;

    if(check_pc(config,
		config->model,
		config->pieces[config->pc_cur_id],
		pos))
    {
        moved = 1;
        config->piece_pos.x = pos.x;
        config->piece_pos.y = pos.y;

        // Piece ghost
        while(check_pc(config,
                   config->model,
                   config->pieces[config->pc_cur_id],
                   pos) 
              && pos.y != PNL_HB)
            pos.y++;
        config->ghost_pos.x = pos.x;
        config->ghost_pos.y = --pos.y;
    }

    disp_gamepanel(config);
    return moved;
}

/* ----- [ drop ] ----------------------------------------------------------- */
void drop(struct Var_conf *config)
{
    int timer = 1; // Fix bug of timer

    // Announce dropping
    config->dropping = 1;

    // Disable timer
    if(!config->down_pressed && !SDL_RemoveTimer(config->timer))
    {
	fprintf(stderr,
		"[ERROR] Cannot remove timer in %s at line %d.\n",
		__FILE__,__LINE__);
	timer = 0;
    }

    // While the piece is not taken off, step forward
    while(config->pc_cur_id != PCMPTY)
    	step(config->interv,config);
    
    // One more step to add a piece
    step(config->interv,config);

    // Enable timer
    if(timer)
	if(!config->down_pressed 
	   && (config->timer = SDL_AddTimer(config->interv,
					    step,config)) == NULL)
	    fprintf(stderr,
		    "[ERROR] Cannot initialize timer in %s at line %d.\n",
		    __FILE__,__LINE__);

    // End of drop
    config->dropping = 0;
}

/* ----- [ add ] ------------------------------------------------------------ */
void add(struct Var_conf *config)
{
    int timer = 1; // Fix bug of timer
    int random = 0;
    SDL_Rect pos;
    // Pieces id's
    enum Piece_bloc pieces[PC_NB] = {	SQR1,SQR1,SQR1,SQR1,
    					BAR1,BAR1,BAR2,BAR2,
					L1,L2,L3,L4,
					LINV1,LINV2,LINV3,LINV4,
					S1,S1,S2,S2,
					SINV1,SINV1,SINV2,SINV2,
					DP1,DP2,DP3,DP4 };

    // Disable timer
    config->state = J_PAUSE;
    if(!config->dropping && !config->down_pressed && !SDL_RemoveTimer(config->timer))
    {
	fprintf(stderr,
		"[ERROR] Cannot remove timer in %s at line %d.\n",
		__FILE__,__LINE__);
	timer = 0;
    }

    // Get a random piece
    random = rand() % PC_NB + 1;

    // Copy next piece in current piece
    config->pc_cur_id = config->pc_next_id;
    
    // Copy random piece in next piece
    config->pc_next_id = pieces[random - 1];

    // Check position
    pos.x = (PNL_LB / 2) - (PC_NB_LBLC / 2);
    pos.y = 1;

    // Position is good
    if(check_pc(config,config->model,config->pieces[config->pc_cur_id],pos))
    {
    	config->piece_pos.x = pos.x;
	config->piece_pos.y = pos.y;

	// Piece ghost
	pos.x = config->piece_pos.x;
	pos.y = config->piece_pos.y;
	while(check_pc(config,
		       config->model,
		       config->pieces[config->pc_cur_id],
		       pos)
	      && pos.y != PNL_HB)
	    pos.y++;
    pos.y--;
    config->ghost_pos.x = config->piece_pos.x;
	config->ghost_pos.y = pos.y;
	
	// Display next piece
	disp_next_pc(config);

	// Enable timer
	config->state = J_PLAY;
	if(timer)
	    if(!config->dropping && !config->down_pressed 
	       && (config->timer = SDL_AddTimer(config->interv,
						step,config)) == NULL)
		fprintf(stderr,
			"[ERROR] Cannot initialize timer in %s at line %d.\n",
			__FILE__,__LINE__);

	return;
    }
    // Game Over
    else
    {
    	config->pc_cur_id = PCMPTY;
	lost(config);
	return;
    }
}

/* ----- [ check ] ---------------------------------------------------------- */
void check(struct Var_conf *config)
{
    int sum = 0;
    int timer = 1; // Fix bug of timer

    // Disable timer
    config->state = J_PAUSE;
    if(!config->dropping && !SDL_RemoveTimer(config->timer))
    {
	fprintf(stderr,
		"[ERROR] Cannot remove timer in %s at line %d.\n",
		__FILE__,__LINE__);
	timer = 0;
    }
    
    sum = remove_lines(config, config->model, 1);
    
    disp_gamepanel(config);

    // Update score, lines and level
    config->lines += sum;
    config->level = config->lines / LN_BY_LVL;
    config->score += SC_COEF * sum * sum * (config->level + 1);
    config->interv = INTERV_NEW;
    disp_scores(config);
    
    // Enable timer
    config->state = J_PLAY;
    if(timer)
    {
	if( !config->dropping 
	    && (config->timer = SDL_AddTimer(config->interv,step,config))
		== NULL)
	    fprintf(stderr,
	    "[ERROR] Cannot initialize timer in %s at line %d.\n",
	    __FILE__,__LINE__);
    }
}

/* ----- [ remove_lines ] --------------------------------------------------- */
int remove_lines(struct Var_conf *config,enum Color **model, int blink)
{
    int *lines = malloc(sizeof(int) * PNL_HB);
    int i = 0, j = 0, k = 0, sum = 0;

    for(i = 0;i < PNL_HB;i++)
	lines[i] = 0;

    // Check full lines
    for(i = 0;i < PNL_HB;i++)
    {
	sum = 0;
	for(j = 0;j < PNL_LB;j++)
	    if(model[i][j] != CL_MPT) sum++;
	if(sum == PNL_LB) lines[i] = 1;
    }

    // Count lines to remove
    sum = 0;
    for(i = 0;i < PNL_HB;i++) if(lines[i]) sum++;

    if(blink)
    {
	// Blink lines
	for(k = 0;k < LN_NBCLIC * 2;k++)
	{
	    for(i = 0;i < PNL_HB;i++)
	    {
		for(j = 0;j < PNL_LB;j++)
		{
		    if(lines[i])
			model[i][j] = (model[i][j] != CL_MPT) ?
						    CL_MPT : CL_GREY1;
		}
		
		SDL_Delay(LN_DELAY);
	    }
	    disp_gamepanel(config);
	}
    }

    // Delete lines
    for(i = 0;i < PNL_HB;i++)
    {
        if(lines[i])
        {
	    for(j = 0;j < PNL_LB;j++)
	    {
		for(k = i;k > 0;k--)
		{
		    model[k][j] = model[k - 1][j];
		}
		model[0][j] = CL_MPT;
	    }
	}
    }
    free(lines);
    return sum;
}

/* ----- [ turn ] ----------------------------------------------------------- */
void turn(struct Var_conf *config,
	  enum Color **model,
	  enum Piece_bloc *piece_id,
	  SDL_Rect *position,
	  enum Rotation rotation,
	  int ghost,
	  int disp)
{
    int assocs[PC_ASS_SIZE][6] = PC_ASSOC;
    int rot = (rotation == HORLO) ? 1 : -1;
    int pc = assocs[*piece_id][1 + rot];
    SDL_Rect pos;

    pos.x = position->x;
    pos.y = position->y;

    if(check_pc(config,model,config->pieces[pc],*position))
	*piece_id = pc;
    else
    {
	if(pos.x <= 0)
	    pos.x++;
	else if(pos.x >= PNL_LB - PC_NB_LBLC)
	    pos.x--;
	if(check_pc(config,model,config->pieces[pc],pos))
	{
	    position->x = pos.x;
	    position->y = pos.y;
	    *piece_id = pc;
	}
    }

    // Piece ghost
    if(ghost)
    {
	pos.x = config->piece_pos.x;
	pos.y = config->piece_pos.y;
	while(check_pc(config,
		       config->model,
		       config->pieces[config->pc_cur_id],
		       pos)
	      && pos.y != PNL_HB)
	    pos.y++;
	pos.y--;
	config->ghost_pos.x = config->piece_pos.x;
	config->ghost_pos.y = pos.y;
    }

    if(disp) disp_gamepanel(config);
}

/* ----- [ undo ] ----------------------------------------------------------- */
void undo(struct Var_conf *config)
{
    int i = 0, j = 0;
    SDL_Rect pos;
    int timer;

    if(config->undo->counter > 0)
    {
	 // Disable timer
	config->state = J_PAUSE;
	if(!config->dropping && !config->down_pressed && !SDL_RemoveTimer(config->timer))
	{
	    fprintf(stderr,
		    "[ERROR] Cannot remove timer in %s at line %d.\n",
		    __FILE__,__LINE__);
	    timer = 0;
	}

	// Load
	undo_load(config,config->undo);

	// Piece ghost
	pos.x = config->piece_pos.x;
	pos.y = config->piece_pos.y;
	while(check_pc(config,
		       config->model,
		       config->pieces[config->pc_cur_id],
		       pos)
	      && pos.y != PNL_HB)
	    pos.y++;
        pos.y--;
    	config->ghost_pos.x = config->piece_pos.x;
	config->ghost_pos.y = pos.y;


	// Display panel
	disp_gamepanel(config);
	disp_next_pc(config);
	disp_scores(config);

	// Enable timer
	config->state = J_PLAY;
	if(timer)
	    if(!config->dropping && !config->down_pressed 
	       && (config->timer = SDL_AddTimer(config->interv,
						step,config)) == NULL)
		fprintf(stderr,
			"[ERROR] Cannot initialize timer in %s at line %d.\n",
			__FILE__,__LINE__);

    }
}

/* ----- [ lost ] ----------------------------------------------------------- */
void lost(struct Var_conf *config)
{
    config->state = J_LOST;
    high_save(config->lines,config->score);
    disp_scores(config);
    disp_gameover(config);
}

/* ----- [ check_pc ] ------------------------------------------------------- */
int check_pc(struct Var_conf *config,
	     enum Color **model,
	     enum Color **piece,
	     SDL_Rect pos)
{
    int i = 0,j = 0;
    // Getting high left corner position
    int x = pos.x;
    int y = pos.y;
    // Check
    for(i = 0;i < PC_NB_HBLC;i++)
    {
    	for(j = 0;j < PC_NB_LBLC;j++)
    	{
	    // if the current bloc is not empty and
	    // not on the panel, then the position is not good
	    if(piece[i][j] != CL_MPT		&&
	       (x + j < 0 || x + j >= PNL_LB	||
	        y + i < 0 || y + i >= PNL_HB)	 )
		return 0;
	    // if the current bloc is not empty
	    // the bloc is on the panel
	    // and the bloc of the model is not empty,
	    // then it is no valable position
	    if(piece[i][j] != CL_MPT	 	&& 
	       x + j >= 0			&&
	       x + j < PNL_LB 			&&
	       y + i >= 0			&&
	       y + i < PNL_HB 			&&
	       model[y + i][x + j] != CL_MPT	 )
		return 0;
	}
    }
    return 1;
}

/* ----- [ takeoff ] -------------------------------------------------------- */
void takeoff(struct Var_conf *config,
	     enum Color **model,
	     enum Piece_bloc *pc_id,
	     SDL_Rect position,
	     int empty)
{
    int i = 0,j = 0;
    SDL_Rect pos;

    // Update undo informations
    if(empty)undo_save(config,config->undo);

    for(i = 0;i < PC_NB_HBLC;i++)
	for(j = 0;j < PC_NB_LBLC;j++)
	    if(config->pieces[*pc_id][i][j] != CL_MPT)
	    {
	    	pos.x = position.x;
		pos.y = position.y;
		model[pos.y + i][pos.x + j] =
		    config->pieces[*pc_id][i][j] + 1;
	    }

    // Empty current piece
    if(empty) *pc_id = PCMPTY;
}

/* ----- [ pc_init ] -------------------------------------------------------- */
void pc_init(struct Var_conf *config)
{
    void copy_pc_tmp(enum Color **tab1,
		     enum Color tab2[PC_NB_HBLC][PC_NB_LBLC])
    {
    	int i = 0,j = 0;
	for(i = 0;i < PC_NB_HBLC;i++)
	    for(j = 0;j < PC_NB_LBLC;j++)
		tab1[i][j] = tab2[i][j];
    }

    // Pieces codes
    enum Color pieces_blc[PC_REAL_NB][PC_NB_HBLC][PC_NB_LBLC] = 
	{	PC_EMPTY,PC_SQR1,PC_BAR1,PC_BAR2,
		PC_L1,PC_L2,PC_L3,PC_L4,
		PC_LINV1,PC_LINV2,PC_LINV3,PC_LINV4,
		PC_S1,PC_S2,PC_SINV1,PC_SINV2,
		PC_DP1,PC_DP2,PC_DP3,PC_DP4 };

    int i = 0,j = 0;

    // Allocating memory for pieces
    config->pieces = malloc(sizeof(enum Color **) * (PC_REAL_NB));
    for(i = 0;i < PC_REAL_NB;i++)
    {
	config->pieces[i] = malloc(sizeof(enum Color *) * (PC_NB_HBLC));
	for(j = 0;j < PC_NB_HBLC;j++)
	{
	    config->pieces[i][j] = malloc(sizeof(enum Color) * (PC_NB_LBLC));
	}
    }
	
    // Copying pieces
    for(i = 0;i < PC_REAL_NB;i++)
	copy_pc_tmp(config->pieces[i],pieces_blc[i]);
}

/* ----- [ pc_free ] -------------------------------------------------------- */
void pc_free(struct Var_conf *config)
{
    int i = 0,j = 0;
    // Desallocating memory for pieces
    for(i = 0;i < PC_REAL_NB;i++)
    {
	for(j = 0;j < PC_NB_HBLC;j++)
	    free(config->pieces[i][j]);
	free(config->pieces[i]);
    }	
    free(config->pieces);
}

