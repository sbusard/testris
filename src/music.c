/*
 * TEsTris
 *
 * Created by Simon Busard on 22.08.2007
 *
 * music.c
 * -------
 * Music managment functions
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

#include "music.h"
#include <SDL/SDL_mixer.h>
#include <string.h>
#include <stdio.h>

/* ----- [ music_init ] ----------------------------------------------------- */
void music_init(struct Var_conf *config)
{
    int audio_rate = MIX_DEFAULT_FREQUENCY;
    Uint16 audio_format = AUDIO_S16; /* 16-bit stereo */
    int audio_channels = 1;
    int audio_buffers = 4096;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers))
	fprintf(stderr,"[ERROR] Unable to open audio.\n");

    config->music = NULL;
}

/* ----- [ music_free ] ----------------------------------------------------- */
void music_free()
{
    Mix_CloseAudio();
}

/* ----- [ music_play ] ----------------------------------------------------- */
void music_play(struct Var_conf *config)
{
    char buffer[GNL_BUF_SIZE];

    sprintf(buffer,"music/testris%d.mid",(int)MUSIC_ID);

    config->music = Mix_LoadMUS(buffer);

    if(!config->music)
	printf("[ERROR] Mix_LoadMUS(%s): %s\n",buffer,Mix_GetError());
	
    Mix_PlayMusic(config->music, -1);
}

/* ----- [ music_stop ] ----------------------------------------------------- */
void music_stop(struct Var_conf *config)
{
    Mix_HaltMusic();
    Mix_FreeMusic(config->music);

}
/* ----- [ music_mute ] ----------------------------------------------------- */
void music_mute(struct Var_conf *config,enum music_mute mute)
{
    int vol = (mute == ON) ? config->music_vol : 0;
    Mix_VolumeMusic(vol);
}

/* ----- [ music_volume ] --------------------------------------------------- */
void music_volume(int new_vol)
{
    Mix_VolumeMusic(new_vol);
}


