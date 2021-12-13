#include <gtk/gtk.h>
#include <gpiod.h>
void check_toggle(GtkWidget *wid, gpointer ptr)
{
    printf("The state of the button is %d\n",
           gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(wid)));

 GPIO(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(wid)));
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

void GPIO(int i)
{
    printf("%d\r\n",i);
    const char *chipname = "gpiochip0";
    struct gpiod_chip *chip;
    struct gpiod_line *gpio26; // GPIO 19

    // Open GPIO chip
    chip = gpiod_chip_open_by_name(chipname);

    // Open GPIO lines
    gpio26 = gpiod_chip_get_line(chip, 26);
    // Open switch line for input
    gpiod_line_request_output(gpio26, "gpio26", NULL);

    if (i == 1)
    {
        //printf("on\n\r");
        gpiod_line_set_value(gpio26, 1);
    }
    if (i == 0)
    {
        //printf("off\n\r");
        gpiod_line_set_value(gpio26, 0);
    }
      gpiod_line_release(gpio26);
}
