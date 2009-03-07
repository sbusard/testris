/*
 * TEsTris
 *
 * Created by Simon Busard on 22.08.2007
 *
 * config.c
 * --------
 * Game configuration functions
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

#include "config.h"
#include "constants.h"

void conf_load(struct Var_conf *config)
{
    FILE *fd = NULL;
    char* conf_table_names[CONF_TBL_L] = CONF_TBL_NAMES;
    double* conf_table_values[CONF_TBL_L] = CONF_TBL_VALUES;
    double conf_table_default[CONF_TBL_L] = CONF_TBL_DEFAULT;
    int i = 0;
    char buffer[GNL_BUF_SIZE];

    // Managing file lines variables
    char *strPtr = NULL; // Temp pointer
    char *setting = NULL;
    char *numchar = NULL;
    double number = 0;

    // Init default values
    for(i = 0;i < CONF_TBL_L;i++)
	*(conf_table_values[i]) = conf_table_default[i];

    // Open file
    if((fd = fopen("TEsTris.conf","r")) == NULL)
    {
	fprintf(stderr,
		"Cannot open file TEsTris.conf. Default configuration loaded.\n"
		);
	return;
    }

    // Read line by line and update corresponding variables
    while(fgets(buffer,GNL_BUF_SIZE,fd) != NULL)
    {
	// Ignore comments
	if(buffer[0] == '#' || buffer[0] == '\n')
	    continue;

	// Get setting and value
	strPtr = buffer;
	setting = strtok(strPtr, "=");
	numchar = strtok(NULL, "=");
	number = strtod(numchar,NULL);

	// Compare to registered settings
	for(i = 0;i < CONF_TBL_L;i++)
	    if(!strncasecmp(setting,conf_table_names[i],
			    strlen(conf_table_names[i])))
		*(conf_table_values[i]) = number;
    }

    // Close file
    close(fd);
}

