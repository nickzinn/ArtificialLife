/*********************************************************/

/********************  EVO-MAIN.c ************************/

/*********** Programmed in Turbo C++ 3.0 *****************/

/***      The userinterface, data and function main    ***/

/***  for the evosim simulator, are contained whithin  ***/

/***  this code.  Calls to main evosim operations      ***/

/***  are made to evosim3.c.                           ***/

/***  All global data resides whithin this module.     ***/

/*********************************************************/

/*********************************************************/

#define   EVO-MAIN 1

#include "evosim3.h"

#include "evosim.p"



void initstatus(void);



int checkcomp(void)

{

//does computer have vga display?



//does computer have a mouse?



//does computer have enough memory?



return 0;

}

/************** Init Simulation **************/

int initsimulation(void)

{

int d,x;

struct bug_type *currentbug;

if((firstbug = (struct bug_type *)malloc(sizeof(struct bug_type))) == (struct bug_type *)NULL)

	exiterror("Shit");

#ifdef MEMON

message("Welcome to EvoSim");

message("Generating Bugs....");

	for(d=0;d<LAST_MOVEMENT_GENE;d++)

		firstbug->genome[d] = 1;

	firstbug->age = 0;

	firstbug->genome[GENOME_FORWARD] = 1;

	firstbug->genome[GENOME_MAX_ENERGY] = 1000;

	firstbug->genome[GENOME_STRENGTH] = 10;

	firstbug->genome[GENOME_MUTATION_RATE] = 99;

	firstbug->genome[GENOME_AGE_REPRODUCE] = 400;

	firstbug->x=  1;

	firstbug->y=  1;

	firstbug->children =0;

	firstbug->energy = sys.INITIAL_BUG_NRG;

	firstbug->direction = 0;

	firstbug->nextbug = BOTTOM;

	firstbug->previousbug = TOP;

	for(x=0;x<sys.STARTING_BUGS;x++){

		(struct bug_type *)currentbug = (struct bug_type *)insertbug((struct bug_type *)firstbug);

		currentbug->x = x+2;

		currentbug->y = x+2;

		}

#endif

message("Generating food....");

for(x=0;x<sys.STARTING_FOOD;x++,makefood());

drawbugs();

initstatus();

currentdisplay = firstbug;

display();

longmessage(simulationhelp);

for(x=0;x<GRAPHSIZE;graph[x++] = 0);

graphpos=0;

return 0;

}

void loadicons(void)

{

FILE *fp;

int x;

unsigned long size;

char *iconfile[4] = {"food.icn",

							"add.icn",

							"kill.icn",

							"explore.icn"};

size = imagesize(1,1,58,50);

for(x=0; x<4; x++){

	if ((buf[x] = (void  *)malloc((size_t)size)) == NULL)

		{

		closegraph();

		printf("Error: not enough heap space in save_screen().\n");

		printf("Memory request: %u",size);

		getch();

		exit(1);

		}

	if((fp=fopen(iconfile[x],"rb")) == NULL) exiterror("Can't find icn file(s)");

	fread((void *)buf[x], size, 1, fp);

	fclose(fp);

	}

}

void exiterror(char *string)

{

closegraph();

DISPLAY("\n\rAbnormal system termination");

cprintf("Error string: %s\n\rgpopulation:%d\n\rgtimesteps:%ld\n\r", string,gpopulation,gtimesteps);

cprintf("Check your setup, check manual, report error to Nick Zinn\n\r");

exit(EXIT_FAILURE);

}





void systemshutdown(void)

{

struct bug_type *current;

int xcord,ycord,xcord2,ycord2,color;

double x;

cleardevice();

settextstyle(1,0,0);

setusercharsize(2,2,2,2);

setcolor(RED);

outtextxy(0,0,"System going down...");

#define CYCLES 1000

for(x=0;x<CYCLES;x++){

	xcord = random(getmaxx()-350)+350;

	ycord = random(getmaxy());

	xcord2 = random(getmaxx());

	ycord2 = random(getmaxy()-50)+50;

	color = random(getmaxcolor())+1;

	setcolor(color);

	line(xcord,ycord,xcord2,ycord2);

	}

#ifdef MEMON

current=firstbug->nextbug;

while(TRUE){

	free(current->previousbug);

	current=current->nextbug;

		if(current == BOTTOM)

			break;

	}

free(current);

free(buf[0]);

free(buf[1]);

free(buf[2]);

free(buf[3]);

#endif

//close all files

closegraph();

}



