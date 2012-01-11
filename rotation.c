#include <stdio.h>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>

//#include <math.h>
#include <malloc.h>
#include <stdlib.h>

float width=800,height=800,x=0,y=0,speed=0.0001,tme[10000][3],t=0,tcur=0,cx,cy;

int dir=0,mark=0,oldmark=0,synchro=1;

void draw(){
	int i;
	glBegin(1);
	glColor3ub(255,255,255);
	glVertex2f(0,-1);
	glVertex2f(0,1);
	glVertex2f(-1,0);
	glVertex2f(1,0);
	glEnd();

	if(synchro){
		cx=x;
		cy=y;
		glBegin(1);
		glColor3ub(0,255,0);
		glVertex2f(0,t);
		glVertex2f(1,t);

		glVertex2f(t-1,-1);
		glVertex2f(t-1,0);
		glEnd();

	}else{
		glBegin(1);
		glColor3ub(0,255,0);
		glVertex2f(0,tcur);
		glVertex2f(1,tcur);

		glVertex2f(tcur-1,-1);
		glVertex2f(tcur-1,0);
		glEnd();
	}
	glBegin(7);
	glColor3ub(255,255,255);
	glVertex2f(cx-0.8,cy+0.4);
	glVertex2f(cx-0.6,cy+0.4);
	glVertex2f(cx-0.6,cy+0.5);
	glVertex2f(cx-0.8,cy+0.5);

	for(i=0;i<mark;i++){
		glVertex2f(tme[i][0]+0.2,tme[i][2]);
		glVertex2f(tme[i][0]+0.4,tme[i][2]);
		glVertex2f(tme[i+1][0]+0.4,tme[i+1][2]);
		glVertex2f(tme[i+1][0]+0.2,tme[i+1][2]);

		glVertex2f(tme[i][2]-1,tme[i][1]-0.6);
		glVertex2f(tme[i+1][2]-1,tme[i+1][1]-0.6);
		glVertex2f(tme[i+1][2]-1,tme[i+1][1]-0.5);
		glVertex2f(tme[i][2]-1,tme[i][1]-0.5);

	}
	if(dir!=0){
		glVertex2f(tme[mark][0]+0.2,tme[mark][2]);
		glVertex2f(tme[mark][0]+0.4,tme[mark][2]);
		glVertex2f(x+0.4,t);
		glVertex2f(x+0.2,t);

		glVertex2f(tme[mark][2]-1,tme[mark][1]-0.6);
		glVertex2f(t-1,y-0.6);
		glVertex2f(t-1,y-0.5);
		glVertex2f(tme[mark][2]-1,tme[mark][1]-0.5);
	}
	glEnd();	


	if(oldmark!=mark){
		tme[mark][0]=x;
		tme[mark][1]=y;
		tme[mark][2]=t;
		oldmark=mark;
	}

	switch(dir){
	case 1:
		if(y<0.5)
			y+=speed;
	break;
	case 2:
		if(x<0.6)
			x+=speed;
	break;
	case 3:
		if(y>-0.4)
			y-=speed;
	break;
	case 4:
		if(x>-0.2)
			x-=speed;
	break;
	}
	if(dir!=0){
		t+=speed;
	}
	if(t>1)
		;
}

