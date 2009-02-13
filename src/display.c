/*
 * TEsTris
 *
 * Created by Simon Busard on 21.02.2008
 *
 * display.c
 * ---------
 * Display functions
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

#include "display.h"
#include "constants.h"
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

// Color RGB codes
int colors[NB_COLORS][4] = COLORS;
// Pieces assocs
int pc_assoc[PC_ASS_SIZE][6] = PC_ASSOC;
// Blocs
SDL_Surface* blocs[PC_REAL_NB];

/* ----- [ disp_init ] ------------------------------------------------------ */
void disp_init(struct Var_conf *config)
{
    // Init libraries
    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER|SDL_INIT_AUDIO) == -1)
    {
	fprintf(stderr,
		"[ERROR] Cannot initialize SDL library : %s\n",SDL_GetError());
	exit(EXIT_FAILURE);
    }

    // Create the window
    if((config->screen = SDL_SetVideoMode(WIN_L,WIN_H,32,
				      SDL_HWSURFACE|SDL_DOUBLEBUF)) == NULL)
    fprintf(stderr,"[ERROR] Cannot create the screen.\n");

    // Title of the window
    SDL_WM_SetCaption("TEsTris",NULL);

    // Init blocs
    disp_bloc_init(config);
}

/* ----- [ disp_window ] ---------------------------------------------------- */
void disp_window(struct Var_conf *config)
{
    // Create game panel
    SDL_FillRect(config->screen,NULL,
		 SDL_MapRGB(config->screen->format,200,200,200));
    config->panel = SDL_CreateRGBSurface(SDL_HWSURFACE,PNL_L,PNL_H,32,0,0,0,0);
    SDL_FillRect(config->panel,NULL,SDL_MapRGB(config->screen->format,0,0,0));
    // Game panel position
    config->pnl_pos.x = WIN_PNL_SP;
    config->pnl_pos.y = config->pnl_pos.x;
    // Display game panel
    SDL_BlitSurface(config->panel,NULL,config->screen,&(config->pnl_pos));
    SDL_Flip(config->screen);
}

/* ----- [ disp_gamepanel ] ------------------------------------------------- */
void disp_gamepanel(struct Var_conf *config)
{
	int max(int i,int j) { return (i < j) ? j : i; }
	int min(int i,int j) { return (i < j) ? i : j; }

    SDL_Surface *ccur = NULL, *cghost = NULL;
    SDL_Rect pos;
    int i = 0,j = 0;

    // Create blocs
    ccur = SDL_CreateRGBSurface(SDL_HWSURFACE,BLC_L,BLC_H,32,0,0,0,0);
    cghost = SDL_CreateRGBSurface(SDL_HWSURFACE,BLC_L,BLC_H,32,0,0,0,0);
    // Apply colors or not
    if(SHOW_COLORS)
    {
    	SDL_FillRect(ccur,NULL,SDL_MapRGB(config->screen->format,
    		     colors[pc_assoc[config->pc_cur_id][3]][1],
		     colors[pc_assoc[config->pc_cur_id][3]][2],
		     colors[pc_assoc[config->pc_cur_id][3]][3]));
	SDL_FillRect(cghost,NULL,SDL_MapRGB(config->screen->format,
		     colors[pc_assoc[config->pc_cur_id][5]][1],
		     colors[pc_assoc[config->pc_cur_id][5]][2],
		     colors[pc_assoc[config->pc_cur_id][5]][3]));
    }
    else
    {
	SDL_FillRect(ccur,NULL,SDL_MapRGB(config->screen->format,255,255,255));
    	SDL_FillRect(cghost,NULL,SDL_MapRGB(config->screen->format,25,25,25));
    }
    // Create background
    SDL_FillRect(config->panel,NULL,SDL_MapRGB(config->screen->format,0,0,0));

	// Dynamic height panel management
	int offset = max(0,config->piece_pos.y - (PNL_HB/2 - PC_NB_HBLC/2));
	offset = (offset + PNL_HB > model_height(config->model)) ? model_height(config->model) - PNL_HB : offset; 

    // Display model
    for(i = 0;i < PNL_HB;i++)
    	for(j = 0;j < PNL_LB;j++)
	    if(model_get(config->model,i + offset,j) != CL_MPT)
	    {
		pos.x = j * (BLC_L + BLC_SP) + BLC_SP;
		pos.y = i * (BLC_H + BLC_SP) + BLC_SP;
		SDL_BlitSurface(blocs[model_get(config->model,i + offset,j)],
		NULL,config->panel,&pos);
	    }
    // Display piece ghost
    if(SHOW_GHOST && config->ghost_pos.y != config->piece_pos.y)
    {
	for(i = 0;i < PC_NB_HBLC;i++)
	    for(j = 0;j < PC_NB_LBLC;j++)
		if(config->pieces[config->pc_cur_id][i][j] != CL_MPT)
		{
		    pos.x = config->ghost_pos.x * (BLC_L + BLC_SP); 
		    pos.x += j * (BLC_L + BLC_SP) + BLC_SP;
		    pos.y = (config->ghost_pos.y - offset) * (BLC_L + BLC_SP);
		    pos.y += i * (BLC_H + BLC_SP) + BLC_SP; 
		    SDL_BlitSurface(cghost,NULL,config->panel,&pos);
		}

    }

    // Display current piece
    for(i = 0;i < PC_NB_HBLC;i++)
    	for(j = 0;j < PC_NB_LBLC;j++)
	    if(config->pieces[config->pc_cur_id][i][j] != CL_MPT)
	    {
		pos.x = config->piece_pos.x * (BLC_L + BLC_SP); 
		pos.x += j * (BLC_L + BLC_SP) + BLC_SP;
		pos.y = (config->piece_pos.y - offset) * (BLC_L + BLC_SP);
		pos.y += i * (BLC_H + BLC_SP) + BLC_SP; 
		SDL_BlitSurface(ccur,NULL,config->panel,&pos);
	    }

    // Display panel
    SDL_BlitSurface(config->panel,NULL,config->screen,&(config->pnl_pos));
    SDL_Flip(config->screen);

    // Free memory
    SDL_FreeSurface(ccur);
    SDL_FreeSurface(cghost);
}

