#include <stdio.h>
#include <gtk/gtk.h>
#include <malloc.h>
#include <sys/socket.h>

#include "alsa.c"

unsigned int elaptime=0;
unsigned char *buffer;
static void destroy(GtkWidget *widget, gpointer data)
{
	gtk_main_quit();
}
static gboolean expose_event(GtkWidget *widget, GdkEventExpose *event, gpointer data)
{
	gtk_label_set_text((GtkLabel*)widget,buffer);
	return FALSE;
}
static gboolean timer_handle(GtkWidget *widget)
{
	if(widget->window == NULL) return FALSE;
	g_sprintf(buffer,"%u",elaptime);
	elaptime++;
	gtk_widget_queue_draw(widget);
	return TRUE;
}

void button_handle(GtkWidget *widget, gpointer data)
{
	alsa_thing();
	printf("button clicked\n");
}

void button1_handle(GtkWidget *widget, gpointer data)
{
	int s,s1,i;
	struct sockaddr sa;
	unsigned char *buf;
	buf=malloc(1500);
	s=socket(2,1,6);
	sa.sa_family=2;
	sa.sa_data[0]=0x10;
	sa.sa_data[1]=0x20;
	sa.sa_data[2]=127;
	sa.sa_data[3]=0;
	sa.sa_data[4]=0;
	sa.sa_data[5]=1;
	if(bind(s,&sa,16)){
		if(errno==98){
			printf("bind failed: addr in use\n");
			i=1;
			setsockopt(s,SOL_SOCKET,SO_REUSEADDR,&i,1);
		}else{
			printf("bind failed: %i\n",errno);
		}
	}
	printf("bind ok\n");
	listen(s,2);
	printf("listentnig...\n");
	s1=accept(s,&sa,&i);
	printf("connection accepted\n",s1);
	while(recv(s1,buf,1500,0)>0){
		printf("recved something\n");
	}
	free(buf);
	close(s1);
	close(s);
}

int main(int argc, char *argv[])
{
	GtkWidget *window, *label, *button, *fixed, *button1;
	buffer=malloc(64);
	sprintf(buffer,"-");
	gtk_init(&argc,&argv);
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size(GTK_WINDOW(window),100,100);
	gtk_window_set_title(GTK_WINDOW(window),"timer");
	g_signal_connect(window,"destroy",G_CALLBACK(destroy),0);
	label=gtk_label_new(0);
	fixed=gtk_fixed_new();
	button=gtk_button_new_with_label("alsa");
	button1=gtk_button_new_with_label("socket");
	
	g_signal_connect(label,"expose-event",G_CALLBACK(expose_event),0); //this called immideatly with buffer filling
	g_timeout_add(1000,(GSourceFunc)timer_handle,(gpointer)window);
	g_signal_connect(button,"clicked",G_CALLBACK(button_handle),0);
	g_signal_connect(button1,"clicked",G_CALLBACK(button1_handle),0);

	gtk_fixed_put(GTK_FIXED(fixed),button,20,50);
	gtk_fixed_put(GTK_FIXED(fixed),button1,20,70);
	gtk_fixed_put(GTK_FIXED(fixed),label,20,20);
	gtk_container_add(GTK_CONTAINER(window),fixed);
	gtk_widget_show_all(window);
	gtk_main();
	timer_handle(window);
	free(buffer);
	return 0;
}
