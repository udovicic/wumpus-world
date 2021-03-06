/*
 *	main.c
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
 
#include <stdio.h>
#include "main.h"
#include "world_generator.h"
#include "game.h"
#include "graphics.h"

void go_away(void ) {
   TTF_Quit();
	SDL_Quit();
}

int main(int nargs, char *args[]) {
	
	/* map variables */
	int nwumpus = 1,
		npit = 2,
		solvable = 1,
		verbose = 0;
	
	char *oFile = "wumpus_world.txt";
	FILE * pFile;
	
	/* tmp variables */
	int a,b;
	char *program = args[0];
	
	/* licence info */
	printf("WumpusWorld is free software: you can redistribute it and/or modify"
			"it under the terms of the GNU General Public License as published by"
			"the Free Software Foundation, either version 3 of the License, or"
			"(at your option) any later version.\n"
			"Source code available at http://code.udovicic.org/wumpus-world\n\n");
			
	world_x=4;
	world_y=4;
	fogofwar=1;
	ai=0;
	
	/* read program parameters from command line */
	while ((nargs>1) && (args[1][0]=='-')) {
		switch(args[1][1]) {
			case 'r': randomize( &world_x, &world_y, &solvable, &npit, &nwumpus); break;
			case 'a': ai=1; break;
			case 'v': verbose^=1; break;
			case 'w': nwumpus=atoi(&args[1][2]); break;
			case 'p': npit=atoi(&args[1][2]); break;
			case 'x': world_x=atoi(&args[1][2]); break;
			case 'y': world_y=atoi(&args[1][2]); break;
			case 's': solvable=1; break;
			case 'f': fogofwar=0; break;
			case 'o': oFile=&args[1][2]; break;
			default:
				printf("Usage\n  %s <options>\n"
						"  -r\t\t Randomise parameters\n"
						"  -v\t\t Verbose mode\n"
						"  -s\t\t Request solvable map\n"
						"  -f\t\t No fog on map\n"
						"  -a\t\t Use AI player\n"
						"  -w<n>\t Number of monsters in world\n"
						"  -p<n>\t Number of pits\n"
						"  -x<n>\t Length of world\n"
						"  -y<n>\t Height of world\n"
						"  -o<file_name>\tSpecify output name\n",program);
				return 0;
				break;
		}
		
		nargs--;
		args++;
	}
	
	/* output map parameters s*/
	if (verbose) printf("Creating Wumpus world [%dx%d] with %d monster(s) and %d pit(s).\nMap ",world_x,world_y,nwumpus,npit);
	if (verbose) {if (solvable) printf("will be solvable."); else printf("may not be solvable.");}
	if (verbose) printf("\nOutput will be saved to %s.\n",oFile);
	
	/* generate map */
	generate_map(world, solvable, world_x, world_y, nwumpus, npit);
	
	/* output map to file */
	pFile = fopen(oFile,"w");	
	if (pFile!=NULL) {
		for (b=0;b<world_y;b++) {for (a=0;a<world_x;a++) fprintf(pFile,"%c",world[a][b]); fprintf(pFile,"\n");};
		fclose(pFile);
	} else {
		perror("Can't open file");
		verbose=1;
	}
	
	/* output map to screen if verbose */
	if (verbose) for (b=0;b<world_y;b++) {for (a=0;a<world_x;a++) printf("%c",world[a][b]); printf("\n");};
	
	/* begin game with SDL */
	if (init_graphics()) {
		go_away();
		return 1;
	}
	
	game_init();
	
   /* game loop */
	while( game_alive() ) {
      if (!ai) SDL_WaitEvent(&event);
		game_input();
		game_logic();
		draw();
	}
   
   /* information about ended game */
   if (st.glitter) {
      if (notify("You Win!")) {
         printf("You Win!\n");
      }
      continue_game=0;
   }
   if (st.grim_reaper) {
      if (notify("You die in agony!")) {
         printf("You die in agony!\n");
      }
      continue_game=0;
   }         
   
   /* wait for user to confirm quit */
   while( game_block() );
	
	go_away();
	return 0;
}


void push(int i) {
	p1++;
	*p1 = i;
}
void pushb(int i) {
	pb1++;
	*pb1 = i;
}
int pop(void) {
	if(p1 == tos)
		return -1;
	p1--;
	return *(p1+1);
}
int popb(void) {
	if(pb1 == tosb)
		return -1;
	pb1--;
	return *(pb1+1);
}
void clear_stack(void) {
	tos=stack;
	p1=stack;
	tosb=stackb;
	pb1=stackb;
	return;
}
