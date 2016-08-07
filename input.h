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

/* contains structure and functions which build data structure ckt */

#ifndef INPUTHEADER
#define INPUTHEADER

typedef struct Info {
	char type;
	int x, y, wirex, wirey;
	short value;
}Info;
Info data; 

void indata();/* Initializes structure data */
void dodatastruct();/* Build data structure ckt using value stored in data */

#endif