int main()
{
	int i,drag=0;

	Display *dpy;
	Window root;
	int att[]={GLX_RGBA,GLX_DEPTH_SIZE,24,GLX_DOUBLEBUFFER,None};
	XVisualInfo *vi;
	Colormap cmap;
	XSetWindowAttributes swa;
	Window win;
	GLXContext glc;
	XWindowAttributes gwa;
	XEvent xev;

	int viewport[4];
	char *buf;
	buf=malloc(1500);
	dpy = XOpenDisplay(0);

	if(!dpy){
		printf("XOpenDisplay failed\n");
		return -1;
	}
	root=DefaultRootWindow(dpy);
	vi=glXChooseVisual(dpy,0,att);
	if(!vi){
		printf("glXChooseVisual failed\n");
	}

	cmap=XCreateColormap(dpy,root,vi->visual,AllocNone);

	swa.colormap=cmap;
	swa.event_mask=ExposureMask|KeyPressMask|KeyReleaseMask|ButtonPressMask|ButtonReleaseMask|PointerMotionMask;
	win=XCreateWindow(dpy,root,0,0,width,height,0,vi->depth,InputOutput,vi->visual,CWColormap|CWEventMask,&swa);
	XMapWindow(dpy,win);

	glc=glXCreateContext(dpy,vi,NULL,GL_TRUE);
	glXMakeCurrent(dpy,win,glc);
	glEnable(GL_DEPTH_TEST);
	XGetWindowAttributes(dpy,win,&gwa);
	glViewport(0,0,gwa.width,gwa.height);
	glGetIntegerv(GL_NUM_EXTENSIONS,&i);
	sprintf(buf,"%i",i);
	XStoreName(dpy,win,buf);

	glGetIntegerv(GL_VIEWPORT,viewport);
	glColor3ub(255,255,255);

	//fix that fills queue initially
	xev.type=Expose;
	XSendEvent(dpy,win,0,ExposureMask,&xev);

	while(1){
	while (XPending(dpy) > 0)
	{
		XNextEvent(dpy,&xev);
		if(xev.type == Expose){
//			glMatrixMode(GL_PROJECTION);
//			glLoadIdentity();
//			glMatrixMode(GL_MODELVIEW);
//			glLoadIdentity();
		}else 
		if(xev.type == KeyPress){
			if(xev.xkey.type==KeyPress){
				switch(xev.xkey.keycode){
				case 9:
					glXMakeCurrent(dpy,None,0);
					glXDestroyContext(dpy,glc);
					XDestroyWindow(dpy,win);
					XCloseDisplay(dpy);
					free(buf);
					return 0;
				case 0x41: //spacebar

				break;
				case 0x6f: //up
					dir=1;
				break;
				case 0x72: //right
					dir=2;
				break;
				case 0x74: //down
					dir=3;
				break;
				case 0x71: //left
					dir=4;
				break;
				default:
					sprintf(buf,"%04X",xev.xkey.keycode);
				}
			}else{
				switch(xev.xkey.keycode){
				default:
					sprintf(buf,"%04X",xev.xkey.keycode);
				}
			}
		}else if(xev.type == KeyRelease){
			XEvent nev;
			XPeekEvent(dpy,&nev);
			if(nev.type == KeyPress && nev.xkey.keycode == xev.xkey.keycode && nev.xkey.time == xev.xkey.time)
				XNextEvent (dpy, &nev);
			else
				switch(xev.xkey.keycode){
				case 0x6f:
				case 0x72:
				case 0x74:
				case 0x71:
					mark++;
					dir=0;
					sprintf(buf,"%04X %i",mark,dir);
					XStoreName(dpy,win,buf);
				break;
				}
		}else if(xev.type == MotionNotify){ //mousebutton

			if(xev.xmotion.x>width/2 && xev.xmotion.y <height/2 && drag)
				tcur=1-(xev.xmotion.y*2.0)/height;
				
			if(xev.xmotion.x<width/2 && xev.xmotion.y >height/2 && drag)
				tcur=(xev.xmotion.x*2.0)/width;

			for(i=0;i<=mark;i++){
				if(tcur<tme[i][2]){
					cx=(tme[i][0]-tme[i-1][0])*(tcur-tme[i-1][2])/(tme[i][2]-tme[i-1][2])+tme[i-1][0];
					cy=(tme[i][1]-tme[i-1][1])*(tcur-tme[i-1][2])/(tme[i][2]-tme[i-1][2])+tme[i-1][1];
					break;
				}
			}

		}else if(xev.type == ButtonPress){
			if(xev.xbutton.button == Button1){
				
				if(xev.xbutton.x>width/2 && xev.xbutton.y<height/2){
					tcur=1-(xev.xmotion.y*2.0)/height;
					synchro=0;
				}
				if(xev.xbutton.x<width/2 && xev.xbutton.y>height/2){
					tcur=xev.xbutton.x/(width/2.0);
					synchro=0;
				}

				for(i=0;i<=mark;i++){
					if(tcur<tme[i][2]){
						cx=(tme[i][0]-tme[i-1][0])*(tcur-tme[i-1][2])/(tme[i][2]-tme[i-1][2])+tme[i-1][0];
						cy=(tme[i][1]-tme[i-1][1])*(tcur-tme[i-1][2])/(tme[i][2]-tme[i-1][2])+tme[i-1][1];
						break;
					}
				}
				sprintf(buf,"%i %i %.5f",xev.xbutton.x,xev.xbutton.y,tcur);
				XStoreName(dpy,win,buf);
				drag=1;
			}else if(xev.xbutton.button == Button2){
				synchro=1;
			}
		}else if(xev.type == ButtonRelease){
			if(xev.xbutton.button == Button1){
				drag=0;
			}
		}
	}
//	sprintf(buf,"abc");
//	XStoreName(dpy,win,buf);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	draw();
	glFinish();
	glXSwapBuffers(dpy, win);
	}
	return 0;
}

