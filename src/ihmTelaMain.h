#ifndef IHM_TELA_MAIN_H
#define IHM_TELA_MAIN_H

#include <lvgl.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 480

typedef struct {
    lv_obj_t *ui_telaMain_dashboard;        // Dashboard principal
    lv_obj_t *ui_telaMain_containerMain;    // Container principal
    lv_obj_t *ui_telaMain_cont_updown;      // Container updown
    // btn_l1
    lv_obj_t *ui_telaMain_btn_upL1;
    lv_obj_t *ui_telaMain_label_btn_upL1;
    lv_obj_t *ui_telaMain_btn_downL1;
    lv_obj_t *ui_telaMain_label_btn_downL1;
    lv_obj_t *ui_telaMain_img_upL1;
    lv_obj_t *ui_telaMain_img_downL1;
    // btn_l2
    lv_obj_t *ui_telaMain_btn_upL2;
    lv_obj_t *ui_telaMain_label_btn_upL2;
    lv_obj_t *ui_telaMain_btn_downL2;
    lv_obj_t *ui_telaMain_label_btn_downL2;
    lv_obj_t *ui_telaMain_img_upL2;
    lv_obj_t *ui_telaMain_img_downL2;
    // btn_l3
    lv_obj_t *ui_telaMain_btn_upL3;
    lv_obj_t *ui_telaMain_label_btn_upL3;
    lv_obj_t *ui_telaMain_btn_downL3;
    lv_obj_t *ui_telaMain_label_btn_downL3;
    lv_obj_t *ui_telaMain_img_upL3;
    lv_obj_t *ui_telaMain_img_downL3;
    // container avançado
    lv_obj_t *ui_telaMain_cont_avancado;
    lv_obj_t *ui_telaMain_btnPercent1;
    lv_obj_t *ui_telaMain_label_btnPercent1;
    lv_obj_t *ui_telaMain_btnPercent2;
    lv_obj_t *ui_telaMain_label_btnPercent2;
    lv_obj_t *ui_telaMain_btnPercent3;
    lv_obj_t *ui_telaMain_label_btnPercent3;
    lv_obj_t *ui_telaMain_btnPercent4;
    lv_obj_t *ui_telaMain_label_btnPercent4;
    lv_obj_t *ui_telaMain_btnPercent5;
    lv_obj_t *ui_telaMain_label_btnPercent5;
    lv_obj_t *ui_telaMain_btnConfig;
    lv_obj_t *ui_telaMain_label_btnConfig;
    lv_obj_t *ui_telaMain_btnNominal;
    lv_obj_t *ui_telaMain_label_btnNominal;
    lv_obj_t *ui_telaMain_btnAgrupar;
    lv_obj_t *ui_telaMain_label_btnAgrupar;
    // Container SelMode
    lv_obj_t *ui_telaMain_cont_selMode;
    lv_obj_t *ui_telaMain_selModePercent;
    lv_obj_t *ui_telaMain_selModeGrandeza;
    // Container UpPasso
    lv_obj_t *ui_telaMain_cont_upPasso;
    lv_obj_t *ui_telaMain_selPasso1;
    lv_obj_t *ui_telaMain_selPasso2;
    lv_obj_t *ui_telaMain_selPasso3;
    lv_obj_t *ui_telaMain_selPasso4;
    // Container Sequencia
    lv_obj_t *ui_telaMain_cont_sequencia;

    // Exemplo de objetos antigos, mantenha se usados em outro lugar
    lv_obj_t *btn_1;
    lv_obj_t *ui_telaMain_label_btn_1;
} ui_t;

void ihmTelaMainInit();
void ihmTelaMainTask();
void createMainUI(ui_t *ui);

#endif