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

#ifndef STACKHEADER
#define STACKHEADER

#include <stdio.h>
#include <stdlib.h>

#define MAX 128

/* array a and curr become global now */
typedef struct node {
	void * ptr;
	short type;
}node;

typedef struct stack {
	node a[MAX];
	int curr;
}stack;

void push(stack *s, node * n); 
node * pop(stack *s);
void init(stack *s); 
int empty(stack *s);
int full(stack *s);

#endif
