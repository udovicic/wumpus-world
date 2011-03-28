/*
 *	world_generator.c
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
#include <stdlib.h>
#include <time.h>    
#include "world_generator.h"


void randomize(int *x, int *y, int *solvable, int *npit, int *nwumpus) {
	/* Generates map parameters within specified range
	 * For range see #defines in world_generator.h */
	
	int map_size;
	
	srand(time(NULL));
	
	*x = x_min + rand() % (x_max - x_min);
	*y = y_min + rand() % (y_max - y_min);
	map_size = (*x)*(*y);
	
	*solvable = rand() % 2;
	
	*npit = rand() % (int)(map_size * np);
	*nwumpus = rand() % (int)(map_size * nw);
	
	return;
}

void validate(int *x, int*y, int *nwumpus, int *npit) {
	/* Checks whether given parameters are in specified range
	 * and corrects them with random numbers if needed */
		
	srand(time(NULL));
	
	/* validate x value */
	if (*x<x_min || *x>x_max) {
		*x = x_min + rand() % (x_max - x_min);
		fprintf(stderr,"! Size x not valid. Using %d instead.\n",*x);
	}
	/* validate y value */
	if (*y<y_min || *y>y_max) {
		*y = y_min + rand() % (y_max - y_min);
		fprintf(stderr,"! Size y not valid. Using %d instead.\n",*y);
	}
	/* validate number of monsters */
	if (*nwumpus < 0 || *nwumpus > ((int)((*x)*(*y)*nw))) {
		*nwumpus = rand() % (int)((*x)*(*y)*nw);
		fprintf(stderr,"! Number of monsters not valid. Using %d instead.\n",*nwumpus);
	}
	/* validate number of pits */
	if (*npit < 0 || *npit > ((int)((*x)*(*y)*np))) {
		*npit = rand() % (int)((*x)*(*y)*np);
		fprintf(stderr,"! Number of pits not valid. Using %d instead.\n",*npit);
	}
	return;
}

int map_valid(int solvable, char map[x_max][y_max], int x, int y) {
	/* If map is requested to be solvable, checks for path betwen player (x,0)
	 * and gold (G). If there is no path, returns FALSE */
	 
	int i,xx,yy,a,b,valid;
	int dir[2][4] = {{0,1,0,-1},{1,0,-1,0}};
	char _map[x_max][y_max];
	
	
	if (!solvable) return 1; /* no map requests */
		
	for (a=0;a<x;a++) for (b=0;b<y;b++) _map[a][b]=map[a][b];
	clear_stack();
	valid=0;
	a=x-1;b=0;_map[a][b]='x'; push(a);push(b);
	
	while (map[a][b]!='G') {
		b=pop();a=pop();
		if (a<0) break;
		
		if (_map[a][b]=='G') {
			valid = 1;
			break;
		} else
			_map[a][b]='x';
			
		for (i=0;i<4;i++) {
			xx=a+dir[0][i];
			yy=b+dir[1][i];
			if (xx>=0 && xx<x && yy>=0 && yy<y) if(_map[xx][yy] == '.' || _map[xx][yy] == 'G') {
				push(xx);
				push(yy);
			}
		}
	}

	if (!valid) fprintf(stderr,"! Generated map not solvable, discarding...\n");
	return valid;
}

void generate_map(char map[x_max][y_max], int solvable, int x, int y, int nwumpus, int npit) {
	
	int a,b,i;
	
	/* validate parameters */
	validate(&x, &y, &nwumpus, &npit);
	
	/* try to generate map */
	do {
	/* clear array */
		for (a=0;a<x;a++) for (b=0;b<y;b++) map[a][b]='.';
		
	/* generate pits .. */
		i = npit;
		while (i) {
			a = rand() % x;
			b = rand() % y;
			
			if (a!=0 && b!=y) if (!(map[a][b]!='.') && (a!=x && b!=0)) {
				map[a][b]='p';
				i--;			
			}
		}

	 /* generate monsters ..*/
		i = nwumpus;
		while (i) {
			a = rand() % x;
			b = rand() % y;
			
			if (a!=0 && b!=y) if (map[a][b]=='.' && (a!=x && b!=0)) {
				map[a][b]='w';
				i--;
			}
		}

	/* place gold .. */
		i=1;
		while (i) {
			a = rand() % x;
			b = rand() % y;
			if (a!=0 && b!=y) if (map[a][b]=='.' && (a!=x && b!=0)) {
				map[a][b]='G';
				i--;
			}
		}
	
	} while (!map_valid(solvable, map, x, y));

}
