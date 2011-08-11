all :
	gcc src/main.c -I/usr/include/gtk-2.0 -I/usr/include/glib-2.0 -I/usr/include/cairo -I/usr/include/pango-1.0 -I/usr/lib/glib-2.0/include -I/usr/lib/gtk-2.0/include -I/usr/include/atk-1.0 -lgtk-x11-2.0 -o g-timer
