#include <graphics.h>

#include <string.h>

#include <STDARG.H>

#include <stdio.h>

#include <stdlib.h>

#include <conio.h>

#define TRUE   1

#define FALSE  0

#define MAXMENUS 13

#define IN 0

#define OUT 1

#define MENUWINDOW window(10,10,10,10)



extern void *buf[4];



extern void loadicons(void);

void longmessage(char *pc);

void gprintxy(int xloc,int yloc, char *fmt,...);

void message(char *pc);

void hilitemenu(int selection);

int DrawGUI(void);

void erasestr(int xloc,int yloc,char *str);

int initgraphics(void);

void drawbutt(struct rect_type rect, char inyoraudi);



struct rect_type{

	int left;

	int up;

	int right;

	int down;

	};

extern struct rect_type explorerect;

extern struct rect_type addrect;

extern struct rect_type killrect;

extern struct rect_type foodrect;

extern struct rect_type returnrect;

#define LENGTH 49

#define ROWS   12

void longmessage(char *pc)

{

char string[LENGTH];

int x,y,fixed=0,tfix=0,scrolls;

for(scrolls=0;;scrolls++){



	if(strlen((pc+(fixed))) < LENGTH){

		if(*(pc+fixed)!=' ')message(pc+fixed);

		else message(pc+fixed+1);

		return;

		}

	for(x=(LENGTH+fixed);*(pc+x) != ' ';x--);

	if(fixed>0) tfix= ++fixed;

	for(y=0;y<(x-(tfix));y++,fixed++)

		string[y] = *(pc+fixed);

	string[y] = NULL;

	message(string);

	}

}

void message(char *pc)

{

int x,col=0,row=0,fix=0;

static char screen[LENGTH][ROWS];

char buf[LENGTH+1];

setcolor(BLACK);

for(row=0;row<ROWS;row++){

		  for(x=0;x<LENGTH;x++)

			   buf[x]=screen[x][row];

		  buf[LENGTH] = NULL;

		  gprintxy(2,(373+(textheight("A") * row)),buf);

	 }//end for



for(x=0;x<(strlen(pc)/LENGTH + ((strlen(pc)%LENGTH) ? 1:0));x++)

	 for(row=0;row<(ROWS-1);row++){

		  for(col=0;col<LENGTH;col++){

			   screen[col][row]=screen[col][row+1];;

			   screen[col][row+1] = NULL;

		  }

	 }

row = ROWS-(strlen(pc)/LENGTH + ((strlen(pc)%LENGTH) ? 1:0));

col=0;

for(x=0;x<strlen(pc);x++){

	 if(col==LENGTH){ col=0; row++;}

	 screen[col][row] = (char)*(pc+(fix));

	 if(strlen(pc)==fix++) break;

	 col++;

	 }

	 setcolor(LIGHTGRAY);

	 for(row=0;row<ROWS;row++){

		  for(x=0;x<LENGTH;x++)

			   buf[x]=screen[x][row];

		  buf[LENGTH] = NULL;

		  gprintxy(2,(373+(textheight("A") * row)),buf);

	 }//end for

}

void hilitemenu(int selection)

{

char *menuname[MAXMENUS]={"Save Simulation",

									"Load Simulation",

									"Toggle Display",

									"Pop. Record On",

									"Pop. Record Off",

									"Config Simulation",

									"Graph Preferences",

									"Help",

									"Credits",

									"What is A-Life?",

									"Bibliography",

									"Return to Sim",

									"Quit"};

int x;

static int oldselection=22;

if(oldselection==selection) return;

settextstyle(TRIPLEX_FONT, HORIZ_DIR, 0);

setusercharsize(3,4,1,2);

if(oldselection==22){

setcolor(LIGHTRED);

	 for(x=0;x<MAXMENUS;x++)

		  {

		  gprintxy(405,250+(17* x),"%s",menuname[x]);

		  }

setcolor(RED);

	 for(x=0;x<MAXMENUS;x++)

		  {

		  gprintxy(406,251+(17* x),"%s",menuname[x]);

		  }

}

else{

	setcolor(LIGHTRED);

	gprintxy(405,250+(17* oldselection),"%s",menuname[oldselection]);

	setcolor(RED);

	gprintxy(406,251+(17* oldselection),"%s",menuname[oldselection]);



	}



setcolor(BLUE);

gprintxy(405,250+(17* selection),"%s",menuname[selection]);

setcolor(LIGHTBLUE);

gprintxy(406,251+(17* selection),"%s",menuname[selection]);

oldselection = selection;

settextstyle(DEFAULT_FONT, HORIZ_DIR, 0);

}

#define ELE	5

//#define WHITE	15

//#define DARKGRAY	CYAN

//#define LIGHTGRAY LIGHTCYAN

void drawbutt(struct rect_type rect, char inyoraudi)

