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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "out.h"

/* makes stack for led no index */
void MakeStack(int index) {
	node * nptr;
	nptr = (node *)malloc(sizeof(node));
	nptr->ptr = c.larray + index;
	nptr->type = LED; 
	push(&s, nptr);
	PushInnerLed(c.larray + index);
}

/* helps in making stack, pushes ptr stored in led */
void PushInnerLed(led * l) {
	node * nptr;
	nptr = (node *)malloc(sizeof(node));
	switch(l->type) {
		case SWITCH :
			nptr->ptr = l->ptr;
			nptr->type = SWITCH;
			push(&s, nptr);
			break;
	
		case OUTPUT :
			nptr->ptr = l->ptr;
			nptr->type = OUTPUT;
			push(&s, nptr);
			PushInnerOutput(l->ptr);
			break;
		default :
			break;
	}
}

/* helps in making stack, pushes ptr stored in output */
void PushInnerOutput(output * o) {
	node * nptr;
	nptr = (node *)malloc(sizeof(node));
	
	nptr->ptr = o->ip1;
	nptr->type = INPUT;
	push(&s, nptr);
	PushInnerInput(o->ip1);
	if(o->ip2 != NULL) {
		nptr->ptr = o->ip2;
		push(&s, nptr);
		PushInnerInput(o->ip2);
	}
}

/* helps in making stack, pushes ptr stored in input*/
void PushInnerInput(input * i) {
	node * nptr;
	nptr = (node *)malloc(sizeof(node));
	switch(i->type) {
		case SWITCH :
			nptr->ptr = i->ptr;
			nptr->type = SWITCH;
			push(&s, nptr);
			break;
	
		case OUTPUT :
			nptr->ptr = i->ptr;
			nptr->type = OUTPUT;
			push(&s, nptr);
			PushInnerOutput(i->ptr);
			break;
	
		default :
			break;
	}
}

/* gives value of a switch */
short GetValue(sch * ptr) {
	short ans ;
	ans = ptr->value;
	return ans;
}

/* gives both inputs */
void GetInputs(int * n1, int * n2, output * o) {
	 *n1 = o->ip1->value;
	if(o->type != NOT) 
		*n2 = o->ip2->value;
}

/* puts value in output / input/ led */
void PutValue(node * ptr , int value) {
	input * iptr;
	output * optr;
	led * lptr;	
	switch(ptr->type) {
		case INPUT :
			iptr = ptr->ptr;
			iptr->value = value;
			break;	
		
		case OUTPUT :
			optr = ptr->ptr;
			optr->value = value;
			break;

		case LED :
			lptr = ptr->ptr;
			lptr->value = value;
			break;
	}
}

/* finds the value of every led saves it in data structure and in Array (used for drawing screen) */
void findOutput(){ 
	int i, n1, n2, value;
	output * optr;
	node * nptr;
	for(i = 0; i < c.li; i++) {
		init(&s);		
		MakeStack(i);
		while(!empty(&s)) {
			nptr = pop(&s);
			switch(nptr->type) {
				case INPUT :
					PutValue(nptr, value);
					break;
			
				case OUTPUT :	
					GetInputs(&n1, &n2, nptr->ptr);
					/* Calculating Output */
					optr = nptr->ptr;
					switch(optr->type) {
						case NAND :
							value = nand(n1, n2);
							break;
	
						case XNOR :
							value = xnor(n1, n2);
							break;

						case NOR :
							value = nor(n1, n2);
							break;

						case AND :
							value = and(n1, n2);
							break;

						case OR :
							value = or(n1, n2);
							break;
					
						case XOR :
							value = xor(n1, n2);
							break;

						case NOT :
							value = not(n1);
							break;

						default :
						break;
						
					PutValue(nptr, value);
					}
					break;
		
				case SWITCH :
					value = GetValue(nptr->ptr); 
					break;

				case LED :
					PutValue(nptr, value);
					break;
			}
		}
	}
	ChangeOnscreen();	
}

/* Changes value of led in data structure */
void ChangeOnscreen() {
	int i, j, ximg, yimg;
	for(i = 0; i < c.li; i++) {
		ximg = c.larray[i].ximage;
		yimg = c.larray[i].yimage;
		for(j = 0; j < cntArray; j++) {
			if((ximg == Array[j].x) && (yimg == Array[j].y)) {
				if(c.larray[i].value == 1) 
					Array[j].index = LED_ON_SPRITE;
				else 
					Array[j].index = LED_OFF_SPRITE;
			}		
		}
	}
}

short and(short a, short b) {
	if(a && b)
		return 1;
	return 0;
}

short or(short a, short b) {
	if(a || b)
		return 1;
	return 0;
}

short nand(short a, short b) {
	return not(and(a, b));
}

short nor(short a, short b) {
	return not(or(a, b));
}

short xor(short a, short b) {
	if(a != b)
		return 1;
	return 0;
}

short xnor(short a, short b) {
	if(a == b)
		return 1;
	return 0;
}

short not(short a) {
	if(a == 1)
		return 0;
	return  1;
}

/* Makes all Led Zero in data structure and in Array */
void offCircuit() { 
	int i ;
	for(i = 0; i < c.li; i++) {
		c.larray[i].value = 0;
	}
	for(i = 0; i < cntArray; i++) {
		if(Array[cntArray].index == LED_ON_SPRITE)
			Array[cntArray].index = LED_OFF_SPRITE;	
	}
}
