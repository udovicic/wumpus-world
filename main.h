/*
 *	main.h
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

#ifndef WUMPUS_MAIN
#define WUMPUS_MAIN

#define x_min 3 /* min and max x map size */
#define x_max 10
#define y_min 3 /* min and max y map size */
#define y_max 10
#define nw 0.1 /* max wumpus and pit ratio */
#define np 0.5

char world[x_max][y_max];
int gmap[x_max][y_max][3];
int world_x, world_y;
int player_x, player_y;

#endif
