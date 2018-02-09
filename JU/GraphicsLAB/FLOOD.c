#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <stdlib.h>
#include <dos.h>
#include <graphics.h>
typedef struct{
	int x;
	int y;
}Point;

int initMainGraph(int cw1){
	int cwidth=cw1;
	int i;
	//request autodetection
	int gdriver=DETECT,gmode,errorcode;
	//initialize graphics mode
	initgraph(&gdriver,&gmode,"C:\\TC\\BGI");

	setlinestyle(SOLID_LINE,0,1);

	setcolor(WHITE);

	for(i=getmaxx()/2-cwidth;i>=0;i-=cwidth)
	line(i,0,i,getmaxy());
	for(i=getmaxx()/2+cwidth;i<=getmaxx();i+=cwidth)
	line(i,0,i,getmaxy());

	for(i=getmaxy()/2-cwidth;i>=0;i-=cwidth)
	line(0,i,getmaxx(),i);
	for(i=getmaxy()/2+cwidth;i<=getmaxy();i+=cwidth)
	line(0,i,getmaxx(),i);

	setcolor(13);
	line(getmaxx()/2,0,getmaxx()/2,getmaxy());
	line(0,getmaxy()/2,getmaxx(),getmaxy()/2);
	setcolor(WHITE);
	return 0;
}

int sign(float f){
	if(f>0)
	return 1;
	else if(f<0)
	return -1;
	else return 0;
}

Point mapPoint(float x1,float y1,int cwidth){
	int x0=getmaxx()/2, y0=getmaxy()/2;
	Point p;
	p.x=x0+(int)(cwidth*x1);
	p.y=y0-(int)(cwidth*y1);
	return p;
}

void plot(int x,int y, int cwidth){
	Point p=mapPoint(x,y,cwidth);
	setfillstyle(SOLID_FILL,BLUE);
	bar((p.x),(p.y),p.x+cwidth,p.y-cwidth);
}

void drawLine(float x0,float y0,float x1,float y1,int cwidth){
	Point p0,p1;
	p0=mapPoint(x0,y0,cwidth);
	p1=mapPoint(x1,y1,cwidth);
	setlinestyle(SOLID_LINE,0,1);
	setcolor(GREEN);
	line(p0.x,p0.y,p1.x,p1.y);
	setlinestyle(SOLID_LINE,0,1);
	setcolor(WHITE);
}


void fill_right(x,y)
int x , y ;
{
if(getpixel(x,y) == 0)
{
putpixel(x,y,BLUE);
fill_right(++x,y,cw);
x = x - 1 ;
fill_right(x,y-1,cw);
fill_right(x,y+1,cw);

}
}

void fill_left(x,y)
int x , y ;
{
if(getpixel(x,y) == 0)
{
putpixel(x,y,BLUE);

fill_left(--x,y);
x = x + 1 ;
fill_left(x,y-1);
fill_left(x,y+1);

}
}


void main()
{
int x , y ,a[10][10];
int gd, gm ,n,i;
int cw;
int r,h,cx,cy;
printf("Enter cell width: ");
	scanf("%d",&cw);
detectgraph(&gd,&gm);
initMainGraph(cw);
//initgraph(&gd,&gm,"c:\\tc\\bgi");

printf("\n\n\tEnter the no. of edges of polygon : ");
scanf("%d",&n);
printf("\n\n\tEnter the cordinates of polygon :\n\n\n ");

for(i=0;i<n;i++)
{
printf("\tX%d Y%d : ",i,i);
scanf("%d %d",&a[i][0],&a[i][1]);
}

a[n][0]=a[0][0];
a[n][1]=a[0][1];

printf("\n\n\tEnter the seed point: ");
scanf("%d%d",&x,&y);


cleardevice();
setcolor(WHITE);

for(i=0;i<n;i++) /*- draw poly -*/
{
line(a[i][0],a[i][1],a[i+1][0],a[i+1][1]);
}

fill_right(x,y);
fill_left(x-1,y);

getch();
}
