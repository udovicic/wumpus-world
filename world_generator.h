/*
 *	world_generator.h
 * 
 *	Copyright 2011 Stjepan Udovičić <udovicic.stjepan@gmail.com>
 *	      
 *	This file is part of WumpusWorld.
 *
 *	WumpusWorld is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	Foobar is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with WumpusWorld.  If not, see <http://www.gnu.org/licenses/>.
 */	  

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define x_min 3 /* min and max x map size */
#define x_max 20
#define y_min 3 /* min and max y map size */
#define y_max 20
#define nw 0.1 /* max wumpus and pit ratio */
#define np 0.5

/* stack used for map validation */
int  *tos, *p1, stack[x_max*y_max*2];
void push(int i);
int pop(void);
void clear_stack(void);

/* used for map generation and validation */
void randomize(int *x, int *y, int *solvable, int *npit, int *nwumpus);
void validate(int *x, int*y, int *nwumpus, int *npit);
int map_valid(int solvable, char world[x_max][y_max], int x, int y);

/* main function for map generation */
void generate_map(char world[x_max][y_max], int solvable, int x, int y, int nwumpus, int npit);