void save(void)

{

FILE *fp;

struct bug_type *current;

char filename[10];

message("Please enter file name to save simulation");

message("_________");

getfixed(filename, 9);

if((fp = fopen(filename, "wb"))==NULL)

	message("File Create Error");

else {

	current=firstbug;

	while(TRUE){

			fwrite(current,sizeof(struct bug_type),1,fp);

			current=current->nextbug;

			if(current == BOTTOM){

			  fwrite(current,sizeof(struct bug_type),1,fp);

				break;

			  }

			}

	fclose(fp);

	}

}

void load(void)

{

FILE *fp;

struct bug_type *current;

char filename[10];

message("Please enter file to load");

message("_________");

getfixed(filename, 9);

if((fp = fopen(filename, "rb"))==NULL)

	message("File load Error");

else {

	//kill all currentbugs

	current=firstbug;

		do current=current->nextbug;

			while(deletebug(current->previousbug)!=NULL);

	//allocate memory for swap bug

	if((current = (struct bug_type *)malloc(sizeof(struct bug_type))) == (struct bug_type *)NULL)

		exiterror("Not enough memory");

	//load new bugs

	while(!feof(fp)){

			fread((void *)current,sizeof(struct bug_type),1,fp);

			insertbug(current);

			}

	deletebug(firstbug);

	fclose(fp);

	}

}

void graphit(void)

{

//Draw graph array with scale factor

static int oldpop;

static float xoldscale=0, yoldscale=0;

int y, x,maxpop=0, starttime;

float xscale, yscale;

for(x=0; x<GRAPHSIZE;x++)

	if(graph[x]>maxpop)

		maxpop=graph[x];

maxpop=((maxpop+100)/100)*100;

xscale=1.0;

yscale= 140.0/(float)maxpop;

//if(yscale!=yoldscale){

	//setfillstyle(SOLID_FILL, BLACK);

	//setcolor(BLACK);

	//bar(421,2,637,148);

	//setcolor(WHITE);

//	}

for(y=graphpos,x=GRAPHSIZE;y<=GRAPHSIZE-1;x--,y++){

	putpixel(630-(int)((float)x*xoldscale),(int)(149.0-((float)graph[y]*yoldscale)), BLACK);

	putpixel(630-(int)((float)x*xscale),(int)(149.0-((float)graph[y+1]*yscale)), RED);

	}

for(y=0,x=graphpos;y<(graphpos-1);x--,y++){

	putpixel(630-(int)((float)x*xoldscale),(int)(149.0-((float)graph[y]*yoldscale)), BLACK);

	putpixel(630-(int)((float)x*xscale),(int)(149.0-((float)graph[y+1]*yscale)), RED);

	}

//if(graphpos == GRAPHSIZE)

//	graphpos=0;

graph[graphpos++] = gpopulation;

if(graphpos == GRAPHSIZE)

	graphpos=0;

xoldscale = xscale;

yoldscale = yscale;

settextstyle(0,1,1);

settextjustify(2,0);

setcolor(BLACK);

gprintxy(415,142,"%d",oldpop);

setcolor(WHITE);

gprintxy(415,142,"%d",gpopulation);

settextstyle(0,0, 0);

setcolor(BLACK);

settextjustify(0,2);

gprintxy(425,155,"%d",gtimesteps-10);

setcolor(WHITE);

gprintxy(425,155,"%d",gtimesteps);

oldpop=gpopulation;

}

void initgraphing(void)