/* ----- [ disp_next_pc ] --------------------------------------------------- */
void disp_next_pc(struct Var_conf *config)
{
    SDL_Surface *ccur = NULL;
    SDL_Surface *bg = NULL;
    SDL_Rect pos;
    SDL_Rect bg_pos;
    int i = 0,j = 0;

    if(SHOW_NEXT_PC)
    {
	// Create blocs
	ccur = SDL_CreateRGBSurface(SDL_HWSURFACE,BLC_L,BLC_H,32,0,0,0,0);
	// Apply colors or not
	if(SHOW_COLORS)
	    SDL_FillRect(ccur,NULL,SDL_MapRGB(config->screen->format,
			     colors[pc_assoc[config->pc_next_id][3]][1],
			     colors[pc_assoc[config->pc_next_id][3]][2],
			     colors[pc_assoc[config->pc_next_id][3]][3]));
    	else
	    SDL_FillRect(ccur,NULL,
			 SDL_MapRGB(config->screen->format,255,255,255));
	// Create background
	bg = SDL_CreateRGBSurface(SDL_HWSURFACE,
				  (PC_NB_LBLC + 2) * (BLC_L + BLC_SP) - BLC_SP,
				  (PC_NB_HBLC + 2) * (BLC_H + BLC_SP) - BLC_SP,
				  32,0,0,0,0);
	SDL_FillRect(bg,NULL,SDL_MapRGB(config->screen->format,0,0,0));

	// Display next piece
	for(i = 0;i < PC_NB_HBLC;i++)
	    for(j = 0;j < PC_NB_LBLC;j++)
		if(config->pieces[config->pc_next_id][i][j] != CL_MPT)
		{
		    pos.x = j * (BLC_L + BLC_SP) + BLC_SP;
		    pos.y = i * (BLC_H + BLC_SP) + BLC_SP; 
		    pos.x += BLC_L;
		    pos.y += BLC_H;
		    SDL_BlitSurface(ccur,NULL,bg,&pos);
		}

	// Display background
	bg_pos.x = BG_POS_X;
	bg_pos.y = BG_POS_Y;
	SDL_BlitSurface(bg,NULL,config->screen,&bg_pos);
	SDL_Flip(config->screen);
	
	SDL_FreeSurface(ccur);
	SDL_FreeSurface(bg);
    }	
}

/* ----- [ disp_pause ] ----------------------------------------------------- */
void disp_pause(struct Var_conf *config,int pause)
{
    SDL_Rect pos, bg_pos;
    SDL_Surface *word, *bg;
    SDL_Color color = {50,50,50};

    if(pause)
    {
    	// Get surfaces
    	word = disp_text("PAUSE",color,PGO_SIZE);
	bg = SDL_CreateRGBSurface(SDL_HWSURFACE,PNL_L,word->h,32,0,0,0,0);
	SDL_FillRect(bg,NULL,SDL_MapRGB(config->screen->format,200,200,200));

	// Get good position
	pos.x = config->panel->w/2 - word->w/2;
	pos.y = config->panel->h/2 - word->h/2;
	bg_pos.x = 0;
	bg_pos.y = pos.y;

	// Display text
	SDL_BlitSurface(bg,NULL,config->panel,&bg_pos);
	SDL_BlitSurface(word,NULL,config->panel,&pos);
	SDL_BlitSurface(config->panel,NULL,config->screen,&(config->pnl_pos));
	SDL_Flip(config->screen);

	SDL_FreeSurface(bg);
	SDL_FreeSurface(word);
    }
    else
    	disp_gamepanel(config);
}

