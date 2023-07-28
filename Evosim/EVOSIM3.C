/*********************************************************/

/********************  EVOSIM3.c *************************/

/***      This code contains the heart of the evosim   ***/

/***  simulator.  It is a secondary file to evo-main.c ***/

/***  which contains the user interface and auxillury  ***/

/***  functions.  All vaiables are declared in evo-main***/

/***  and are extern to this module.                   ***/

/*********************************************************/

/*********************************************************/





#define EVOSIM3	1

#include "evosim3.h"

void movebug(struct bug_type *currentbug);

void makefood (void);

void mutate(struct bug_type *bug);

struct bug_type *insertbug(struct bug_type *bugbasedon);

int deletebug(struct bug_type *deadbug);

struct bug_type *findbug(int x,int y);

struct bug_type *checkbug(struct bug_type *currentbug);

void drawbugs (void);

extern void exiterror(char *string);



struct bug_type *insertbug(struct bug_type *bugbasedon)

{

struct bug_type *newbug;



if((newbug = (struct bug_type *)malloc(sizeof(struct bug_type))) == (struct bug_type *)NULL)

	exiterror("Not enough memory in function insertbug");



memcpy(newbug,bugbasedon, sizeof(struct bug_type));



newbug->previousbug = TOP;

firstbug->previousbug=newbug;

newbug->nextbug=firstbug;

firstbug = newbug;

newbug->age = 0;

newbug->children =0;

return (struct bug_type *)newbug;

}



int deletebug(struct bug_type *deadbug)

{

struct bug_type *previousbug,*nextbug;

if(deadbug == BOTTOM || deadbug == TOP)

	return NULL;

if(deadbug->nextbug == BOTTOM && deadbug->previousbug == TOP)

	return NULL;

previousbug = deadbug->previousbug;

nextbug = deadbug->nextbug;

if(previousbug!=TOP)

	previousbug->nextbug=nextbug;

else

	nextbug->previousbug = TOP;

if(nextbug != BOTTOM)

	nextbug->previousbug = previousbug;

else

	previousbug->nextbug =BOTTOM;

putpixel(deadbug->x,deadbug->y,BLACK);

if(firstbug == deadbug)

	firstbug = nextbug;

if(currentdisplay ==deadbug) currentdisplay = firstbug;

free(deadbug);

return 1;

}



struct bug_type *findbug(int x,int y)

{

struct bug_type *currentbug;

currentbug=firstbug;



while(TRUE){

	if(currentbug->x == x && currentbug->y ==y)

		return currentbug;

	if(currentbug->nextbug == BOTTOM)

		return (struct bug_type *)NULL;

	currentbug=currentbug->nextbug;

	}



}

struct bug_type *checkbug(struct bug_type *currentbug)

{

struct bug_type *newbug;

/*** check to see  if bug is alive, if not turn to food ***/

	if(currentbug->energy <= 0){

		/*make food*/

		putpixel(currentbug->x,currentbug->y,sys.FOOD_COLOR);

		newbug = currentbug->nextbug;

		deletebug(currentbug);

		return newbug;

		}

/** check to see if energy = MAX_ENERGY for reproduction**/

	if(currentbug->energy >= currentbug->genome[GENOME_MAX_ENERGY] && currentbug->age > currentbug->genome[GENOME_AGE_REPRODUCE]){

	/*** newbug ***/

		newbug = insertbug(currentbug);

		mutate(newbug);

		newbug->energy = currentbug->genome[GENOME_MAX_ENERGY]/2;

		currentbug->energy =currentbug->genome[GENOME_MAX_ENERGY]/2;

		currentbug->children++;

		/* move new bug*/

		newbug->x = currentbug->x;

		newbug->y = currentbug->y;

		movebug(newbug);

		return currentbug->nextbug;

	}

return currentbug->nextbug;

}







void movebug(struct bug_type *currentbug)

