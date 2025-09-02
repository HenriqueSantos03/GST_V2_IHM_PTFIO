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
    lv_obj_t *ui_telaMain_label_seqFase;
    lv_obj_t *ui_telaMain_label_seq_l1;
    lv_obj_t *ui_telaMain_label_seq_l2;
    lv_obj_t *ui_telaMain_label_seq_l3;
    lv_obj_t *ui_telaMain_btnSeqL1L2;
    lv_obj_t *ui_telaMain_label_btnSeqL1L2;
    lv_obj_t *ui_telaMain_btnSeqL2L3;
    lv_obj_t *ui_telaMain_label_btnSeqL2L3;
    lv_obj_t *ui_telaMain_btnSeqL1L3;
    lv_obj_t *ui_telaMain_label_btnSeqL1L3;
    lv_obj_t *ui_telaMain_btnSeqL1L2L3;
    lv_obj_t *ui_telaMain_label_btnSeqL1L2L3;
    // Container Teclado
    lv_obj_t *ui_telaMain_cont_teclado;
    lv_obj_t *ui_telaMain_btn_n0;
    lv_obj_t *ui_telaMain_label_btn_n0;
    lv_obj_t *ui_telaMain_btn_n1;
    lv_obj_t *ui_telaMain_label_btn_n1;
    lv_obj_t *ui_telaMain_btn_n2;
    lv_obj_t *ui_telaMain_label_btn_n2;
    lv_obj_t *ui_telaMain_btn_n3;
    lv_obj_t *ui_telaMain_label_btn_n3;
    lv_obj_t *ui_telaMain_btn_n4;
    lv_obj_t *ui_telaMain_label_btn_n4;
    lv_obj_t *ui_telaMain_btn_n5;
    lv_obj_t *ui_telaMain_label_btn_n5;
    lv_obj_t *ui_telaMain_btn_n6;
    lv_obj_t *ui_telaMain_label_btn_n6;
    lv_obj_t *ui_telaMain_btn_n7;
    lv_obj_t *ui_telaMain_label_btn_n7;
    lv_obj_t *ui_telaMain_btn_n8;
    lv_obj_t *ui_telaMain_label_btn_n8;
    lv_obj_t *ui_telaMain_btn_n9;
    lv_obj_t *ui_telaMain_label_btn_n9;
    lv_obj_t *ui_telaMain_btn_ok;
    lv_obj_t *ui_telaMain_label_btn_ok;
    lv_obj_t *ui_telaMain_btn_cancel;
    lv_obj_t *ui_telaMain_label_btn_cancel;
    // container escala
    lv_obj_t *ui_telaMain_cont_escala;
    lv_obj_t *ui_telaMain_cont_escala_tensoes;
    lv_obj_t *ui_telaMain_selEscala0;
    lv_obj_t *ui_telaMain_selEscala1;   
    lv_obj_t *ui_telaMain_selEscala2;
    lv_obj_t *ui_telaMain_selEscala3;
    lv_obj_t *ui_telaMain_selEscala4;
    lv_obj_t *ui_telaMain_selEscala5;
    lv_obj_t *ui_telaMain_selEscala6;
    lv_obj_t *ui_telaMain_selEscala7;
    // container Frequencia
    lv_obj_t *ui_telaMain_cont_frequencia;
    lv_obj_t *ui_telaMain_label_frequencia;
    lv_obj_t *ui_telaMain_label_pointEsq;
    lv_obj_t *ui_telaMain_label_freqAtual;
    lv_obj_t *ui_telaMain_label_pointDir;
    lv_obj_t *ui_telaMain_sliderFreq;
    lv_obj_t *ui_telaMain_btnFreq50;
    lv_obj_t *ui_telaMain_label_btnFreq50;
    lv_obj_t *ui_telaMain_btnFreq60;
    lv_obj_t *ui_telaMain_label_btnFreq60;
    // containers de fase (cont_L1, cont_L2, cont_L3)
    lv_obj_t *ui_telaMain_cont_L1;
    lv_obj_t *ui_telaMain_label_L1;
    lv_obj_t *ui_telaMain_label_v_L1;
    lv_obj_t *ui_telaMain_label_mA_L1;
    lv_obj_t *ui_telaMain_label_fp_L1;
    lv_obj_t *ui_telaMain_linhaSup_L1;
    lv_obj_t *ui_telaMain_linhaInf_L1;
    lv_obj_t *ui_telaMain_label_set_L1;
    lv_obj_t *ui_telaMain_label_saida_L1;
    lv_obj_t *ui_telaMain_lbDisplayL1;
    lv_obj_t *ui_telaMain_lbCorrenteL1;
    lv_obj_t *ui_telaMain_lbFatorL1;
    lv_obj_t *ui_telaMain_lbSetL1;
    lv_obj_t *ui_telaMain_cbHabL1;
    // Cont_L2
    lv_obj_t *ui_telaMain_cont_L2;
    lv_obj_t *ui_telaMain_label_L2;
    lv_obj_t *ui_telaMain_label_v_L2;
    lv_obj_t *ui_telaMain_label_mA_L2;
    lv_obj_t *ui_telaMain_label_fp_L2;
    lv_obj_t *ui_telaMain_linhaSup_L2;
    lv_obj_t *ui_telaMain_linhaInf_L2;
    lv_obj_t *ui_telaMain_label_set_L2;
    lv_obj_t *ui_telaMain_label_saida_L2;
    lv_obj_t *ui_telaMain_lbDisplayL2;
    lv_obj_t *ui_telaMain_lbCorrenteL2;
    lv_obj_t *ui_telaMain_lbFatorL2;
    lv_obj_t *ui_telaMain_lbSetL2;
    lv_obj_t *ui_telaMain_cbHabL2;
    // Cont_L3
    lv_obj_t *ui_telaMain_cont_L3;
    lv_obj_t *ui_telaMain_label_L3;
    lv_obj_t *ui_telaMain_label_v_L3;
    lv_obj_t *ui_telaMain_label_mA_L3;
    lv_obj_t *ui_telaMain_label_fp_L3;
    lv_obj_t *ui_telaMain_linhaSup_L3;
    lv_obj_t *ui_telaMain_linhaInf_L3;
    lv_obj_t *ui_telaMain_label_set_L3;
    lv_obj_t *ui_telaMain_label_saida_L3;
    lv_obj_t *ui_telaMain_lbDisplayL3;
    lv_obj_t *ui_telaMain_lbCorrenteL3;
    lv_obj_t *ui_telaMain_lbFatorL3;
    lv_obj_t *ui_telaMain_lbSetL3;
    lv_obj_t *ui_telaMain_cbHabL3;
    // Container ONOFF
    lv_obj_t *ui_telaMain_cont_OnOff;
    lv_obj_t *ui_telaMain_btnOnOff;
    lv_obj_t *ui_telaMain_label_btnOnOff;
} lv_ui;

void ihmTelaMainInit();
void ihmTelaMainTask();
void createMainUI(lv_ui *ui);
lv_ui *getUiTelaMain(void);

#endif