/*
 * TEsTris
 *
 * Created by Simon Busard on 22.08.2007
 *
 * highscores.h
 * ------------
 * Prototype - High scores saving
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

#ifndef HIGHSCORES
#define HIGHSCORES

/*
 * Save scores in file "TEsTris.scores"
 */
void high_save(int lines, int scores);

/*
 * Return a pointer to a table of NB_HGSCRS
 * containing NB_HGSCRS best scores.
 * Scores are stocked in TEsTris.scores
 */
char** high_load();

#endif

