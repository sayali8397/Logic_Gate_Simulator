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

/* THis header File contains fuctions to glow led and print truthtable and boolean equation */
#ifndef OUTHEADER
#define OUTHEADER
#include "logic.h"
#include "stack.h"
stack s;
short and(short a, short b);
short or(short a, short b);
short nand(short a, short b);
short nor(short a, short b);
short xor(short a, short b);
short xnor(short a, short b);
short not(short a);

/* finds the value of every led saves it in data structure and in Array (used for drawing screen) */
void findOutput();

/* makes stack for led no index */
void MakeStack(int index);

/* puts value in output / input/ led */
void PutValue(node * ptr , int value);

/* gives both inputs */
void GetInputs(int * n1, int * n2, output * o);

/* gives value of a switch */
short GetValue(sch * ptr);

/* helps in making stack, pushes ptr stored in led */
void PushInnerLed(led *);

/* helps in making stack, pushes ptr stored in input*/
void PushInnerInput(input *);

/* helps in making stack, pushes ptr stored in output */
void PushInnerOutput(output *);

/* Makes all Led Zero in data structure and in Array */
void offCircuit();

/* Changes value of led in data structure */
void ChangeOnscreen();

#endif
