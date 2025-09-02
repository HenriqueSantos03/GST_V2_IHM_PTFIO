#ifndef EVENTS_H
#define EVENTS_H

#include <lvgl.h>
#include "ihmTelaMain.h"

void eventsInit();
void eventsTask();
void events_init_ui_telaMain(lv_ui *ui);

#endif