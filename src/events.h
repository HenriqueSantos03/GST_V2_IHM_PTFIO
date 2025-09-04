#ifndef EVENTS_H
#define EVENTS_H

#include <lvgl.h>
#include "ihmTelaMain.h"
#include "masterControl.h"

void eventsInit();
void eventsTask();
void events_init_ui_telaMain(lv_ui *ui);
void ativarL1(lv_ui *ui, STATUS_GST *gst);
void ativarL2(lv_ui *ui, STATUS_GST *gst);
void ativarL3(lv_ui *ui, STATUS_GST *gst);
void showSetPointL1(lv_ui *ui, STATUS_GST *gst);
void showSetPointL2(lv_ui *ui, STATUS_GST *gst);
void showSetPointL3(lv_ui *ui, STATUS_GST *gst);
void showSetPointsPercents(lv_ui *ui, STATUS_GST *gst);
void saveSetPointsPercents(lv_ui *ui, STATUS_GST *gst);
void restoreSetPointsPercents(lv_ui *ui, STATUS_GST *gst);
void alternarGrupoFases(lv_ui *ui, STATUS_GST *gst);
void incPercent(enum PERCENTS_FASES fase, STATUS_GST *gst);
void decPercent(enum PERCENTS_FASES fase, STATUS_GST *gst);
void setPercent(int valor, STATUS_GST *gst);
double calcPassoTensao(double valPasso, double escala);
void bloquearTeclado(lv_ui *ui, STATUS_GST *gst);
void desbloquearTeclado(lv_ui *ui, STATUS_GST *gst);
void mbox_close_event_cb(lv_event_t * e);
void altModecbHab(lv_ui *ui, STATUS_GST *gst);
void altModeInputTeclado(lv_ui *ui, STATUS_GST *gst);
void ihmDashboardRefresh();

#endif