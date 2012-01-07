#include <stdio.h>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>

#include <math.h>
#include <malloc.h>
#include <stdlib.h>

#include "main.h"

void draw(int mode){
	drawtrain();
	graph();
}

int main()
{
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

	int viewport[4],i;
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

	for(i=0;i<NUM_TRAINS;i++){
		speed[i]=speedc;
		state[i]=0;
	}

	cmap=XCreateColormap(dpy,root,vi->visual,AllocNone);
	swa.colormap=cmap;
	swa.event_mask=ExposureMask|KeyPressMask|PointerMotionMask;
	win=XCreateWindow(dpy,root,0,0,width,height,0,vi->depth,InputOutput,vi->visual,CWColormap|CWEventMask,&swa);
	XMapWindow(dpy,win);
	sprintf(buf,"%s",glGetString(GL_VENDOR));
	XStoreName(dpy,win,buf);
	glc=glXCreateContext(dpy,vi,NULL,GL_TRUE);
	glXMakeCurrent(dpy,win,glc);
	glEnable(GL_DEPTH_TEST);
	XGetWindowAttributes(dpy,win,&gwa);
	glViewport(0,0,gwa.width,gwa.height);
	glGetIntegerv(GL_VIEWPORT,viewport);
	glColor3ub(255,255,255);
	while(1){
	while (XPending(dpy) > 0)
	{
		XNextEvent(dpy,&xev);
//		if(xev.type == Expose){
/*			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();*/
//		}else 
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
				default:
					sprintf(buf,"%04X",xev.xkey.keycode);
				}
			}else{
				switch(xev.xkey.keycode){
				default:
					sprintf(buf,"%04X",xev.xkey.keycode);
				}
			}
		}else if(xev.type == MotionNotify){ //mousebutton
			x=(xev.xmotion.x*2.0)/width-1;
			y=1-(xev.xmotion.y*2.0)/height;
		}
	}
//sprintf(buf,"%.2f:%.2f %u",train[0][0],train[0][1],state[0]);
//	XStoreName(dpy,win,buf);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	draw(GL_RENDER);
	glFinish();
	glXSwapBuffers(dpy, win);
	}
	return 0;
}

