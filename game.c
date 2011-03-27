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
 #include "main.h"
 #include "graphics.h"

void game_input(void ) {
   switch (event.type) {
      case SDL_QUIT:
         continue_game = 0;
         break;
      case SDL_KEYDOWN:
         switch (event.key.keysym.sym) {
            case SDLK_UP: move(0); break;
            case SDLK_RIGHT: move(1); break;
            case SDLK_DOWN: move(2); break;
            case SDLK_LEFT: move(3); break;
            case SDLK_ESCAPE: st.grim_reaper = 1; continue_game = 0; break;
            default: /* sit and bequite */ break;
         }
      }
}

void game_logic(void ) {
   get_status();
   if (st.stench) gmap[player_x][player_y][1]=1;
   if (st.breeze) gmap[player_x][player_y][2]=1;
   if (st.glitter) continue_game=0;
   if (st.grim_reaper) continue_game=0;         
}

void init_game(void ) {
   int i,j,k;
   
   for (i=0;i<world_x;i++) {
      for (j=0;j<world_y;j++) {
         for (k=0;k<3;k++) gmap[i][j][k]=0;
      }
   }
   st.breeze=0;
   st.stench=0;
   st.glitter=0;
   st.grim_reaper=0;

   player_x=0;player_y=world_y-1;
   gmap[player_x][player_y][0]=1;
   
   SDL_EnableKeyRepeat(0,SDL_DEFAULT_REPEAT_INTERVAL);
   continue_game = 1;
}

int game_alive(void ) {
   return continue_game;
}

int move(int d) {
   int dir[2][4] = {{0,1,0,-1},{-1,0,1,0}};
   
   /* bump!! */
   if ( (player_x + dir[0][d]) == world_x || (player_x + dir[0][d]) < 0) return -1;
   if ( (player_y + dir[1][d]) == world_y || (player_y + dir[1][d]) < 0) return -1;
   
   player_x += dir[0][d];
   player_y += dir[1][d];
   gmap[player_x][player_y][0]=1;
   return 0;
}

void get_status(void ) {
   int dir[2][4] = {{0,1,0,-1},{-1,0,1,0}};
   int i;
   
   if (world[player_x][player_y]=='w' || world[player_x][player_y]=='p') st.grim_reaper=1;
   if (world[player_x][player_y]=='G') st.glitter=1;
   st.breeze=0;
   st.stench=0;
   for (i=0;i<4;i++)
      switch(world[ player_x+dir[0][i] ][ player_y + dir[1][i] ] ) {
         case 'p': st.breeze =1; break;
         case 'w': st.stench =1; break;
      }
   
}
int game_block(void ) { 
   SDL_Event block;
   SDL_PollEvent(&block);
   if (block.type == SDL_QUIT ) return 0;
   if (block.key.keysym.sym == SDLK_ESCAPE ) return 0;
   return 1;   
}