/* ----- [ disp_gameover ] -------------------------------------------------- */
void disp_gameover(struct Var_conf *config)
{
    SDL_Rect pos,bg_pos;
    SDL_Surface *word, *bg;
    SDL_Color color = {50,50,50};

    // Get surface where text is written
    word = disp_text("GAME OVER",color,PGO_SIZE);
    bg = SDL_CreateRGBSurface(SDL_HWSURFACE,PNL_L,word->h,32,0,0,0,0);
    SDL_FillRect(bg,NULL,SDL_MapRGB(config->screen->format,200,200,200));


    // Get good position
    pos.x = config->panel->w/2 - word->w/2;
    pos.y = config->panel->h/2 - word->h/2;	
    bg_pos.x = 0;
    bg_pos.y = pos.y;

    // Display text
    SDL_BlitSurface(bg,NULL,config->panel,&bg_pos);
    SDL_BlitSurface(word,NULL,config->panel,&pos);
    SDL_BlitSurface(config->panel,NULL,config->screen,&(config->pnl_pos));
    SDL_Flip(config->screen);

    SDL_FreeSurface(bg);
    SDL_FreeSurface(word);
}

/* ----- [ disp_scores ] ---------------------------------------------------- */
void disp_scores(struct Var_conf *config)
{
    int max(int i,int j)
    {
    	if(i > j) return i;
	else return j;
    }

    SDL_Rect pos;
    SDL_Surface *scores;
    SDL_Surface *score, *lines, *level;
    SDL_Color color = {0,0,0};
    char scr_buf[SCR_BUF_SIZE];
    
    // Get surfaces
    sprintf(scr_buf,"Score : %d",config->score);
    score = disp_text(scr_buf,color,SCR_SIZE);
    sprintf(scr_buf,"Lines : %d",config->lines);
    lines = disp_text(scr_buf,color,SCR_SIZE);
    sprintf(scr_buf,"Level : %d",config->level);
    level = disp_text(scr_buf,color,SCR_SIZE);
    
    // Get great surface
    scores = SDL_CreateRGBSurface(SDL_HWSURFACE,
				  3*max(score->w,max(lines->w,level->w)),
				  score->h + lines->h + level->h,
				  32,0,0,0,0);
    SDL_FillRect(scores,NULL,SDL_MapRGB(config->screen->format,200,200,200));

    // Blit on great surface
    pos.x = 0;
    pos.y = 0;	
    SDL_BlitSurface(score,NULL,scores,&pos);
    pos.y = score->h;
    SDL_BlitSurface(lines,NULL,scores,&pos);
    pos.y += level->h;
    SDL_BlitSurface(level,NULL,scores,&pos);

    // Get position
    pos.x = SCR_POS_X;
    pos.y = SCR_POS_Y - scores->h/2;

    // Display text
    SDL_BlitSurface(scores,NULL,config->screen,&pos);
    SDL_Flip(config->screen);

    SDL_FreeSurface(score);
    SDL_FreeSurface(lines);
    SDL_FreeSurface(level);
    SDL_FreeSurface(scores);
}

/* ----- [ disp_highscores ] ------------------------------------------------ */
void disp_highscores(struct Var_conf *config)
{
    // TODO
}

/* ----- [ disp_text ] ------------------------------------------------------ */
SDL_Surface* disp_text(char *text,SDL_Color color,int size)
{
    TTF_Font *font = NULL;
    SDL_Surface *word;
    
    // Open font
    if((font = TTF_OpenFont(FONT,size)) == NULL)
    	fprintf(stderr,"[ERROR] Cannot open font.\n");
    TTF_SetFontStyle(font,TTF_STYLE_BOLD);

    // Get surface where text is written
    word = TTF_RenderText_Blended(font,text,color);

    // Close font
    TTF_CloseFont(font);

    return word;
}

/* ----- [ disp_bloc_init ] ------------------------------------------------- */
void disp_bloc_init(struct Var_conf *config)
{
    int i = 1;
    for(i = 1;i < NB_COLORS;i++)
    {
	blocs[i] = SDL_CreateRGBSurface(SDL_HWSURFACE,BLC_L,BLC_H,32,0,0,0,0);
	// Apply colors or not
	if(SHOW_COLORS)
	    SDL_FillRect(blocs[i],NULL,SDL_MapRGB(config->screen->format,
			     colors[i][1],
			     colors[i][2],
			     colors[i][3]));
	else
	    SDL_FillRect(blocs[i],NULL,
			 SDL_MapRGB(config->screen->format,255,0,0));
    }
}

/* ----- [ disp_bloc_free ] ------------------------------------------------- */
void disp_bloc_free()
{
    int i = 1;
    for(i = 1;i < NB_COLORS;i++)
    	SDL_FreeSurface(blocs[i]);
}

