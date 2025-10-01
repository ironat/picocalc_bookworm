#include <lxpanel/plugin.h>

#include <stdio.h>

#define LabelSize 32

GtkWidget *test_constructor(LXPanel *panel, config_setting_t *settings)
{
 /* panel is a pointer to the panel and
     settings is a pointer to the configuration data
     since we don't use it, we'll make sure it doesn't
     give us an error at compilation time */
 (void)panel;
 (void)settings;

 // make a label out of the hostname
 char cIdBuf[LabelSize+1] = {'\0'};
 FILE *fp;
 fp = fopen("/sys/firmware/picocalc/battery_percent", "r");
 fgets(cIdBuf, LabelSize, fp);
 fclose(fp);

 //convert string to int
 int percent = atoi(cIdBuf);
 char clableBuf[LabelSize+1] = {'\0'};
 if(percent > 128) {
    percent-=128;
    sprintf(clableBuf,"C%d%%",percent);
 } else {
    sprintf(clableBuf,"%d%%",percent);
 } 
 // create a label widget instance
 GtkWidget *pLabel = gtk_label_new(clableBuf);

 // set the label to be visible
 gtk_widget_show(pLabel);

 // need to create a container to be able to set a border
 GtkWidget *p = gtk_event_box_new();

 // our widget doesn't have a window...
 // it is usually illegal to call gtk_widget_set_has_window() from application but for GtkEventBox it doesn't hurt
 gtk_widget_set_has_window(p, FALSE);

 // set border width
 gtk_container_set_border_width(GTK_CONTAINER(p), 1);

 // add the label to the container
 gtk_container_add(GTK_CONTAINER(p), pLabel);

 // set the size we want
//  gtk_widget_set_size_request(p, 100, 25);

 // success!!!
 return p;
}

FM_DEFINE_MODULE(lxpanel_gtk, test)

/* Plugin descriptor. */
LXPanelPluginInit fm_module_init_lxpanel_gtk = {
   .name = "PicoCalcBattery",
   .description = "Display Pico Calc Battery",
   .one_per_system = 1,

   // assigning our functions to provided pointers.
   .new_instance = test_constructor
};
