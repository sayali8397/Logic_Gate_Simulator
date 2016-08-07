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

/* contains code which build data structure ckt by calling function from input.c*/

#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "logic.h"
#include "input.h"

/* Initializes structure data */
void indata() {
	data.type = -1;
	data.value = -1;
	data.x = data.y = data.wirex = data.wirey = -1;
}

/* Build data structure ckt using value stored in data */
void dodatastruct() {
	input * i1, *i2;
	int x1, x2, xo, y1, y2, yo;	
	int x, y;
	x = data.x;
	y = data.y;	
	switch(data.type) {
		case AND : case OR : case NOR : case XOR :
		case NAND : case XNOR : 
				
			x1 = x;
			y1 = y + 25;
			x2 = x;
			y2 = y + 75;
			xo = x + 200;
			yo = y + 50;
			i1 = c.iarray + c.ii;
			i2 = c.iarray + c.ii + 1;
			ininput(i1, x1, y1);
			ininput(i2, x2, y2);
			c.ii = c.ii + 2;

			inoutput((c.oarray + c.oi), i1, i2, data.type, xo, yo);
			c.oi++;
			
			break;

		case NOT :
			x1 = x;
			y1 = y + 50;
			xo = x + 200;
			yo = y + 50;
			i1 = c.iarray + c.ii;
			i2 = NULL;
			ininput(i1, x1, y1);
			c.ii++;
	
			inoutput((c.oarray + c.oi), i1, i2, data.type, xo, yo);
			c.oi++;
 
		case WIRE :
			nearBy(&x1, &y1, data.x, data.y);
			nearBy(&x2, &y2, data.wirex, data.wirey);
			
			inwire( x1, y1, x2, y2); 
			
			wires[cntwires].startx = x1;
			wires[cntwires].endx = x2;
			wires[cntwires].starty = y1;
			wires[cntwires].endy = y2;
			cntwires++;
			break;

		case SWITCH :
			x1 = x + 200;
			y1 = y + 50;
			inswitch((c.sarray + c.si), x1, y1, data.value);
			c.si++;
			break;

		case LED :
			x1 = x;
			y1 = y + 50;
			inled((c.larray + c.li), x1, y1, x, y);
			c.li++;
			break;

		case RESET :
			c.oi = c.ii = c.li = c.si = 0;
			break;

		default :
			break;
	}
}
