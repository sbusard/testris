/*
 * TEsTris
 *
 * Created by Simon Busard on 22.08.2007
 *
 * music.h
 * -------
 * Prototypes - Music managment functions
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

#ifndef MUSIC
#define MUSIC

#include "constants.h"

enum music_mute
{
    ON, OFF
};

/*
 * Initialize music library
 */
void music_init(struct Var_conf *config);

/*
 * Close music library
 */
void music_free();

/*
 * Play music
 */
void music_play(struct Var_conf *config);

/*
 * Stop music
 */
void music_stop(struct Var_conf *config);

/*
 * Mute music
 */
void music_mute(struct Var_conf *config,enum music_mute mute);

/*
 * Change music volume
 */
void music_volume(int new_vol);

#endif