{

//clear status space and draw graph frame

setfillstyle(SOLID_FILL, BLACK);

setcolor(BLACK);

bar(402,1,returnrect.right-1,returnrect.up-1);

setcolor(WHITE);

//x-axis

line(415,150,630,150);

//for(int x=415;x<=630;x==

//y-axis

line(420,10,420,155);

settextstyle(0,1,1);

outtextxy(415,10,"Population");

settextstyle(0,0, 0);

outtextxy(600,155,"Time");

}

void status(void)

{

int line,off,x=0;

static int rate=0,oldpop;

static float oldrate;

static long int oldsteps = 0;

  if(gdisplay == GRAPH){

	graphit();

	return;

	}

//if(graphpos == GRAPHSIZE)

	//graphpos=0;

graph[graphpos++] = gpopulation;

if(graphpos == GRAPHSIZE)

	graphpos=0;

	line = textheight("A") +1;

	off  = textwidth("Population : ")+404;

	setcolor(BLACK);

	gprintxy(off,3+((x++)*line),"%d",oldsteps);

	gprintxy(off,3+((x++)*line),"%d",oldpop);

	gprintxy(off,3+((x++)*line),"%f%",oldrate);

	gprintxy(off,3+((x++)*line),"%d",oldpop);

	gprintxy(off,3+((x++)*line),"%d",oldpop);

	gprintxy(off,3+((x++)*line),"%d",oldpop);

	gprintxy(off,3+((x++)*line),"%d",oldpop);

	setcolor(WHITE);

	x=0;

	gprintxy(off,3+((x++)*line),"%d",oldsteps=gtimesteps);

	gprintxy(off,3+((x++)*line),"%d",oldpop=gpopulation);

	gprintxy(off,3+((x++)*line),"%f%",(oldrate=( ( ((float)rate/(float)gpopulation) - 1.0) *100.0)));

	gprintxy(off,3+((x++)*line),"%d",gpopulation);

	gprintxy(off,3+((x++)*line),"%d",gpopulation);

	gprintxy(off,3+((x++)*line),"%d",gpopulation);

	gprintxy(off,3+((x++)*line),"%d",gpopulation);

	if(!(gpopulation % 100)) rate =gpopulation;



}



void initstatus(void)

{

int line,x=0;



//clear status space and draw graph frame

setfillstyle(SOLID_FILL, BLACK);

setcolor(BLACK);

bar(402,1,returnrect.right-1,returnrect.up-1);

setcolor(WHITE);

line = textheight("A")+1;

setcolor(RED);

	gprintxy(404,3+((x++)*line),"Time Steps :");

	gprintxy(404,3+((x++)*line),"Population :");

	gprintxy(404,3+((x++)*line),"Growth Rate:");

	gprintxy(404,3+((x++)*line),"Carnivours :");

	gprintxy(404,3+((x++)*line),"Herbivours :");

	gprintxy(404,3+((x++)*line),"Average Age:");

	gprintxy(404,3+((x++)*line),"Elvis      :");

}



void recordon(void)

{

}

void recordoff(void)

{

}

void edit_enviroment(void)

{

}

void graphprefs(void)

{



}

void executemenu( int selection)

{

switch(selection){

	case SAVE:

		save();

		break;

	case LOAD:

		load();

		break;

	case TOGGLE:

		if(gdisplay==GRAPH){

			gdisplay=STATUS;

			initstatus();

			}

		else {

			gdisplay= GRAPH;

			initgraphing();

			}

		break;

	case RECORDON:

		recordon();

		break;

	case RECORDOFF:

		recordoff();

		break;

	case CONFIG:

		edit_enviroment();

		break;

	case GRAPHPREF:

		graphprefs();

		break;

	case HELP:

		longmessage(help);

		break;

	case CREDITS:

		longmessage(credits);

		break;

	case WHATIS:

		longmessage(whatis);

		break;

	case BIBLIO:

		longmessage(biblio);

		break;

	case QUIT:

		gpause = FALSE;

		gdone = TRUE;

		break;

	case RETURNTOSIM:

		gpause = FALSE;

		break;

	}

}