{

int x;

setcolor(BLACK);

for(x=0;x<ELE;x++) rectangle(rect.left+x,rect.up+x,rect.right-x,rect.down-x);

setcolor(WHITE);

rectangle(rect.left,rect.up,rect.right,rect.down);

rectangle(rect.left+ELE,rect.up+ELE,rect.right-ELE, rect.down-ELE);

line(rect.left,rect.down,rect.left+ELE, rect.down-ELE);

line(rect.right,rect.up, rect.right-ELE,rect.up+ELE);

if(inyoraudi==OUT){

	setfillstyle(SOLID_FILL,WHITE);

	floodfill(((rect.right-rect.left)/2)+rect.left,rect.up+2, WHITE);

	floodfill(rect.left+2,((rect.down-rect.up)/2)+rect.up,WHITE);

	setfillstyle(SOLID_FILL,DARKGRAY);

	floodfill(rect.right-2,((rect.down-rect.up)/2)+rect.up,WHITE);

	floodfill(((rect.right-rect.left)/2)+rect.left,rect.down-2, WHITE);

	}



if(inyoraudi==IN){

	setfillstyle(SOLID_FILL,DARKGRAY);

	floodfill(((rect.right-rect.left)/2)+rect.left,rect.up+2, WHITE);

	floodfill(rect.left+2,((rect.down-rect.up)/2)+rect.up,WHITE);

	setfillstyle(SOLID_FILL,WHITE);

	floodfill(rect.right-2,((rect.down-rect.up)/2)+rect.up,WHITE);

	floodfill(((rect.right-rect.left)/2)+rect.left,rect.down-2, WHITE);

	}

setcolor(BLACK);

rectangle(rect.left,rect.up,rect.right,rect.down);

setcolor(WHITE);

setfillstyle(SOLID_FILL,LIGHTGRAY);

floodfill(((rect.right-rect.left)/2)+rect.left,((rect.down-rect.up)/2)+rect.up, WHITE);

if(inyoraudi==IN){

	 setcolor(DARKGRAY);

	 moveto(rect.right-ELE-1,rect.up+ELE);

	 lineto(rect.left+ELE,rect.up+ELE);

	 lineto(rect.left+ELE,rect.down-ELE-1);

	 }

else{

	setcolor(DARKGRAY);

	 moveto(rect.right-ELE,rect.up+ELE+1);

	 lineto(rect.right-ELE,rect.down-ELE);

	 lineto(rect.left+ELE+1,rect.down-ELE);

	}

putimage(explorerect.left+5, explorerect.up+5,buf[3],COPY_PUT);

putimage(addrect.left+5, addrect.up+5,buf[1],COPY_PUT);

putimage(killrect.left+5, killrect.up+5,buf[2],COPY_PUT);

putimage(foodrect.left+5, foodrect.up+5,buf[0],COPY_PUT);

settextstyle(TRIPLEX_FONT, HORIZ_DIR, 0);

setusercharsize(2,3,1,2);

setcolor(LIGHTRED);

outtextxy(returnrect.left+7, returnrect.up+5, "Return to Simulation");

setcolor(RED);

outtextxy(returnrect.left+8, returnrect.up+6, "Return to Simulation");

settextstyle(DEFAULT_FONT, HORIZ_DIR, 0);

}

#define LIGHTGRAY 7

#define WHITE 15

#define DARKGRAY 8

int DrawGUI(void)

{



cleardevice();

rectangle(0,0,401,351); //simulation window

rectangle(401,0,639,200);          //status\graph window

rectangle(401,250,639,479);        //menu window

rectangle(0,351,401,371);          //info window

rectangle(0,371,401,479);          //text window

setcolor(BLACK);

rectangle(402,200,638,250);

setcolor(WHITE);

loadicons();

drawbutt(explorerect,IN);        //explore icon    each box is 58*50

drawbutt(addrect,OUT);     //add bugs icon

drawbutt(killrect,OUT);        //kill bugs icon

drawbutt(foodrect,OUT);        //add food/kill food icon

drawbutt(returnrect,OUT);

//return restore_screen("GUI.bgi");

setcolor(WHITE);

line(639,199,639,251);

hilitemenu(1);

return 0;

}





void erasestr(int xloc,int yloc,char *str)

{

	 struct textsettingstype textinfo;

     int xdim,ydim;

     void *textimage;

     gettextsettings(&textinfo);

	  switch(textinfo.direction){

          case HORIZ_DIR: xdim = textwidth(str);

										ydim = textheight(str);

										xloc--;break;

          case VERT_DIR: ydim = textwidth(str);

                              xdim = textheight(str);

										yloc++;break;

          }

     switch(textinfo.horiz){

			 case LEFT_TEXT:                         break;

          case CENTER_TEXT: xloc-=xdim/2;    break;

          case RIGHT_TEXT:  xloc-=xdim; break;

          }

	  switch(textinfo.vert){

          case BOTTOM_TEXT: yloc-=ydim; break;

          case CENTER_TEXT: yloc-=ydim/2;    break;

          case TOP_TEXT:                     break;

          }

	  while(xloc<0){xloc++;ydim--;}

	  while(yloc<0){yloc++;ydim--;}

	 textimage = (void *)malloc((size_t)imagesize(xloc,yloc,xdim,ydim));

     getimage(xloc,yloc,xloc+xdim,yloc+ydim,textimage);

     putimage(xloc,yloc,textimage, XOR_PUT);

	 free(textimage);

}



void gprintxy(int xloc,int yloc, char *fmt,...)

{

     va_list argptr;

     char str[140];

     struct textsettingstype textinfo;

	  va_start(argptr,fmt);

	 vsprintf(str,fmt,argptr);

     va_end(argptr);

     gettextsettings(&textinfo);

     //erasestr(xloc,yloc,str);

	  outtextxy(xloc,yloc,str);

}

int initgraphics()

{

	int gdriver = DETECT, gtool, errorcode,x;

	for(x=0;x<3;x++){

		if(x==0)errorcode = registerfarbgidriver(EGAVGA_driver_far);

		if(x==1)errorcode = registerfarbgifont(triplex_font_far);

		if(x==2)errorcode = registerfarbgifont(sansserif_font_far);

		if (errorcode < 0){

			printf("Graphics error: %s\n", grapherrormsg(errorcode));

			return TRUE;

			}

		}

	initgraph(&gdriver, &gtool, "");



	errorcode = graphresult();

	if (errorcode != grOk)  /* an error occurred */

	{

	printf("Graphics error: %s\n", grapherrormsg(errorcode));

	return TRUE;

	}

	return FALSE;

}