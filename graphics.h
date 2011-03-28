/*
 *	graphics.h
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
 *	WumpusWorld is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with WumpusWorld.  If not, see <http://www.gnu.org/licenses/>.
 */
 
#ifndef WUMPUS_GRAPHIC
#define WUMPUS_GRAPHIC

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "main.h"

#define DEPTH 32

SDL_Surface *disp, *tmp, *terrain, /* general purpose */
			*fog, *grass, *pit, /* terrain */
			*wumpus, *player, /* charachters */
			*stench, *breeze, *gold, /* misc */
         *message; /* message surface */

TTF_Font *font;

int init_graphics(void );
int load_sprites(void);
void draw(void );
void draw_terrain(void );
void place_player(void );
int notify(char * message);

#endif
