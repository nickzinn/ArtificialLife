#include <graphics.h>

#include <stdlib.h>

#include <stdio.h>

#include <conio.h>

#include <string.h>

#include <ctype.h>

#include <bios.h>

#include <PROCESS.H>

#include <alloc.h>



#define PAUSE 	printf("\n<<<<<Enter any key to continue>>>>>");getch(); puts("");

#define DISPLAY(text)	cprintf("%s\n\r",text)

#define isevent	(kbhit() || isbuttonpressed())



#define VERSION 	".5a"

#define TRUE 		1

#define FALSE 		0



#define EXPLORE		TRUE

#define ADD			2

#define KILL		3

#define FOOD		4



#define MEMON		1



#define TOP			(struct bug_type *)NULL

#define BOTTOM		(struct bug_type *)NULL

#define IN          0

#define OUT         1

#define	SAVE		0

#define LOAD		1

#define TOGGLE		2

#define RECORDON	3

#define	RECORDOFF	4

#define CONFIG		5

#define GRAPHPREF	6

#define	HELP		7

#define CREDITS		8

#define WHATIS		9

#define BIBLIO		10

#define RETURNTOSIM	11

#define QUIT		12



#define BLANK		BLACK



#define GRAPHSIZE	209

#define MAXX 		400

#define MAXY 		350

#define MAX_BUGS 	700

#define STATUS		TRUE

#define GRAPH		FALSE

#define EDIT		TRUE+1

#define RECORD	       	TRUE+2

#define LAST_MOVEMENT_GENE 	8



#define GENOME_SIZE 12

/**** NUMBER IN GENOME ****/

	#define GENOME_HARDRIGHT        0

	#define	GENOME_RIGHT            1

	#define	GENOME_EASYRIGHT        2

	#define	GENOME_FORWARD          3

	#define	GENOME_EASYLEFT         4

	#define	GENOME_LEFT             5

	#define	GENOME_HARDLEFT         6

	#define	GENOME_REVERSE          7

	#define	GENOME_MAX_ENERGY       8

	#define GENOME_AGE_REPRODUCE		9

	#define	GENOME_STRENGTH         10

	#define	GENOME_MUTATION_RATE    11

	/****  TURN DEGREES   ***/

	#define HARDRIGHT	-135

	#define	RIGHT           -90

	#define	EASYRIGHT       -45

	#define	FORWARD         0

	#define	EASYLEFT        45

	#define	LEFT            90

	#define	HARDLEFT        135

	#define	REVERSE         180

//Data Types

struct rect_type{

	int left;

	int up;

	int right;

	int down;

	};

struct bug_type{

	int genome[GENOME_SIZE];

	int x,y;

	int energy;

	int direction;

	int age;

	int children;

	struct bug_type *nextbug;

	struct bug_type *previousbug;

	};



struct enviroment_globals{

	int STARTING_BUGS;

	int STARTING_FOOD;

	int NEW_FOOD_RATE;

	int INITIAL_BUG_NRG;

	int BUG_COLOR;

	int FOOD_COLOR;

	int FOOD_VALUE;

	int BUG_VALUE;

	int MAX_HERBIVOR_STRENGTH;

	int MIN_CARNIVOR_STRENGTH;

	int FOOD_RADIUS;

	};

#ifdef EVOSIM3



#endif

/***** globals *****/

#ifdef EVO-MAIN

FILE *fp;

int gdone, gpopulation;

long int gtimesteps=0;

char gfilepath[30],gspeed=1,gpause=FALSE, gtape=FALSE,gdisplay=STATUS,

	gtool = EXPLORE;

int graphpos;

int far graph[GRAPHSIZE];

struct bug_type *firstbug, *currentdisplay;

char far *food;

struct enviroment_globals sys={100,1900,15,500,WHITE,GREEN,10,10,10,20,2};

void *buf[4];

char *help = {"This is the help text. Isn't it very helpful it is the most helpful text ever.  Thank you for trying me!"};

char *credits={"Evosim, the evolution simulator.  Program design and Implementation by Nick Zinn.  Aesthetic design by Uri Davillier  Thanks to Scott Smith, David Devore and University School.  Project sponsored by Strnad Fellowship and my family."};

char *whatis={"A-Life is the...."};

char *biblio={"These books are helpful in...."};

char *simulationhelp={"The simulation is running right now. To stop the simulation, hit a key or hold down the mouse button."};

struct rect_type explorerect 	=	{402,200,460,250};

struct rect_type addrect 		=	{461,200,519,250};

struct rect_type killrect 		=	{520,200,578,250};

struct rect_type foodrect 		=   {579,200,637,250};

struct rect_type simulationrect = 	{1,1,MAXX,MAXY};

struct rect_type returnrect 	=  {402,165,637,198};

struct rect_type drawrect		=   {6,6,MAXX-5,MAXY-5};

struct rect_type menurect		=	{401,250,639,479};

#endif





#ifndef EVO-MAIN

extern FILE *fp;

extern int gdone, gpopulation;

extern long int gtimesteps;

extern char gfilepath[30], gpause, gtape, gtool,gdisplay;

extern struct bug_type *firstbug, *currentdisplay;

extern unsigned char far *food;

extern struct enviroment_globals sys;

#endif

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



