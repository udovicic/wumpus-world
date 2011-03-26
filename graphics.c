/*
 *	graphics.c
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
#include <SDL/SDL_image.h>
#include <stdio.h>
#include "graphics.h"
#include "main.h"

/* init SDL graphics */
int init_graphics() {
   
   SDL_Rect rect;
	int i,j;
   
   /* init SDL */
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		perror("Faile to init SDL");
		SDL_Quit();
		return 1;
	}
	
   /* init display */
	if ((disp = SDL_SetVideoMode(world_x*95, world_y*68, DEPTH, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
		perror("Can't open display");
		SDL_Quit();
		return 1;
	}
	terrain = SDL_CreateRGBSurface(SDL_HWSURFACE, world_x*95, world_y*68, DEPTH, 0, 0, 0, 0);
   
	/* load sprites */
	if (load_sprites()!=0) {
		SDL_Quit();
		return 1;
	}
   
   /* draw terrain */
   rect.w = 95;
	rect.h = 68;
	for (i=0;i<world_x;i++) {
		for (j=0;j<world_y;j++) {
			rect.x=95*i;
			rect.y=68*j;
			SDL_BlitSurface(grass,NULL,terrain,&rect);
		}
	}
   i=0;j=0;
	for (i=0;i<world_x;i++) for (j=0;j<world_y;j++) {
		switch(world[i][j]) {
			case 'G': tmp=gold;
				rect.w=30;rect.h=34;
				rect.x=95*i;
				rect.y=68*j;
				break;
			case 'p': tmp=pit;
				rect.w=95;rect.h=68;
				rect.x=95*i;
				rect.y=68*j;
				break;
			case 'w': tmp=wumpus;
				rect.w=43;
				rect.h=50;
				rect.x=95*i;
				rect.y=68*j+18;
				break;
		}
		SDL_BlitSurface(tmp,NULL,terrain,&rect);
	}
   return 0;
}

/* load sprites */
int load_sprites(void) {
	fog = IMG_Load("resources/fog.png");
	if (fog == NULL) {
		perror("Unable to open fog sprite");
		return 1;
	}
	
	grass = IMG_Load("resources/grass.png");
	if (grass == NULL) {
		perror("Unable to open grass sprite");
		return 1;
	}
	
	pit = IMG_Load("resources/pit.png");
	if (pit == NULL) {
		perror("Unable to open pit sprite");
		return 1;
	}
	
	wumpus = IMG_Load("resources/wumpus.png");
	if (wumpus == NULL) {
		perror("Unable to open wumpus sprite");
		return 1;
	}
	
	player = IMG_Load("resources/player.png");
	if (player == NULL) {
		perror("Unable to open player sprite");
		return 1;
	}
	
	stench = IMG_Load("resources/stench.png");
	if (stench == NULL) {
		perror("Unable to open stench sprite");
		return 1;
	}
	breeze = IMG_Load("resources/breeze.png");
	if (breeze == NULL) {
		perror("Unable to open breeze sprite");
		return 1;
	}
	gold = IMG_Load("resources/gold.png");
	if (gold == NULL) {
		perror("Unable to open gold sprite");
		return 1;
	}
	return 0;
}

 /*draw artefacts on disp */
void draw_terrain(void ) {
   SDL_Rect rect;
   
   int i,j;
   for (i=0;i<world_x;i++) {
      for (j=0;j<world_y;j++) {
         if ( gmap[i][j][0] ) { /* fog */
            tmp=fog;
         } else { /* place other stuff */
            if ( gmap[i][j][1] ) { /* stench */
               
            }
            if ( gmap[i][j][2] ) { /* breeze */
            
            }
            if ( gmap[i][j][3] ) { /* gold */
            
            }
            if ( gmap[i][j][4] ) { /* player */
            
            }
            
         }
         SDL_BlitSurface(tmp,NULL,disp,&rect);
      }
   }
}
   
/* draw frame */
void draw(void ) {
   /* TODO
    *   draw_terrain();
    *   place_player();
    */
   SDL_BlitSurface(terrain,NULL,disp,NULL);
   SDL_Flip(disp);
}
