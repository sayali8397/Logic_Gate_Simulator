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

/* array a and curr become global now */

#include "stack.h"
void push(stack *s, node * n) {
	s->a[s->curr].ptr = n->ptr;
	s->a[s->curr].type = n->type;
	s->curr++;
}
node * pop(stack *s) {
	node * n;
	n = (node *)malloc(sizeof(node));
	n->ptr = s->a[s->curr - 1].ptr;
	n->type = s->a[s->curr - 1].type;
	s->curr--;
	return n;
}
/* This function gets added, because with a type declration, we can't do curr = 0 */
void init(stack *s) {
	s->curr = 0;
}
int empty(stack *s) {
	return s->curr == 0;
}
int full(stack *s) {
	return s->curr == 128;
}

