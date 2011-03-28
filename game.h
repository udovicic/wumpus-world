/*
 *	game.h
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
 
#ifndef WUMPUS_GAME
#define WUMPUS_GAME

#include <SDL/SDL.h>
#include "main.h"

int continue_game;
int aiw[x_max][y_max];
SDL_Event event;
typedef struct {
   int stench;
   int breeze;
   int glitter;
   int grim_reaper;
} status;
status st;
   
void game_init(void );
int game_alive(void );
void game_input(void );
void game_logic(void );
int move(int dir );
void get_status(void );
int game_block(void );

#endif
