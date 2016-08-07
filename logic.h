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

/* Contains functions to build the data structure ckt i.e. helping functions to input.c */

#ifndef LOGICHEADER
#define LOGICHEADER

#define AND 	1
#define OR 	2
#define NAND 	3
#define NOR	4
#define XOR 	5
#define XNOR	6
#define NOT 	7
#define INPUT 	8
#define OUTPUT 	9
#define LED  	10
#define SWITCH 	11
#define GATE 	12
#define WIRE 	13
#define STATEC	14
#define DONE 	15
#define RESET	16

#define JUNCSIZE	100
#define COMPSIZE 	50
typedef struct sch {
	short value; 
}sch;

typedef struct led {
	int ximage, yimage;
	void * ptr;
	char type;
	short value;
}led;

typedef struct input {
	void * ptr;
	char type;
	short value;
}input;

typedef struct output {
	short value;
	char type ; /* type of the corresponding gate */  
	input * ip1, *ip2;
}output;

/* this is the structure whose array junction we will be using to build structure i.e. to link the elements with each other */
typedef struct pos { /* input output sch led */ 
	int x, y; /* connecting points*/
	void * ptr; /* pointer to the element */
	char type; /* type of the element */ 
}pos;

struct pos junction[JUNCSIZE];
int cnt; /* no. of elements in the junction */ 

typedef struct ckt {
	output oarray[COMPSIZE]; /* array of outputs */
	led larray[COMPSIZE];	/* array of leds */
	sch sarray[COMPSIZE];	/* array of switches */
	input iarray[COMPSIZE]; /* array of inputs */
	int oi, si, li, ii; /* corresponding counters */
}ckt;
ckt c;

/* Initializes main data structure ckt */
void inc();

/* build structure input , x and y specifies position on screen*/
void ininput(input * , int, int);

/* buids structure output, x and y specifies position on screen , i1, i2 points to corresponding inputs */
void inoutput(output *, input *, input *, char, int, int);

/* connects two components of a ckt */
void inwire(int, int, int, int);

/* returns a pointer to a structure which points to a component of the ckt at position (x, y) on screen */
pos *getit(int x, int y);

/* builds structure switch , x and y specifies position on screen and state gives its value */
void inswitch(sch * s, int x, int y, short state);

/* builds structure led , x and y specifies position , ximage and yimage specifies pixel holding its image */
void inled(led *l, int x, int y, int ximage, int yimage);

/* determines near by connection point to the click */ 
void nearBy(int *, int *, int, int);
#endif
