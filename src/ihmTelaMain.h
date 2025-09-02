#ifndef IHM_TELA_MAIN_H
#define IHM_TELA_MAIN_H

#include <lvgl.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 480

typedef struct {
    lv_obj_t *ui_telaMain_dashboard;        // Dashboard principal
    lv_obj_t *ui_telaMain_containerMain;    // Container principal (equivalente a ui_Dashoboard_cont_Main)
    lv_obj_t *ui_telaMain_cont_updown;      // Container updown (equivalente a ui_Dashoboard_cont_updown)
    //btn_l1
    lv_obj_t *ui_telaMain_btn_upL1;         // Botão up L1 (equivalente a ui_Dashoboard_btn_upL1)
    lv_obj_t *ui_telaMain_label_btn_upL1;   // Label do botão up L1
    lv_obj_t *ui_telaMain_btn_downL1;       // Botão down L1 (equivalente a ui_Dashoboard_btn_downL1)
    lv_obj_t *ui_telaMain_label_btn_downL1; // Label do botão down L1
    lv_obj_t *ui_telaMain_img_upL1;         // Imagem do botão up L1
	lv_obj_t *ui_telaMain_img_downL1;       // Imagem do botão down L1
    //btn_l2
    lv_obj_t *ui_telaMain_btn_upL2;         // Botão up L2 (equivalente a ui_Dashoboard_btn_upL2)
    lv_obj_t *ui_telaMain_label_btn_upL2;   // Label do botão up L2
    lv_obj_t *ui_telaMain_btn_downL2;       // Botão down L2 (equivalente a ui_Dashoboard_btn_downL2)
    lv_obj_t *ui_telaMain_label_btn_downL2; // Label do botão down L2
	lv_obj_t *ui_telaMain_img_upL2;         // Imagem do botão up L2   
    lv_obj_t *ui_telaMain_img_downL2;       // Imagem do botão down L2
    //btn_l3
    lv_obj_t *ui_telaMain_btn_upL3;         // Botão up L3 (equivalente a ui_Dashoboard_btn_upL3)
    lv_obj_t *ui_telaMain_label_btn_upL3;   // Label do botão up L3
    lv_obj_t *ui_telaMain_btn_downL3;       // Botão down L3 (equivalente a ui_Dashoboard_btn_downL3)
    lv_obj_t *ui_telaMain_label_btn_downL3; // Label do botão down L3
	lv_obj_t *ui_telaMain_img_upL3;         // Imagem do botão up L3
	lv_obj_t *ui_telaMain_img_downL3;       // Imagem do botão down L3

    lv_obj_t *btn_1;                        // Botão "Iniciar"
    lv_obj_t *label_btn1;                   // Label do botão
} ui_t;

void ihmTelaMainInit();
void ihmTelaMainTask();
void createMainUI(ui_t *ui);

#endif