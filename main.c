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
 *	Foobar is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with WumpusWorld.  If not, see <http://www.gnu.org/licenses/>.
 */	            
 
#include <stdio.h>
#include "world_generator.h"

int main(int nargs, char *args[]) {
	
	/* map variables */
	int nwumpus = 1,
		npit = 2,
		x = 4,
		y = 4,
		solvable = 0,
		verbose = 0;
	char world[x_max][y_max];
	char *oFile = "wumpus_world.txt";
	FILE * pFile;

	/* tmp variables */
	int a,b;
	char *program = args[0];
	
	/* read program parameters from command line */
	while ((nargs>1) && (args[1][0]=='-')) {
		switch(args[1][1]) {
			case 'r': randomize( &x, &y, &solvable, &npit, &nwumpus); break;
			case 'v': verbose^=1; break;
			case 'w': nwumpus=atoi(&args[1][2]); break;
			case 'p': npit=atoi(&args[1][2]); break;
			case 'x': x=atoi(&args[1][2]); break;
			case 'y': y=atoi(&args[1][2]); break;
			case 's': solvable=1; break;
			case 'o': oFile=&args[1][2]; break;
			default:
				printf("Usage\n  %s <options>\n"
						"  -r\t\t Randomise parameters\n"
						"  -v\t\t Verbose mode\n"
						"  -s\t\t Request solvable map\n"
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
	if (verbose) printf("Creating Wumpus world [%dx%d] with %d monster(s) and %d pit(s).\nMap ",x,y,nwumpus,npit);
	if (verbose) {if (solvable) printf("will be solvable."); else printf("may not be solvable.");}
	if (verbose) printf("\nOutput will be saved to %s.\n",oFile);
	
	/* generate map */
	generate_map(world, solvable, x, y, nwumpus, npit);
	
	/* output map to file */
	pFile = fopen(oFile,"w");	
	if (pFile!=NULL) {
		for (a=0;a<x;a++) {for (b=0;b<y;b++) fprintf(pFile,"%c",world[a][b]); fprintf(pFile,"\n");};
		fclose(pFile);
	} else {
		perror("Can't open file");
		verbose=1;
	}
	
	/* output map to screen if verbose */
	if (verbose) for (a=0;a<x;a++) {for (b=0;b<y;b++) printf("%c",world[a][b]); printf("\n");};
	
	return 0;
}
