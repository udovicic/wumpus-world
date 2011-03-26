/*
 *	game.c
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
 
 #include <SDL/SDL.h>
 #include <stdio.h>
 #include "game.h"

void game_input(void ) {
   while ( SDL_PollEvent(&event) ) {
      switch (event.type) {
         case SDL_QUIT:
            continue_game = 0;
            break;
      }
   }
}

void game_logic(void ) {

}

void init_game(void ) {
   continue_game = 1;
}

int game_alive(void ) {
   return continue_game;
}
