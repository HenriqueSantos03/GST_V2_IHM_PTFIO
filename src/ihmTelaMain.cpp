#include <Arduino.h>
#include <lvgl.h>
#include "ihmTelaMain.h"
#include "events.h"

void createMainUI(ui_t *ui) {
    // Criar container principal (equivalente a ui_Dashoboard)
    ui->ui_telaMain_dashboard = lv_obj_create(lv_scr_act());
    lv_obj_set_size(ui->ui_telaMain_dashboard, 800, 480);
    lv_obj_set_scrollbar_mode(ui->ui_telaMain_dashboard, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(ui->ui_telaMain_dashboard, LV_OBJ_FLAG_SCROLLABLE); // Desativar scroll
    lv_obj_set_style_bg_opa(ui->ui_telaMain_dashboard, 0, LV_PART_MAIN | LV_STATE_DEFAULT); // Fundo transparente

    // Criar container principal (equivalente a ui_Dashoboard_cont_Main)
    ui->ui_telaMain_containerMain = lv_obj_create(ui->ui_telaMain_dashboard);
    lv_obj_set_pos(ui->ui_telaMain_containerMain, -20, 143);
    lv_obj_set_size(ui->ui_telaMain_containerMain, 624, 336);
    lv_obj_set_scrollbar_mode(ui->ui_telaMain_containerMain, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(ui->ui_telaMain_containerMain, LV_OBJ_FLAG_SCROLLABLE); // Desativar scroll
    lv_obj_add_flag(ui->ui_telaMain_containerMain, LV_OBJ_FLAG_EVENT_BUBBLE); // Evitar que o container capture eventos de scroll

    // Estilo do container principal
    lv_obj_set_style_border_width(ui->ui_telaMain_containerMain, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->ui_telaMain_containerMain, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->ui_telaMain_containerMain, lv_color_hex(0x4A4C4A), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->ui_telaMain_containerMain, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_containerMain, 35, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_containerMain, 250, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_containerMain, lv_color_hex(0x242424), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_containerMain, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_telaMain_containerMain, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_containerMain, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_containerMain, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_containerMain, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_containerMain, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Criar container updown (equivalente a ui_Dashoboard_cont_updown) dentro de ui_telaMain_containerMain
    ui->ui_telaMain_cont_updown = lv_obj_create(ui->ui_telaMain_containerMain);
    lv_obj_set_pos(ui->ui_telaMain_cont_updown, 6, 3);
    lv_obj_set_size(ui->ui_telaMain_cont_updown, 609, 59);
    lv_obj_set_scrollbar_mode(ui->ui_telaMain_cont_updown, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(ui->ui_telaMain_cont_updown, LV_OBJ_FLAG_SCROLLABLE); // Desativar scroll

    // Estilo do container updown
    lv_obj_set_style_border_width(ui->ui_telaMain_cont_updown, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->ui_telaMain_cont_updown, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->ui_telaMain_cont_updown, lv_color_hex(0x4A4C4A), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->ui_telaMain_cont_updown, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_cont_updown, 35, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_cont_updown, 242, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_cont_updown, lv_color_hex(0x5a5b5b), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_cont_updown, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_telaMain_cont_updown, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_cont_updown, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_cont_updown, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_cont_updown, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_cont_updown, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
}

void ihmTelaMainInit() {
    static ui_t ui;
    createMainUI(&ui);
}

void ihmTelaMainTask() {
    // Tarefas periódicas, se necessário
}