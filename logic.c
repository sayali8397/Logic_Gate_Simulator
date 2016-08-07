/*
< Logic Gate Simulator > Copyright (C) < 2015 >  < Sayali S. Salunke>
< sayalisalunke8397@gmail.com >

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*  Contains code to build the data structure ckt i.e. helping functions to input.c  */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "main.h"
#include "logic.h"

extern int cntArray;

/* Initializes main data structure ckt */
void inc() {
	static int f = 0;
	if( f == 0) {
		c.oi = c.ii = c.si = c.li = 0;
		cnt = 0;
		cntArray = 0;
		cntwires = 0;
		f = 1;
	}
}

/* build structure input , x and y specifies position on screen*/
void ininput(input * i, int x, int y) {
	i->value = -1;
	junction[cnt].x = x;
	junction[cnt].y = y;
	junction[cnt].type = INPUT;
	junction[cnt].ptr = i;
	cnt++;
}

/* buids structure output, x and y specifies position on screen , i1, i2 points to corresponding inputs */
void inoutput(output * o, input * i1, input * i2, char type, int x, int y) {
	o->value = -1;
	o->ip1 = i1;
	o->ip2 = i2;
	o->type = type;
	junction[cnt].x = x;
	junction[cnt].y = y;
	junction[cnt].type = OUTPUT;
	junction[cnt].ptr = o;
	cnt++;
}

/* connects two components of a ckt */
void inwire(int x1, int y1, int x2, int y2) {
	pos * p, *q;
	input * iptr;
	output * optr;
	sch * sptr;
	led * lptr;
	p = getit(x1, y1);
	q = getit(x2, y2);

	switch(p->type) {
		case INPUT:
			iptr = (input *)p->ptr;
			switch(q->type) {
				case OUTPUT :/* INPUT , OUTPUT */
					optr = (output *)q->ptr;
					iptr->ptr = optr;
					iptr->type = OUTPUT;
					break;

				case SWITCH : /* INPUT , SWITCH */
					sptr = (sch *)q->ptr;
					iptr->ptr = sptr;
					iptr->type = SWITCH;
					break;

				case LED : /* INPUT , LED */
					/*IMPOSSILE COMBINATION */
					break;

			}
			break;
		case OUTPUT:
			optr = (output *)p->ptr;
			switch(q->type) { 
				case INPUT : /* OUTPUT , INPUT */ 
					iptr = (input *)q->ptr;
					iptr->ptr = optr;
					iptr->type = OUTPUT;
					break;

				case SWITCH : /* OUTPUT , SWITCH */
					/* IMPOSSIBLE COMBINATION */
					break;

				case LED : /* OUTPUT , LED */
					lptr = (led *)q->ptr;
					lptr->ptr = optr;
					lptr->type = OUTPUT;
					break;
			}
			break;
		case SWITCH:
			sptr = (sch *)p->ptr;
			switch(q->type) {
				case INPUT : /* INPUT, SWITCH */
					iptr = (input *)q->ptr;
					iptr->ptr = sptr;
					iptr->type = SWITCH;
					break;

				case OUTPUT : /* SWITCH , OUTPUT */
					/* IMPOSSIBLE COMBINATION */
					break;

				case LED : /* SWITCH , LED */
					lptr = (led *)q->ptr;
					lptr->ptr = sptr;
					lptr->type = SWITCH;
					break;
			}
			break;
		case LED :
			lptr = (led *)p->ptr;
			switch(q->type) {
				case INPUT : /*LED , INPUT */
					/* IMPOSSILE COMBINATION */
					break;

				case OUTPUT : /* LED , OUTPUT */
					optr = (output *)q->ptr;
					lptr->ptr = optr;
					lptr->type = OUTPUT; 
					break;

				case SWITCH : /* LED , SWITCH */
					sptr = (sch *)q->ptr;
					lptr->ptr = sptr;
					lptr->type = SWITCH;
					break;
			}
			break;

	}
	
}

/* builds structure switch , x and y specifies position on screen and state gives its value */
void inswitch(sch * s, int x, int y, short state) {
	
	s->value = state;
	junction[cnt].x = x;
	junction[cnt].y = y;
	junction[cnt].type = SWITCH;
	junction[cnt].ptr = s;
	cnt++;
}

/* builds structure led , x and y specifies position , ximage and yimage specifies pixel holding its image */
void inled(led *l , int x, int y, int ximage, int  yimage) {
	l->value = 0;
	l->ximage = ximage;
	l->yimage = yimage;
	junction[cnt].x = x;
	junction[cnt].y = y;
	junction[cnt].type = LED;
	junction[cnt].ptr = l;
	cnt++;	
}

/* returns a pointer to a structure which points to a component of the ckt at position (x, y) on screen */
pos *getit(int x, int y) {
	pos *ptr = (pos *)malloc(sizeof(pos));
	int i = 0;
	for(i = 0; i < cnt ; i++) {
		if(junction[i].x == x && junction[i].y == y) {
			ptr->x = x;
			ptr->y = y;
			ptr->ptr = junction[i].ptr;
			ptr->type = junction[i].type;
		}
	}
	return ptr;
}

/* determines near by connection point of the click */ 
void nearBy(int * ax, int * by, int x, int y) {
	float dist, min = 2000000;
	int i, xjunc, yjunc, imin;
	for(i = 0; i < cnt; i++) {
		xjunc = junction[i].x;
		yjunc = junction[i].y;
		dist = ((x - xjunc) * (x - xjunc)) + ((y - yjunc) * (y - yjunc));
		if(dist < min) {
			min = dist;
			imin = i;
		}
	}
	*ax = junction[imin].x;
	*by = junction[imin].y;
}
