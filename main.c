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
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "out.h"
#include "input.h"
#include "main.h"

/* main function , handles screen and calls all the prime function that calls subfunction */
int main() {
	inc();
	unsigned int frameLimit = SDL_GetTicks() + 16;
	inittitle("Logic Gate Simulator");
	atexit(cleanup);
	LoadAllSprites();
	initAllSprites();
	
	while(1) {
		getInput();
		doEverything();
		draw();	
		delay(frameLimit);
		frameLimit = SDL_GetTicks() + 16;
	}		
	exit(0);
}

/* opens window and gives it a title */
void inittitle(char *c) {	
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Could not initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}
	screen = SDL_SetVideoMode(WIDTH , HEIGHT, 0, SDL_HWPALETTE);
	if (screen == NULL) {
		printf("Couldn't set screen mode to 640 x 480: %s\n", SDL_GetError());
		exit(1);
	}
	SDL_WM_SetCaption(c, NULL);
}

/* cleans all memory at the end */
void cleanup() {
	FreeALLSprites();
	SDL_FreeSurface(screen);
	SDL_Quit();
}

/* takes care of every movement on the screen */
void getInput() {
	in();
	SDL_Event event;
		
	while(SDL_PollEvent(&event)) {
		
		switch(event.type) {
			/* Closing the Window or pressing Escape will exit the program */
			case SDL_QUIT :
				exit(0);
				break;

			case SDL_MOUSEBUTTONDOWN:
				switch(event.button.button) {
					case SDL_BUTTON_LEFT :
					case SDL_BUTTON_RIGHT :
						SDL_GetMouseState(&just.x, &just.y);
						if((just.x >= 0) && (just.x <= 1400) && (just.y >= 0) && (just.y <= 200)) {							
							just.done = 1;
							just.firstclick.flag = 0;
						}
						if((just.x >= 0) && (just.x <= 1400) && (just.y > 200) && (just.y <= 1000) && (just.done == 1)) {		
							just.done = 2;
							just.lastclick.flag = 0;
						}							
						break;
					default:
					break;
				}
				break;
		}	
		SDL_GetMouseState(&just.x, &just.y);

		if((just.firstclick.flag == 0) && (just.done == 1)) {
			
			if((just.x >= 0) && (just.x <= 1400) && (just.y >= 0) && (just.y <= 200)) {				
				just.firstclick.flag = 1;
				just.firstclick.x = just.x;
				just.firstclick.y = just.y;
				just.wire.flag = 0;
				just.wire.x = 0;
				just.wire.y = 0;
				if((just.x >= 800) && (just.x <= 1000) && (just.y >= 100) && (just.y <= 200)) {					
				just.wire.flag = 1;
				} 
			}		
			else { 
				just.done = 0;
				just.firstclick.flag = 0;
				just.wire.flag = 0;
				just.wire.x = 0;
				just.wire.y = 0;
			}
		
		}
		if((just.lastclick.flag == 0) && (just.done == 2)) {


			if((just.x >= 0) && (just.x <= 1400) && (just.y > 200) && (just.y <= 1000)) {			
				just.lastclick.flag = 1;
				just.lastclick.x = just.x;
				just.lastclick.y = just.y;
				
				if((just.wire.flag == 1) && (just.wire.x == 0)) {
					just.wire.x = just.x;
					just.wire.y = just.y;
					just.done = 1;
					just.lastclick.flag = 0;
				}
			}
			else {
				just.done = 1;
				just.lastclick.flag = 0;
			}
		}
		
	}
}	

/* initializes the structure "just" that stores movement on screen */
void in() {
	static int flag = 0;
	if(flag == 0) {
		just.firstclick.flag = 0;
		just.lastclick.flag = 0;
		just.wire.flag = 0;
		just.done = 0;
		flag = 1;
	}

}

/* function such that screen stays for a while */
void delay(unsigned int frameLimit) {
	unsigned int ticks = SDL_GetTicks();
	if (frameLimit < ticks)	{
		return;
	}
	if (frameLimit > ticks + 16) {
		SDL_Delay(16);
	}
	else {
		SDL_Delay(frameLimit - ticks);
	}
}

