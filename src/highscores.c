/*
 * TEsTris
 *
 * Created by Simon Busard on 22.08.2007
 *
 * highscores.c
 * ------------
 * High scores saving
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

#include <stdio.h>
#include <time.h>
#include "highscores.h"

/* ----- [ high_save ] ------------------------------------------------------ */
void high_save(int lines, int scores)
{
    FILE *fd = NULL;
    time_t tmp_time;
    struct tm *cur_time = NULL;

    // Open file
    if((fd = fopen("TEsTris.scores","a+")) == NULL)
    {
	fprintf(stderr,
		"[ERROR] Cannot open highscores file in %s at line %d.\n",
		__FILE__,__LINE__);
	return;
    }

    // Get time
    tmp_time = time(NULL);
    if((cur_time = localtime(&tmp_time)) == NULL)
    {
	fprintf(stderr,
		"[ERROR] Cannot get time of day in %s at line *d.\n",
		__FILE__,__LINE__);
	close(fd);
    	return;
    }

    fprintf(fd,"%d.%d.%d %d:%d \t%d \t%d\n",
	    cur_time->tm_mday,
	    cur_time->tm_mon + 1,
	    cur_time->tm_year + 1900,
	    cur_time->tm_hour,
	    cur_time->tm_min,
	    lines,
	    scores);

    // Close file
    fclose(fd);
}

/* ----- [ high_load ] ------------------------------------------------------ */char** high_load()
{
    // TODO

    // Count number of scores
    
    // Get scores

    // Sort scores

    // Return first NB_HGSCRS
    
    return NULL;
}

