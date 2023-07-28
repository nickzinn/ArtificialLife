#define ESC 27

#define TAB 9

#define ENTER 13

#define BACKSPACE 8

#define SHIFTTAB 271

#define CTRLEND 373

#define HOME 327

#define CTRLHOME 375

#define END 335

#define UPARROW 328

#define DOWNARROW 336

#define PGUP 329

#define PGDN 337

#define LEFTARROW 331

#define RIGHTARROW 333

#define INS 338

#define DEL 339



#define F1  315

#define F2  316

#define F3  317

#define F4  318

#define F5  319

#define F6  320

#define F7  321

#define F8  322

#define F9  323

#define F10 324

#define F11 360

#define F12 361

#define F13 362

#define F14 363

#define F15 364

#define F16 365

#define F17 366

#define F18 367

#define F19 368

#define F20 369



#define SHFTF1  340

#define SHFTF2  341

#define SHFTF3  342

#define SHFTF4  343

#define SHFTF5  344

#define SHFTF6  345

#define SHFTF7  346

#define SHFTF8  347

#define SHFTF9  348

#define SHFTF10 349



#define CTRLF1  350

#define CTRLF2  351

#define CTRLF3  352

#define CTRLF4  353

#define CTRLF5  354

#define CTRLF6  355

#define CTRLF7  356

#define CTRLF8  357

#define CTRLF9  358

#define CTRLF10 359

#define CTRL_R   18

#define CTRL_Y   25

#define CTRL_W   23



#define ATLF1  360

#define ALTF2  361

#define ALTF3  362

#define ALTF4  363

#define ALTF5  364

#define ALTF6  365

#define ALTF7  366

#define ALTF8  367

#define ALTF9  368

#define ALTF10 369



#define ALT_A 286

#define ALT_B 304

#define ALT_C 302

#define ALT_D 288

#define ALT_E 274

#define ALT_F 289

#define ALT_G 290

#define ALT_H 291

#define ALT_I 279

#define ALT_J 292

#define ALT_K 293

#define ALT_L 294

#define ALT_M 306

#define ALT_N 305

#define ALT_O 280

#define ALT_P 281

#define ALT_Q 272

#define ALT_R 275

#define ALT_S 287

#define ALT_T 276

#define ALT_U 278

#define ALT_V 303

#define ALT_W 273

#define ALT_X 301

#define ALT_Y 277

#define ALT_Z 300



#include "evosim3.h"

#include <dos.h>

extern void gprintxy(int xloc,int yloc, char *fmt,...);

extern void message(char *pc);

int getkey(void);



int isbuttonpressed(void)

{

	union REGS regs;

	regs.x.ax = 3;

	int86(0x33, &regs, &regs);

	return (regs.x.bx & 3);

}





int initmouse(void)

//init mouse, doesn't display mouse, and returns 1 on error

{

	union REGS regs;

	regs.x.ax = 0;             // reset mouse driver

	int86(0x33,&regs, &regs);  // and check status

	if (regs.x.ax == 0)

		{ 	printf("\n mouse not available");

		return 1;

		}

	 return 0;

}



void getmousexy(int *px, int *py)

{

	union REGS regs;

	regs.x.ax = 3;

	int86(0x33, &regs, &regs);

	*px = (regs.x.cx);

	*py = (regs.x.dx);

}



void mouseon()

{

union REGS regs;

 regs.x.ax = 1;

 int86(0x33, &regs, &regs);   // display mouse cursor

}

void mouseoff()

{

union REGS regs;

 regs.x.ax = 2;

 int86(0x33, &regs, &regs);   // hide mouse cursor



}



int isinside(int x, int y, struct rect_type rect)

{

if(x<rect.right && y>rect.up && x>rect.left && y<rect.down)

	return TRUE;

return FALSE;

}



int getkey()

{

int i=0;



if ((i=getch()) != 0 )

	return(i);



i=getch();

return(i+256);

}



int getfixed(char *pc, int length)   //return 1 on abort, 0 on success

#define ROWS	12

#define DRAWTEXT	gprintxy(2,(373+(textheight("A") * ROWS+1)),pc);

{

int ic;

int stringlength=0;

memset(pc,NULL,length);

while(1){

	ic = getkey();

	setcolor(BLACK);

	if(stringlength < length){

		strcat(pc, "_");

		DRAWTEXT;

		*(pc+stringlength) = NULL;

		}else

			DRAWTEXT;

	switch(ic){

		case ENTER:

			message(pc);

			return 0;

		case ESC:

			return 1;

		case BACKSPACE:

			if(stringlength>0) *(pc+(--stringlength))=NULL;

			break;

		default:

			if(isprint(ic) && stringlength <(length))

				*(pc+(stringlength++)) = ic;

		}//end switch

	setcolor(WHITE);

		if(stringlength < length){

		strcat(pc, "_");

		DRAWTEXT;

		*(pc+stringlength) = NULL;

		}else

			DRAWTEXT;

	}//end while

}