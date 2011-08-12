#include <stdio.h>
#include <gtk/gtk.h>
#include <malloc.h>

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

int main(int argc, char *argv[])
{
	GtkWidget *window, *label;
	buffer=malloc(64);
	buffer[0]=0x30;
	buffer[1]=0;
	gtk_init(&argc,&argv);
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size(GTK_WINDOW(window),100,100);
	gtk_window_set_title(GTK_WINDOW(window),"timer");
	g_signal_connect(window,"destroy",G_CALLBACK(destroy),0);
	label=gtk_label_new(0);
	g_signal_connect(label,"expose-event",G_CALLBACK(expose_event),0); //this called immideatly with buffer filling
	g_timeout_add(1000,(GSourceFunc)timer_handle,(gpointer)window);
	gtk_container_add(GTK_CONTAINER(window),label);
	gtk_widget_show_all(window);
	gtk_main();
	timer_handle(window);
	free(buffer);
	return 0;
}