void seticon(int oldtool)

{

if(oldtool == gtool) return;

mouseoff();

switch(gtool){

	case EXPLORE:

		drawbutt(explorerect,OUT);

		break;

	case ADD:

		drawbutt(addrect,OUT);

		break;

	case KILL:

		drawbutt(killrect,OUT);

		break;

	case FOOD:

		drawbutt(foodrect,OUT);

		break;

	}

switch(oldtool){

	case EXPLORE:

		drawbutt(explorerect,IN);

		break;

	case ADD:

		drawbutt(addrect,IN);

		break;

	case KILL:

		drawbutt(killrect,IN);

		break;

	case FOOD:

		drawbutt(foodrect,IN);

		break;

	}

mouseon();

}



void uinterface(void)

{

	struct bug_type *newbug;

	static  int selection =1;

	unsigned long d;

	int ic,x,y,xt;

	float i;

	message("ESC to return to simulation");

	if(isbuttonpressed());

		while(isbuttonpressed());

	if(kbhit()) getkey();

	mouseon();

	gpause=TRUE;

	while(gpause == TRUE){

		if(isbuttonpressed()){

			getmousexy(&x,&y);

			//message("click");

			//gprintxy(100,100,"%d,%d",x,y);

			if(isinside(x,y,explorerect)){

				if(gtool != EXPLORE){

					seticon(EXPLORE);

					message("Tool Switched to Explore");

					gtool = EXPLORE;

					}

				}

			if(isinside(x,y,addrect)){

				if(gtool != ADD){

					seticon(ADD);

					gtool = ADD;

					message("Tool Switched to Add Bugs");

					}

				}

			if(isinside(x,y,killrect)){

				if(gtool != KILL){

					seticon(KILL);

					message("Tool Switched to Kill Bugs");

					gtool = KILL;

					}

				}

			if(isinside(x,y,foodrect)){

				seticon(FOOD);

				if(gtool!= FOOD){

					message("Tool Switched to Add/Remove Food");

					message("Left mouse button to add food, right to remove");

					}

				gtool = FOOD;

				}

			if(isinside(x,y,simulationrect))

				switch(gtool){

					case EXPLORE:

						mouseoff();

						if(findbug(x,y)!= (struct bug_type *)NULL)

							currentdisplay = findbug(x,y);

						display();

						drawbugs();

						mouseon();

						break;

					case ADD:

						mouseoff();

						if(findbug(x,y)== (struct bug_type *)NULL){

							newbug = insertbug(currentdisplay);

							newbug->x=x;

							newbug->y=y;

							currentdisplay = newbug;

							drawbugs();

                            }

						mouseon();

						break;

					case KILL:

						mouseoff();

						for(xt=0;xt<sys.FOOD_RADIUS*gspeed*gspeed;xt++)

						if((newbug =findbug(x+(random(gspeed)-(gspeed/2)),y+(random(gspeed)-(gspeed/2))))!= (struct bug_type *)NULL)

							deletebug(newbug);

						mouseon();

						break;

					case FOOD:

						if(isinside(x,y,drawrect)){

						mouseoff();

						for(xt=0;xt<sys.FOOD_RADIUS*gspeed*gspeed;xt++){

						if(isbuttonpressed()==1)putpixel(x+(random(10)-5),y+(random(10)-5),sys.FOOD_COLOR);

						if(isbuttonpressed()==2)putpixel(x+(random(10)-5),y+(random(10)-5),BLACK);

						}

						drawbugs();

						mouseon();

						//putpixel(x+(random(10)-5),y+(random(10)-5),sys.FOOD_COLOR);

						}

						break;

					}

			if(isinside(x,y,menurect)){

				i =((float)(menurect.up-y)/((float)(menurect.up-menurect.down)/13.0));

				if ((int)i <13 && (int)i>=0) selection = (int)i;

				mouseoff();

				hilitemenu(selection);

				mouseon();

				d=0;

				while(isbuttonpressed()==2)d++;

				if(d >5) executemenu(selection);



				}

			if(isinside(x,y,returnrect)){

				gpause=FALSE;

				mouseoff();

				drawbutt(returnrect, IN);

				if(isbuttonpressed());

					while(isbuttonpressed());

				drawbutt(returnrect,OUT);

				mouseon();

				}

			}//end mouse

		if(kbhit()){

			getmousexy(&x,&y);

			if(isinside(x,y,menurect))

				mouseoff();

			ic = getkey();

			switch(ic){

				case UPARROW:

					if(selection>0)selection--;

					hilitemenu(selection);

					break;

				case DOWNARROW:

					if(selection<12) selection++;

					hilitemenu(selection);

					break;

				case ESC:

					gpause = FALSE;

					break;

				case END:

					gpause = FALSE;

					gdone = 	TRUE;

					break;

				case ENTER:

					mouseoff();

					executemenu(selection);

					mouseon();

					break;

				default:

						if(isdigit(ic))

							gspeed = ic-'0';



				}//end switch

			mouseon();

			}//end kbhit



		}//end loop

mouseoff();

}