/* builds all the required structures Sprite, loading images  */
void LoadAllSprites() {
	LoadSprite(TOOL_SPRITE, "img/toolbox.png");
	LoadSprite(AND_SPRITE, "img/and.png");
	LoadSprite(OR_SPRITE, "img/or.png");
	LoadSprite(NAND_SPRITE, "img/nand.png");
	LoadSprite(NOR_SPRITE, "img/nor.png");
	LoadSprite(XOR_SPRITE, "img/xor.png");
	LoadSprite(XNOR_SPRITE, "img/xnor.png");
	LoadSprite(NOT_SPRITE, "img/not.png");
	LoadSprite(SWITCH0_SPRITE, "img/switch0.png");
	LoadSprite(SWITCH1_SPRITE, "img/switch1.png");
	LoadSprite(LED_ON_SPRITE, "img/ledon.png");
	LoadSprite(LED_OFF_SPRITE, "img/ledoff.png");
	LoadSprite(WIRE_SPRITE, "img/wire.png");
	LoadSprite(RESET_SPRITE, "img/reset.png");
	LoadSprite(DONE_SPRITE, "img/done.png");
	LoadSprite(WIREFIELD_SPRITE, "img/wirefield.png");
}

/* build structure sprite  ,loads image*/
void LoadSprite(int index, char *c ) {
	/* Load the image into the next slot in the sprite bank */
	if (index >= MAX_SPRITE || index < 0) {
		printf("Invalid index for sprite! Index: %d Maximum: %d\n", index, MAX_SPRITE);
		exit(1);
	}
	sp[index].image = LoadImage(c);
	if (sp[index].image == NULL) {
		exit(1);
	}
}

/* loads images into memory for fast access*/
SDL_Surface *LoadImage(char * c) {
	/* Load the image using SDL Image */
	SDL_Surface *temp = IMG_Load(c);
	SDL_Surface *image;	
	if (temp == NULL) {
		printf("Failed to load image %s\n", c);
		return NULL;
	}

	/* Make the background transparent */
	SDL_SetColorKey(temp, (SDL_SRCCOLORKEY|SDL_RLEACCEL), SDL_MapRGB(temp->format, 0, 0, 0));

	/* Convert the image to the screen's native format */
	image = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);
	if (image == NULL) {
		printf("Failed to convert image %s to native format\n", c);
		return NULL;
	}

	/* Return the processed image */
	return image;
}

/* free all sprites */
void FreeALLSprites() {
	int i;
	/* Loop through the sprite bank and clear the images */
	for (i=0; i < MAX_SPRITE; i++) {
		if (sp[i].image != NULL) {
			SDL_FreeSurface(sp[i].image);
		}
	}
}

/* builds all the required structures Sprite, defining position on screen   */
void initAllSprites() {
	int i;
	for(i = 0; i < MAX_SPRITE; i++) {
		initSprite(i);
	}
}

/* builds Sprite, defining position on screen   */
void initSprite(int index) {
	switch(index) {
		case TOOL_SPRITE :
			sp[TOOL_SPRITE].x = 0 ;
			sp[TOOL_SPRITE].y = 0;
			break;

		case AND_SPRITE :
			sp[AND_SPRITE].x = 200 ;
			sp[AND_SPRITE].y = 0;
			break;
			
		case OR_SPRITE :
			sp[OR_SPRITE].x = 400;
			sp[OR_SPRITE].y = 0;
			break;

		case NAND_SPRITE :
			sp[NAND_SPRITE].x = 600;
			sp[NAND_SPRITE].y = 0;
			break;
			
		case NOR_SPRITE :
			sp[NOR_SPRITE].x = 800;
			sp[NOR_SPRITE].y = 0;
			break;
			
		case XOR_SPRITE :
			sp[XOR_SPRITE].x = 1000;
			sp[XOR_SPRITE].y = 0;
			break;
			
		case XNOR_SPRITE :
			sp[XNOR_SPRITE].x = 1200;
			sp[XNOR_SPRITE].y = 0;
			break;
			
		case NOT_SPRITE :
			sp[NOT_SPRITE].x = 0;
			sp[NOT_SPRITE].y = 100;
			break;
			
		case SWITCH0_SPRITE :
			sp[SWITCH0_SPRITE].x = 200;
			sp[SWITCH0_SPRITE].y = 100;
			break;
		
		case SWITCH1_SPRITE :
			sp[SWITCH1_SPRITE].x = 400;
			sp[SWITCH1_SPRITE].y = 100;
			break;
		
		case LED_ON_SPRITE :
			sp[LED_ON_SPRITE].x = -1;
			sp[LED_ON_SPRITE].y = -1;
			break;
		
		case LED_OFF_SPRITE :
			sp[LED_OFF_SPRITE].x = 600;
			sp[LED_OFF_SPRITE].y = 100;
			break;
			
		case WIRE_SPRITE :
			sp[WIRE_SPRITE].x = 800;
			sp[WIRE_SPRITE].y = 100;
			break;
			
		case RESET_SPRITE :
			sp[RESET_SPRITE].x = 1000;
			sp[RESET_SPRITE].y = 100;
			break;
			
		case DONE_SPRITE :
			sp[DONE_SPRITE].x = 1200;
			sp[DONE_SPRITE].y = 100;
			break;
		
		case WIREFIELD_SPRITE :
			sp[WIREFIELD_SPRITE].x = -1;
			sp[WIREFIELD_SPRITE].y = -1;
			break;
		
		default :
			break;

	}

}

