#include <gtk/gtk.h>
#include <gpiod.h>
#include <string.h>

void check_toggleL1(GtkWidget *wid, gpointer ptr)
{
    /* printf("The state of the LED1 is %d\n",
           gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(wid)));*/

    GPIO(26, gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(wid)));
}

void check_toggleL2(GtkWidget *wid, gpointer ptr)
{
    GPIO(19, gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(wid)));
}

void check_toggleI1(GtkWidget *wid, gpointer ptr)
{
    char test[1];
    sprintf(test, "%d", GPIO(23, gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(wid))));
    gtk_label_set_text(GTK_LABEL(ptr), test);
}

void check_toggleI2(GtkWidget *wid, gpointer ptr)
{
    char test[1];
    sprintf(test, "%d", GPIO(22, gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(wid))));
    gtk_label_set_text(GTK_LABEL(ptr), test);
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
    GtkWidget *btnL2 = (GtkWidget *)gtk_builder_get_object(builder,
                                                           "LED2");
    GtkWidget *btnI1 = (GtkWidget *)gtk_builder_get_object(builder,
                                                           "INPUT1");
    GtkWidget *btnI2 = (GtkWidget *)gtk_builder_get_object(builder,
                                                           "INPUT2");
    GtkWidget *lbl1 = gtk_builder_get_object(builder, "INPUTLBL1");
    GtkWidget *lbl2 = gtk_builder_get_object(builder, "INPUTLBL2");

    g_signal_connect(btnL1, "toggled",
                     G_CALLBACK(check_toggleL1),
                     NULL);
    g_signal_connect(btnL2, "toggled",
                     G_CALLBACK(check_toggleL2),
                     NULL);
    g_signal_connect(btnI1, "toggled",
                     G_CALLBACK(check_toggleI1),
                     lbl1);
    g_signal_connect(btnI2, "toggled",
                     G_CALLBACK(check_toggleI2),
                     lbl2);

    gtk_widget_show_all(win);
    gtk_main();
}

int GPIO(int gpio, int i)
{
    int state = 0;

    const char *chipname = "gpiochip0";
    struct gpiod_chip *chip;
    struct gpiod_line *gpio26; // GPIO 26
    struct gpiod_line *gpio19; // GPIO 19
    struct gpiod_line *gpio23; // GPIO 23
    struct gpiod_line *gpio22; // GPIO 22

    // Open GPIO chip
    chip = gpiod_chip_open_by_name(chipname);

    // Open GPIO lines
    gpio26 = gpiod_chip_get_line(chip, 26);
    gpio19 = gpiod_chip_get_line(chip, 19);
    gpio23 = gpiod_chip_get_line(chip, 23);
    gpio22 = gpiod_chip_get_line(chip, 22);
    // Open switch line for input
    gpiod_line_request_output(gpio26, "gpio26", 1);
    gpiod_line_request_output(gpio19, "gpio19", 1);
    gpiod_line_request_input(gpio23, "gpio23");
    gpiod_line_request_input(gpio22, "gpio22");

    switch (gpio)
    {
    case 26:
        if (i == 1)
        {
            printf("on1\n\r");
            gpiod_line_set_value(gpio26, 1);
        }
        if (i == 0)
        {
            printf("off1\n\r");
            gpiod_line_set_value(gpio26, 0);
        }
        printf("dink");
        break;

    case 19:
        if (i == 1)
        {
            printf("on2\n\r");
            gpiod_line_set_value(gpio19, 1);
        }
        if (i == 0)
        {
            printf("off2\n\r");
            gpiod_line_set_value(gpio19, 0);
        }
        break;
    case 23:
        state = gpiod_line_get_value(gpio23);
        break;
    case 22:
        state = gpiod_line_get_value(gpio22);
        break;

    default:

        break;
    }

    gpiod_line_release(gpio26);
    gpiod_line_release(gpio19);
    gpiod_line_release(gpio23);
    gpiod_line_release(gpio22);

    return state;
}
