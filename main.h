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

/* include all structure definations required to carry screen */ 

#ifndef MAINHEADER
#define MAINHEADER
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#define WIDTH		1400
#define HEIGHT		1000
#define ELESIZE		40
#define WIRESIZE	50	
enum {
	TOOL_SPRITE,
	AND_SPRITE,
	OR_SPRITE,
	NAND_SPRITE,
	NOR_SPRITE,
	XOR_SPRITE,
	XNOR_SPRITE,
	NOT_SPRITE,
	SWITCH0_SPRITE,
	SWITCH1_SPRITE,
	LED_ON_SPRITE,
	LED_OFF_SPRITE,
	WIRE_SPRITE,
	RESET_SPRITE,
	DONE_SPRITE,
	WIREFIELD_SPRITE,
	MAX_SPRITE,
};

/* significant click is remembered */
typedef struct movement {
	int flag;
	int x, y;
}movement;
 
/* mouse clicks are stored */
typedef struct control {
	int x, y;
	movement firstclick, lastclick, wire;
	int reset;
	int done;
}control;

control just;
/* entity with image and position in screen */
typedef struct sprite {
	int x, y;
	SDL_Surface * image;
}sprite;
 
SDL_Surface *screen;
sprite sp[MAX_SPRITE];

/* element in the ckt */
typedef struct element {
	int x, y;
	int index;/* Image index */
}element;

element current;/* current hold by mouse */
element Array[ELESIZE]; /* elements in the ckt */
int cntArray;

/* wires with endpoints */
typedef struct wire {
	int startx, endx, starty, endy;	
}wire;

/* wires in the ckt */
wire wires[WIRESIZE];
int cntwires;

/* opens window and gives it a title */
void inittitle(char *);

/* cleans all memory at the end */
void cleanup();

/* takes care of every movement on the screen */
void getInput();

/* function such that screen stays for a while */
void delay(unsigned int);

/* builds all the required structures Sprite, loading images  */
void LoadAllSprites();

/* build structure sprite , loads image*/
void LoadSprite(int, char *);

/* loads images into memory for fast access*/
SDL_Surface * LoadImage(char *);

/* free all sprites */
void FreeALLSprites();

/* builds all the required structures Sprite, defining position on screen   */
void initAllSprites();

/* builds Sprite, defining position on screen   */
void initSprite(int);

/* builds a structure data to send to fuction which build main structure ckt */
void doEverything(); 

/* draws the screen */
void draw();

/* draws Toolbox */
void drawTool();

/* draws image stored in the sprite to the position also stored in it */
void drawSprite(int);

/* initializes the structure "just" that stores movement on screen */
void in();

/* draws all wires */
void drawWires();

/* draws line */
void drawLine(int startx, int starty, int endx, int endy);

/* draws components currently in the ckt */
void drawArray();

/* draws current picture hold by mouse */
void drawCurrent();

/* draws image indicated by index at position given by x, y*/
void drawSprite2(int, int, int);
void checkLed();

#endif