{

register int x,n;

	int sum,run_sum, nextx, nexty;

/*** get next movement ***/

	run_sum = 0;

	sum = 0;

	for(x = 0;x<LAST_MOVEMENT_GENE;x++)

		sum = sum + currentbug->genome[x];

	n = random(sum);





	while(TRUE){

		/***  Hard Right ***/

		run_sum = currentbug->genome[GENOME_HARDRIGHT];

		if(n<=run_sum){

			currentbug->direction = currentbug->direction + HARDRIGHT;

			break;

			}



		/*** Right ***/

		run_sum = run_sum + currentbug->genome[GENOME_RIGHT];

		if(n<=run_sum){

			currentbug->direction = currentbug->direction + RIGHT;

			break;

			}



		/*** Easy Right ***/

		run_sum = run_sum +currentbug->genome[GENOME_EASYRIGHT];

		if(n<=run_sum){

			currentbug->direction = currentbug->direction + EASYRIGHT;

			break;

			}







		/*** Easyleft ***/

		run_sum = run_sum + currentbug->genome[GENOME_EASYLEFT];

		if(n<=run_sum){

			currentbug->direction =currentbug->direction + EASYLEFT;

			break;

			}



		/*** left ***/

		run_sum = run_sum + currentbug->genome[GENOME_LEFT];

		if(n<=run_sum){

			currentbug->direction = currentbug->direction + LEFT;

			break;

			}



		/*** Right ***/

		run_sum = run_sum + currentbug->genome[GENOME_RIGHT];

		if(n<=run_sum){

			currentbug->direction = currentbug->direction + RIGHT;

			break;

			}



		/*** Hard Right ***/

		run_sum = run_sum + currentbug->genome[GENOME_HARDRIGHT];

		if(n<=run_sum){

			currentbug->direction = currentbug->direction + HARDRIGHT;

			break;

			}



		/*** Reverse ***/

		run_sum = run_sum + currentbug->genome[GENOME_REVERSE];

		if(n<=run_sum){

			currentbug->direction = currentbug->direction + REVERSE;

			break;

			}

		/*** Forward ***/

			/** Direction stays the same**/

			break;





	}/*** end while***/

	if(currentbug->direction>=360)

		currentbug->direction = currentbug->direction -360;

	if(currentbug->direction<0)

		currentbug->direction = currentbug->direction +360;

	nextx= currentbug->x;

	nexty= currentbug->y;

	switch(currentbug->direction){

		case 0:

			nextx++;

			break;

		case 45:

			nextx++;

			nexty++;

			break;

		case 90:

			nexty++;

			break;

		case 135:

			nexty++;

			nextx--;

			break;

		case 180:

			nextx--;

			break;

		case 225:

			nextx--;

			nexty--;

			break;

		case 270:

			nexty--;

			break;

		case 315:

			nextx++;

			nexty--;

			break;

		}/*end switch*/

/*** check to see if bug will hit the wall if so, screen wrap ***/

if(nextx==MAXX)

	nextx=1;

else if(nextx==1)

	nextx= MAXX-1;

if(nexty==MAXY)

	nexty=1;

else if(nexty==1)

	nexty= MAXY-1;

/*** check to see if another bug is there***/

	if(getpixel(nextx,nexty) == sys.BUG_COLOR){

		if(currentbug->genome[GENOME_STRENGTH]<=sys.MAX_HERBIVOR_STRENGTH){

			/*** recursive function until bug can move ***/

			movebug(currentbug);

			return;

			}

	/*** not done yet here ***/

	}/*end other bug*/

/*** check to see if food is there        ***/

	if(getpixel(nextx,nexty) == sys.FOOD_COLOR  && currentbug->genome[GENOME_STRENGTH] < sys.MIN_CARNIVOR_STRENGTH){

		currentbug->energy = currentbug->energy + sys.FOOD_VALUE;

	}

/*** move bug ***/

/* delete old bug***/

putpixel(currentbug->x,currentbug->y,BLANK);

currentbug->x = nextx;

currentbug->y = nexty;



}





void drawbugs (void)

{

struct bug_type *current;

(struct bug_type *)current=(struct bug_type *)firstbug;



while(TRUE){

		putpixel(current->x,current->y,sys.BUG_COLOR);

		if((struct bug_type *)current->nextbug == BOTTOM)

			break;

		(struct bug_type *)current=(struct bug_type *)current->nextbug;

	}

putpixel(currentdisplay->x,currentdisplay->y,LIGHTRED);

}



void makefood (void)

{

register int c,x,y;



	for(c=0;c<sys.NEW_FOOD_RATE;c++){

		/*** get random spot for food ***/

			x = random(MAXX-1)+1;

			y = random(MAXY-1)+1;

		/*** draw food ***/

		if(getpixel(x,y) == BLANK)

			putpixel(x,y,sys.FOOD_COLOR);

		}

}



void mutate(struct bug_type *bug)

{

int gene;

if( random(100)< bug->genome[GENOME_MUTATION_RATE]){

	gene = random(GENOME_SIZE);

	switch (gene){

		case GENOME_MAX_ENERGY:

			bug->genome[gene]+= (random(3)-1) *10;

			if(bug->genome[gene]<1) bug->genome[gene]=1;

			break;

		case GENOME_AGE_REPRODUCE:

			bug->genome[gene]+= (random(3)-1)*10;

			if(bug->genome[gene]<1) bug->genome[gene]=1;

			break;

		case GENOME_STRENGTH:

			bug->genome[gene]+= (random(3)-1);

			if(bug->genome[gene]<1) bug->genome[gene]=1;

			break;

		case GENOME_MUTATION_RATE:

			bug->genome[gene]+= (random(3)-1)*2;

			if(bug->genome[gene]<1) bug->genome[gene]=1;

			if(bug->genome[gene]>100) bug->genome[gene]=99;

			break;

		default:

			bug->genome[gene]+= random(3)-1;

			if(bug->genome[gene]==0) bug->genome[gene]=1;

			break;

		}

	}

}



void mainloop(void)

{

struct bug_type *current;

current=firstbug;



gpopulation =0;

	while(TRUE){

			current->energy--;

			current->age++;

			gpopulation++;

			movebug(current);

			current = checkbug(current);

			if(current == BOTTOM)

				break;

			}



	drawbugs();

	makefood();



}

