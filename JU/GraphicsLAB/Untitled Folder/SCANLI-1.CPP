#include<cstdio>
#include<graphics.h>
#include<cmath>
#include<iostream>
#include<fstream>
#define XORIGIN 250
#define YORIGIN 300
#define XSTART 50
#define YSTART 50
#define HEIGHT 600
#define WIDTH 450
#define BOUNDARY_VALUE 8
#define NEW_VALUE 10
#define MAX 10000

using namespace std;

typedef struct pix{
	int x;
	int y;
} pixel;

class stack{
	pixel st[MAX];
	int top;

	public:
		stack(){
			top=-1;
		}
		void push(pixel p){
			if(top==MAX-1){
				cout<<"Stack Overflow!"<<endl;
				return;
			}
			st[++top]=p;
		}
		pixel pop(){
			return st[top--];
		}
		void display();
		int stlen();
		int empty(){
			if(top==-1)
				return 1;
			return 0;
		}
};
int stack::stlen(){
	return top+1;
}
void stack::display(){
	int c=0;
	for(;c<=top;c++)
		cout<<"("<<st[c].x<<","<<st[c].y<<") ";
}
void draw_line(int,int,int,int);
void draw_circle();
void seed_fill();
int sign(int n){
	if(n>0)
		return 1;
	else if(n==0)
		return 0;
	else
		return -1;
}
void fillpixel(int x,int y,int col){
	int x1_actual,y1_actual,x2_actual,y2_actual;
	x1_actual=YORIGIN+(5*x);
	y1_actual=XORIGIN-(5*y);
	x2_actual=x1_actual-5;
	y2_actual=y1_actual+5;
	bar(x1_actual,y1_actual,x2_actual,y2_actual);

}

int getpixelcolor(pixel p){
	int x1_actual,y1_actual;
	x1_actual=YORIGIN+(p.x*5)-2;
	y1_actual=XORIGIN-(p.y*5)+2;
	return getpixel(x1_actual,y1_actual);
}

int main(){
	int gd=DETECT,gm;
	initgraph(&gd,&gm,NULL);
	int row,col;
	setbkcolor(5);
	for(row=YSTART;row<=HEIGHT;row+=5){
		if(row==YORIGIN){
			setcolor(15);
			setlinestyle(0,0,3);
		}
		else if(row%50==0){
			setcolor(7);
			setlinestyle(0,0,3);
		}
		else{
			setcolor(7);
			setlinestyle(0,0,1);
		}
		line(row,XSTART,row,WIDTH);
	}
	for(col=XSTART;col<=WIDTH;col+=5){
		if(col==XORIGIN){
			setcolor(7);
			setlinestyle(0,0,3);
		}
		else if(col%50==0){
			setcolor(7);
			setlinestyle(0,0,3);
		}
		else{
			setcolor(7);
			setlinestyle(0,0,1);
		}
		line(YSTART,col,HEIGHT,col);
	}
	setcolor(0);

	/*
	// SQUARE
	draw_line(-10,10,10,10);
	draw_line(-10,10,-10,-10);
	draw_line(-10,-10,10,-10);
	draw_line(10,10,10,-10);

	*/
	// HEXAGON

	/*draw_line(0,30,20,20);
	draw_line(20,20,10,-10);
	draw_line(10,-10,-10,-10);
	draw_line(-10,-10,-20,20);
	draw_line(-20,20,0,30);*/
	//draw_line(20,0,10,-10);

	//draw_circle();
       /*	draw_line(0,30,40,-20);
	draw_line(40,-20,-40,-20);
	draw_line(-40,-20,0,30);*/
	draw_line(10,10,10,-10);
	draw_line(10,-10,-10,-10);
	draw_line(-10,-10,-10,10);
	draw_line(-10,10,10,10);
	draw_line(-40,-20,40,-20);
	draw_line(-40,-20,-20,27);
	draw_line(-20,27,-10,20);
	draw_line(-10,20,5,20);
	draw_line(5,20,20,38);
	draw_line(20,38,40,-20);



	seed_fill();
	getch();
	closegraph();
}
/*void draw_ellipse(){
	int a,b,curx,cury,d1,d2;
	printf("Enter value of a and b: ");
	scanf("%d %d",&a,&b);
	curx=0;
	cury=b;
	fillpixel(curx,cury,BOUNDARY_VALUE);
	while(a*a*(cury-0.5)>b*b*(curx+1)){
		if(d1<0)
			d1=d1+(b*b*(2*curx+3));
		else
			d1=d1+*/