void display(void)

{

static struct bug_type oldbug,*poldbug;

poldbug = &oldbug;

setcolor(BLACK);

gprintxy(1,353," %3d %3d      %4d     %6d     %3d          %3d",oldbug.x,oldbug.y,oldbug.energy, oldbug.age,oldbug.direction, oldbug.children);

if(memcmp(poldbug,currentdisplay , sizeof(int)*GENOME_SIZE) != 0)gprintxy(1,361,"{%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d}",oldbug.genome[0],oldbug.genome[1],oldbug.genome[2],oldbug.genome[3],oldbug.genome[4],oldbug.genome[5],oldbug.genome[6],oldbug.genome[7],oldbug.genome[8],oldbug.genome[9],oldbug.genome[10],oldbug.genome[11], oldbug.genome[12]);

putpixel(currentdisplay->x,currentdisplay->y,LIGHTRED);

setcolor(WHITE);

if(currentdisplay!=(struct bug_type *)NULL){ gprintxy(1,353,"(%3d,%3d) NRG:%4d AGE:%6d DIR:%3d CHILDREN:%3d",currentdisplay->x,currentdisplay->y,currentdisplay->energy,currentdisplay->age,currentdisplay->direction,currentdisplay->children);

gprintxy(1,361,"{%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d}",currentdisplay->genome[0],currentdisplay->genome[1],currentdisplay->genome[2],currentdisplay->genome[3],currentdisplay->genome[4],currentdisplay->genome[5],currentdisplay->genome[6],currentdisplay->genome[7],currentdisplay->genome[8],currentdisplay->genome[9],currentdisplay->genome[10],currentdisplay->genome[11],currentdisplay->genome[12]);}

memcpy(poldbug,currentdisplay,sizeof(struct bug_type));

}

void main(void)

{

cprintf("Evosim, by Nick Zinn  Version %s\n\r Compiled: %s, %s\n\r", VERSION,__TIME__,__DATE__);

cprintf("File: %s\n\rCompiled in Turbo C++ %d\n\r",__FILE__, __TURBOC__);

PAUSE;

if(initgraphics()) 	// init VGA Display

	exiterror("Graphics Driver Error");

if(checkcomp())	//Does computer have VGA display?  Mouse? and enough memory-

	exiterror("Incompatible computer type"); // are all needed files availible

if(initmouse())

	exiterror("Mouse error");

if(DrawGUI())

	exiterror("Could not draw Graphical User Interface");

if(initsimulation())	//allocate memory, starting variables

	exiterror("Simulation Initilization Error");



while(gdone==FALSE){

	while(!isevent){

			#ifdef MEMON

			mainloop();

			mainloop();

			mainloop();

			mainloop();

			mainloop();

			mainloop();

			mainloop();

			mainloop();

			mainloop();

			mainloop();

			#endif

			gtimesteps+=10;

			status();

			display();

		}

	uinterface();

	}

systemshutdown();

}







