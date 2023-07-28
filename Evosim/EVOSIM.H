#include <graphics.h>

#include <stdlib.h>

#include <stdio.h>

#include <conio.h>

#include <string.h>

#include <ctype.h>

#include <PROCESS.H>





#define TRUE 		1

#define FALSE 		0

#define BLANK		BLACK

#define ESC	        27

#define BACKSPACE       8

#define UP              'w'

#define DOWNWARD        's'

#define LEFTWARD        'a'

#define RIGHTWARD       'd'

#define CONTINUE	'p'

#define DEAD 		-100

#define MAXX 		399

#define MAXY 		349

#define MAX_BUGS 	700

#define CREDITS		TRUE+1

#define HELP		TRUE

#define INFO		FALSE

#define SIMULATION	TRUE

#define GRAPH		FALSE

#define EDIT		TRUE+1

#define RECORD	       	TRUE+2

#define STARTING_BUGS	100

#define STARTING_FOOD	900

#define NEW_FOOD_RATE	15

#define INITIAL_BUG_NRG	500

#define BUG_COLOR	WHITE

#define FOOD_COLOR      GREEN

#define	FOOD_VALUE      20

#define	BUG_VALUE       10

#define LAST_MOVEMENT_GENE 	7

#define	MAX_HERBIVOR_STRENGTH 	10

#define	MIN_CARNIVOR_STRENGTH 	20

#define GENOME_SIZE 11

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

	#define GENOME_AGE_REPRODUCE	9

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

struct bug_type{

	int genome[GENOME_SIZE+1];

	int x,y;

	int energy;

	int direction;

	int age;

	int next;

	};

struct food_location{

	char bit[8]	:1;

	};



/***** globals *****/

#ifdef EVO-MAIN

FILE *fp;

int gdone, gpopulation;

long int gtimesteps=0;

char ginput[20]= {"\0"}, goutput[22]={"this is output"},

	gfilepath[30],gstatup=TRUE, gpause=FALSE, gtape=FALSE,

	gmode = SIMULATION;/*mode can be either graph mode(FALSE)

			or simulation mode (TRUE), or edit mode (TRUE+1)*/

struct bugs_type *bug[MAX_BUGS+1];

#endif



#ifdef EVOSIM3

extern FILE *fp;

extern int gdone, gpopulation;

extern long int gtimesteps=0;

extern char ginput[20]= {"\0"}, goutput[22]={"this is output"},

	gfilepath[30],gstatup=TRUE, gpause=FALSE, gtape=FALSE,

	gmode = SIMULATION;/*mode can be either graph mode(FALSE)

			or simulation mode (TRUE), or edit mode (TRUE+1)*/

extern struct bugs_type *bug[MAX_BUGS+1];

#endif

/***** prototypes *****/

void initprog(void);

void mainloop(void);

void GetEvent(void);

void HandleAction(void);

void initbugs(void);

void checkbug(int c);

void movebug(int c);

void drawbugs(void);

void makefood(void);

void initgraphics(void);

void mutate(int father, int daughter);

void Record(void);

void Variables(void);

void EditMode(void);

void EditEvent(void);

void DrawFrame(void);

void DrawStatus(void);

void DrawIndicator(void);

void DrawTextBox(char title[10],char text );

void DrawTitle(char title[15]);

