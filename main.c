#include <gtk/gtk.h>
void check_toggle(GtkWidget *wid, gpointer ptr)
{
    printf("The state of the button is %d\n",
           gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(wid)));
}
void main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);
    GtkBuilder *builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "../Layout.glade", NULL);
    GtkWidget *win = (GtkWidget *)gtk_builder_get_object(builder,
                                                         "window1");
    GtkWidget *btnL1 = (GtkWidget *)gtk_builder_get_object(builder,
                                                           "LED1");
    g_signal_connect(btnL1, "toggled",
                     G_CALLBACK(check_toggle),
                     NULL);
    gtk_widget_show_all(win);
    gtk_main();
}