/* builds a structure data to send to fuction which build main structure ckt */
void doEverything() {
	indata();
	int index = -1;
	int x = -1, y = -1;
	if(just.firstclick.flag == 1) {
		x = just.firstclick.x;
		y = just.firstclick.y;
	}
	if((x >= 200) && (x < 400) && (y >= 0) && (y < 100)) {
		index = AND_SPRITE;
	}
	else if((x >= 400) && (x < 600) && (y >= 0) && (y < 100)) {
		index = OR_SPRITE;
	}
	else if((x >= 600) && (x < 800) && (y >= 0) && (y < 100)) {
		index = NAND_SPRITE;
	}
	else if((x >= 800) && (x < 1000) && (y >= 0) && (y < 100)) {
		index = NOR_SPRITE;
	}
	else if((x >= 1000) && (x < 1200) && (y >= 0) && (y < 100)) {
		index = XOR_SPRITE;
	}
	else if((x >= 1200) && (x <= 1400 ) && (y >= 0) && (y < 100)) {
		index = XNOR_SPRITE;
	}
	else if((x >= 0) && (x < 200) && (y >= 100) && (y <= 200)) {
		index = NOT_SPRITE;
	}
	else if((x >= 200) && (x < 400) && (y >= 100) && (y <= 200)) {
		index = SWITCH0_SPRITE;
	}
	else if((x >= 400) && (x < 600) && (y >= 100) && (y <= 200)) {
		index = SWITCH1_SPRITE;
	}
	else if((x >= 600) && (x < 800) && (y >= 100) && (y <= 200)) {
		index = LED_OFF_SPRITE;
	}
	else if((x >= 800) && (x < 1000) && (y >= 100) && (y <= 200)) {
		index = WIRE_SPRITE;
	}			
	else if((x >= 1000) && (x < 1200) && (y >= 100) && (y <= 200)) {
		index = RESET_SPRITE;
	}
	else if((x >= 1200) && (x <= 1400) && (y >= 100) && (y <= 200)) {
		index = DONE_SPRITE;
	}

	if(index == DONE_SPRITE) {
		index = -1;
		findOutput();
		just.firstclick.flag = 0;
		just.lastclick.flag = 0;
		just.wire.flag = 0;
		just.wire.x = 0;
		just.wire.y = 0;
		just.done = 0;
		return;
	}
	else {
		offCircuit();
	}

	if(index == RESET_SPRITE) {
		cntArray = 0;
		cntwires = 0;
		current.index = -1;
		just.firstclick.flag = 0;
		just.lastclick.flag = 0;
		just.wire.flag = 0;
		just.wire.x = 0;
		just.wire.y = 0;
		just.done = 0;
		data.type = RESET;
		dodatastruct();
	}
	else if(just.done == 1) {
		if(index != WIRE_SPRITE) {
			current.index = index;
			current.x = just.x;
			current.y = just.y;
		}	
	}
	else if(just.done == 2) {
		if(index != WIRE_SPRITE) {
			Array[cntArray].index = index;
			Array[cntArray].x = just.lastclick.x;
			Array[cntArray].y = just.lastclick.y;
			cntArray++;
		}
		data.x = just.lastclick.x;
		data.y = just.lastclick.y;
		if(just.wire.flag == 1) {
			data.wirex = just.wire.x;
			data.wirey = just.wire.y;
		}
		switch(index) {
			case AND_SPRITE :
				data.type = AND;
				break;
			
			case OR_SPRITE :
				data.type = OR;
				break;
			
			case NAND_SPRITE :
				data.type = NAND;
				break;
			
			case NOR_SPRITE :
				data.type = NOR;
				break;
	
			case XOR_SPRITE :
				data.type = XOR;
				break;

			case XNOR_SPRITE :
				data.type = XNOR;
				break;

			case NOT_SPRITE :
				data.type = NOT;
				break;
			
			case SWITCH0_SPRITE :
				data.type = SWITCH;
				data.value = 0;
				break;

			case SWITCH1_SPRITE :
				data.type = SWITCH;
				data.value = 1;
				break;

			case LED_OFF_SPRITE :
				data.type = LED;
				break;

			case WIRE_SPRITE :
				data.type = WIRE;
				break;
		
			default :
				break;

		}
		dodatastruct();
		
		just.firstclick.flag = 0;
		just.lastclick.flag = 0;
		just.done = 0;
		
	}
		
}