void draw_circle(){
	int r;
	printf("Enter radius of the circle: ");
	scanf("%d",&r);
	int cur_x=0,cur_y=r,delta,del1,del2;
	delta=2*(1-r);
	while(cur_y>=0){
		fillpixel(cur_x,cur_y,BOUNDARY_VALUE);
		fillpixel(cur_x,-cur_y,BOUNDARY_VALUE);
		fillpixel(-cur_x,-cur_y,BOUNDARY_VALUE);
		fillpixel(-cur_x,cur_y,BOUNDARY_VALUE);
		if(delta<0){
			del1=2*(delta+cur_y)-1;
			if(del1<0){
				cur_x=cur_x+1;
				delta=delta+2*cur_x+1;
			}
			else{
				cur_x=cur_x+1;
				cur_y=cur_y-1;
				delta=delta+2*cur_x-2*cur_y+1;
			}
		}
		else if(delta>0){
			del2=2*(delta-cur_x)-1;
			if(del2>0){
				cur_y=cur_y-1;
				delta=delta-2*cur_y+1;
			}
			else{
				cur_y=cur_y-1;
				cur_x=cur_x+1;
				delta=delta+2*cur_x-2*cur_y+1;
			}
		}
		else{
			cur_x=cur_x+1;
			cur_y=cur_y-1;
			delta=delta+2*cur_x-2*cur_y+1;
		}
	}
}
void draw_line(int x1,int y1,int x2,int y2){
	int length;
	//printf("Enter x1,y1,x2,y2: ");
	//scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
	int del_x,del_y;
	float cur_x,cur_y,x_inr,y_inr;
	del_x=x2-x1;
	del_y=y2-y1;
	if(fabs(del_x)>=fabs(del_y))
		length=fabs(del_x);
	else
		length=fabs(del_y);
	x_inr=del_x/(float)length;
	y_inr=del_y/(float)length;
	cur_x=x1+0.5;
	cur_y=y1+0.5;
	int i=1;
	while(i<=length){
		fillpixel((int)cur_x,(int)cur_y,BOUNDARY_VALUE);
		cur_x=cur_x+x_inr;
		cur_y=cur_y+y_inr;
		i=i+1;
	}
}

void seed_fill(){
	int maxlen=-100;
	pixel seed={0,19};
	stack st;
	st.push(seed);
	//int count=0;
	while(!st.empty()){
		if(st.stlen()>maxlen)
			maxlen=st.stlen();
		pixel curr=st.pop();
		fillpixel(curr.x,curr.y,NEW_VALUE);
		int savex=curr.x;
		curr.x=curr.x+1;
		while(getpixelcolor(curr)!=BOUNDARY_VALUE){
			fillpixel(curr.x,curr.y,NEW_VALUE);
			curr.x=curr.x+1;
		}
		int xright=curr.x-1;
		curr.x=savex;
		curr.x=curr.x-1;
		while(getpixelcolor(curr)!=BOUNDARY_VALUE){
			fillpixel(curr.x,curr.y,NEW_VALUE);
			curr.x=curr.x-1;
		}
		int xleft=curr.x+1;
		curr.x=savex;
		//
		curr.x=xleft;
		curr.y=curr.y+1;
		while(curr.x<=xright){
			int pflag=0;
			while(getpixelcolor(curr)!=BOUNDARY_VALUE && getpixelcolor(curr)!=NEW_VALUE && curr.x<xright){
				if(pflag==0)
					pflag=1;
				curr.x=curr.x+1;
			}
			if(pflag==1){
				if(curr.x==xright && getpixelcolor(curr)!=BOUNDARY_VALUE && getpixelcolor(curr)!=NEW_VALUE)
					st.push(curr);
					//if(st.stlen()>maxlen)
					  //	maxlen=st.stlen();
				else{
					pixel temp={curr.x-1,curr.y};
					st.push(temp);
					//if(st.stlen()>maxlen)
						//maxlen=st.stlen();
				}
				pflag=0;
			}
			int xenter=curr.x;
			while((getpixelcolor(curr)==BOUNDARY_VALUE || getpixelcolor(curr)==NEW_VALUE) && curr.x<xright)
				curr.x=curr.x+1;
			if(curr.x==xenter)
				curr.x=curr.x+1;
		}
		curr.x=xleft;
		curr.y=curr.y-2;
		while(curr.x<=xright){
			int pflag=0;
			while(getpixelcolor(curr)!=BOUNDARY_VALUE && getpixelcolor(curr)!=NEW_VALUE && curr.x<xright){
				if(pflag==0)
					pflag=1;
				curr.x=curr.x+1;
			}
			if(pflag==1){
				if(curr.x==xright && getpixelcolor(curr)!=BOUNDARY_VALUE && getpixelcolor(curr)!=NEW_VALUE)
					st.push(curr);
					//if(st.stlen()>maxlen)
						//maxlen=st.stlen();
				else{
					pixel temp={curr.x-1,curr.y};
					st.push(temp);
					//if(st.stlen()>maxlen)
						//maxlen=st.stlen();
				}
				pflag=0;
			}
			int xenter=curr.x;
			while((getpixelcolor(curr)==BOUNDARY_VALUE || getpixelcolor(curr)==NEW_VALUE) && curr.x<xright)
				curr.x=curr.x+1;
			if(curr.x==xenter)
				curr.x=curr.x+1;
		}
		//if(st.stlen()>maxlen)
		  //	maxlen=st.stlen();
	}
	printf("%d ",maxlen);
}