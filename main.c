#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

static void activate(GtkApplication *app, gpointer user_data) 
{
    GtkWidget *window;
    GtkWidget *button;

    window = gtk_application_window_new(app);

    gtk_window_set_title(GTK_WINDOW(window), "2D Jump and Run");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 800);

    button = gtk_button_new_with_label("Click me!");

    gtk_window_set_child(GTK_WINDOW(window), button);
    gtk_window_present(GTK_WINDOW(window));
}


int main(int argc, char **argv)
{
    GtkApplication *app;
    int status; 

    app = gtk_application_new(
        "de.matthias.jumpandrun",
        G_APPLICATION_DEFAULT_FLAGS
    );

    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    
    return 0;
}