/* draws the screen */
void draw() {
	SDL_FillRect(screen, NULL, 0);
	drawTool();
	drawArray();
	drawWires();
	drawCurrent();
	SDL_Flip(screen);
}

/* draws Toolbox */
void drawTool() {
	int i;
	for(i = 0; i < MAX_SPRITE; i++) {
		if(i == LED_ON_SPRITE) 
			continue;		
		drawSprite(i);	
	}
}

/* draws image stored in the sprite to the position also stored in it */
void drawSprite(int index) {
	SDL_Rect dest;

	/* Set the blitting rectangle to the size of the src image */

	dest.x = sp[index].x;
	dest.y = sp[index].y;
	dest.w = sp[index].image->w;
	dest.h = sp[index].image->h;
	
	/* Blit the entire image onto the screen at coordinates x and y */
	SDL_BlitSurface(sp[index].image, NULL, screen, &dest);
	
}

/* draws components currently in the ckt */
void drawArray() {
	int i;
	for(i = 0; i < cntArray; i++) {
		if((Array[i].index >= 0) && (Array[i].index < MAX_SPRITE))
			drawSprite2(Array[i].index, Array[i].x, Array[i].y);
	} 
}

/* draws all wires */
void drawWires() {
	int i;
	for(i = 0; i < cntwires; i++) {
		drawLine(wires[i].startx, wires[i].starty, wires[i].endx, wires[i].endy);
	}
}

/* draws line */
void drawLine(int startx, int starty, int endx, int endy) { 
	float m, b;
	int dx = endx - startx;
	int dy = endy- starty;
	drawSprite2(WIREFIELD_SPRITE, startx, starty);
		
	if (abs(dx) > abs(dy)) {
		/* handles slope < 1 */
		m = (float) dy / (float) dx; /* calculate the slope */
		b = starty - m * startx;
		/* compute the y-intercept */
		dx = (endx > startx) ? 1 : -1;
		while ( startx != endx ) {
			startx += dx;
			/* next x value */
			starty = round(m * startx + b); /* corresponding y value */
			drawSprite2(WIREFIELD_SPRITE, startx, starty);
		}
	} 
	else {
		/* handles slope >= 1 */
		m = (float) dx / (float) dy;
		b = startx - m * starty;
		dy = (endy > starty) ? 1 : -1;
		while (starty != endy) {
			starty +=dy;
			startx = round(m * starty + b);
			drawSprite2(WIREFIELD_SPRITE, startx, starty);
		}
	}
}

/* draws current picture hold by mouse */
void drawCurrent() {
	if((just.done == 1) && (current.index >= 0) && (current.index < MAX_SPRITE)) {
		drawSprite2(current.index, current.x, current.y);
	}
}

/* draws image indicated by index at position given by x, y*/
void drawSprite2(int index, int x, int y) {
	SDL_Rect dest;

	/* Set the blitting rectangle to the size of the src image */

	dest.x = x;
	dest.y = y;
	dest.w = sp[index].image->w;
	dest.h = sp[index].image->h;
	
	/* Blit the entire image onto the screen at coordinates x and y */
	SDL_BlitSurface(sp[index].image, NULL, screen, &dest);
} 

