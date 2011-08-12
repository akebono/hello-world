#include <stdio.h>
#include <gtk/gtk.h>
#include <malloc.h>

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
	int s,i;
	struct sockaddr sa;

	s=socket(2,1,6);
	sa.sa_family=2;
	sa.sa_data[0]=0x10;
	sa.sa_data[0]=0x20;
	sa.sa_data[0]=127;
	sa.sa_data[0]=0;
	sa.sa_data[0]=0;
	sa.sa_data[0]=1;
	if(bind(s,&sa,16))
		if(errno==98){
			i=1;
			setsockopt(s,SOL_SOCKET,SO_REUSE_ADDR,&i,1)
		}
		

	return FALSE;
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
	button=gtk_button_new_with_label("socket");
	
	g_signal_connect(label,"expose-event",G_CALLBACK(expose_event),0); //this called immideatly with buffer filling
	g_timeout_add(1000,(GSourceFunc)timer_handle,(gpointer)window);
	g_signal_connect(button,"clicked",G_CALLBACK(button_handle),0);
	g_signal_connect(button,"clicked",G_CALLBACK(button1_handle),0);

	gtk_fixed_put(GTK_FIXED(fixed),button,20,70);
	gtk_fixed_put(GTK_FIXED(fixed),label,20,20);
	gtk_container_add(GTK_CONTAINER(window),fixed);
	gtk_widget_show_all(window);
	gtk_main();
	timer_handle(window);
	free(buffer);
	return 0;
}
