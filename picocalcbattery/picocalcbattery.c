#include <lxpanel/plugin.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
//#include <glib/gi18n.h>

//#include <string.h>


#define LabelSize 32


typedef gint (*GetBatteryFunc)(char const *);

typedef struct battery {
   LXPanel *panel;
   unsigned int timer;
   char *cpercent;
   GetBatteryFunc getPercentLabelText;
   GtkWidget *namew;
} battery;

static void getPercentLabelText(battery* bat) {
    
 // make a label out of the hostname
 char cIdBuf[LabelSize+1] = {'\0'};
 FILE *fp;
 fp = fopen("/sys/firmware/picocalc/battery_percent", "r");
 fgets(cIdBuf, LabelSize, fp);
 fclose(fp);

 //convert string to int
 int percent = atoi(cIdBuf);
 //const char* clableBuf[LabelSize+1] = {'\0'};
 if(percent > 128) {
    percent-=128;
    sprintf(bat->cpercent,"C%d%%",percent);
 } else {
    sprintf(bat->cpercent,"%d%%",percent);
 } 
}

static void
update_display(battery *bat)
{
    getPercentLabelText(bat);
    lxpanel_draw_label_text(bat->panel, bat->namew, bat->cpercent, TRUE, 1, TRUE);
}

static gboolean update_display_timeout(gpointer user_data)
{
    if (g_source_is_destroyed(g_main_current_source()))
        return FALSE;
    update_display(user_data);
    return TRUE; /* repeat later */
}

static GtkWidget *picocalcbattery_constructor(LXPanel *panel, config_setting_t *settings)
{
 /* panel is a pointer to the panel and
     settings is a pointer to the configuration data
     since we don't use it, we'll make sure it doesn't
     give us an error at compilation time */
 battery *bat;
 bat = g_new0(battery,1);
 // create a label widget instance
 bat->namew = gtk_label_new("123");
 bat->panel = panel;
 bat->cpercent =  g_strdup("CXXXXX");
 //(void)panel;
 (void)settings;
 // set the label to be visible
 gtk_widget_show(bat->namew);

 // need to create a container to be able to set a border
 GtkWidget *p = gtk_event_box_new();

 // our widget doesn't have a window...
 // it is usually illegal to call gtk_widget_set_has_window() from application but for GtkEventBox it doesn't hurt
 gtk_widget_set_has_window(p, FALSE);

 // set border width
 gtk_container_set_border_width(GTK_CONTAINER(p), 1);

 // add the label to the container
 gtk_container_add(GTK_CONTAINER(p), bat->namew);

 update_display(bat);
 bat->timer = g_timeout_add_seconds(3, (GSourceFunc) update_display_timeout, (gpointer)bat);
 return p;
}

FM_DEFINE_MODULE(lxpanel_gtk, battery)

/* Plugin descrptor. */
LXPanelPluginInit fm_module_init_lxpanel_gtk = {
   .name = "PicoCalcBattery",
   .description = "Display Pico Calc Battery",
   .one_per_system = 1,

   // assigning our functions to provided pointers.
   .new_instance = picocalcbattery_constructor
};
