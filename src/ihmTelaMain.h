#ifndef IHM_TELA_MAIN_H
#define IHM_TELA_MAIN_H

#include <lvgl.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 480

typedef struct {
    lv_obj_t *ui_telaMain_dashboard;    // Dashboard principal
    lv_obj_t *ui_telaMain_containerMain;    // Container principal (equivalente a ui_Dashoboard_cont_Main)
    lv_obj_t *ui_telaMain_cont_updown;  // Container updown (equivalente a ui_Dashoboard_cont_updown)
    lv_obj_t *btn_1;                    // Botão "Iniciar"
    lv_obj_t *label_btn1;               // Label do botão
} ui_t;

void ihmTelaMainInit();
void ihmTelaMainTask();
void createMainUI(ui_t *ui);

#endif