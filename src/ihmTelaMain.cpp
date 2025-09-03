#include <Arduino.h>
#include <lvgl.h>
#include "ihmTelaMain.h"
#include "events.h"
#include "fonts/fonts.h"
#include "images/images.h"

uint8_t dashboardCreated = 0;
lv_ui uiTelaMain;

//*******************************************************************************************
// inicializa
//*******************************************************************************************

void createMainUI(lv_ui *ui) {
    lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0x000000), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(lv_scr_act(), LV_OPA_COVER, LV_PART_MAIN);
    // Criar container principal (equivalente a ui_telaMain)
    ui->ui_telaMain_dashboard = lv_obj_create(lv_scr_act());
    lv_obj_set_size(ui->ui_telaMain_dashboard, 800, 480);
    lv_obj_set_pos(ui->ui_telaMain_dashboard, 0, 0); // Posicionar exatamente na origem (0,0)
    lv_obj_set_style_pad_all(ui->ui_telaMain_dashboard, 0, LV_PART_MAIN); // Remover qualquer padding
    lv_obj_set_style_border_width(ui->ui_telaMain_dashboard, 0, LV_PART_MAIN); // Remover bordas
    lv_obj_set_style_radius(ui->ui_telaMain_dashboard, 0, LV_PART_MAIN); // Remover bordas arredondadas
    lv_obj_set_scrollbar_mode(ui->ui_telaMain_dashboard, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(ui->ui_telaMain_dashboard, LV_OBJ_FLAG_SCROLLABLE); // Desativar scroll
    lv_obj_set_style_bg_opa(ui->ui_telaMain_dashboard, 0, LV_PART_MAIN | LV_STATE_DEFAULT); // Fundo transparente

    // Criar container principal (equivalente a ui_telaMain_cont_Main)
    ui->ui_telaMain_containerMain = lv_obj_create(ui->ui_telaMain_dashboard);
    lv_obj_set_pos(ui->ui_telaMain_containerMain, 1, 143); 
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

    // Criar container updown (equivalente a ui_telaMain_cont_updown) dentro de ui_telaMain_containerMain
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
//==================================================================================================================
    //Write codes ui_telaMain_btn_upL1
    ui->ui_telaMain_btn_upL1 = lv_btn_create(ui->ui_telaMain_cont_updown);
    ui->ui_telaMain_label_btn_upL1 = lv_label_create(ui->ui_telaMain_btn_upL1);
    lv_label_set_text(ui->ui_telaMain_label_btn_upL1, "");
    lv_label_set_long_mode(ui->ui_telaMain_label_btn_upL1, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->ui_telaMain_label_btn_upL1, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->ui_telaMain_btn_upL1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->ui_telaMain_label_btn_upL1, LV_PCT(100));
    lv_obj_set_pos(ui->ui_telaMain_btn_upL1, 24, 3);
    lv_obj_set_size(ui->ui_telaMain_btn_upL1, 70, 50);
    lv_obj_add_flag(ui->ui_telaMain_btn_upL1, LV_OBJ_FLAG_HIDDEN); //esconde o botão

    //Write style for ui_telaMain_btn_upL1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->ui_telaMain_btn_upL1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btn_upL1, lv_color_hex(0x29BAE6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_btn_upL1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_telaMain_btn_upL1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_btn_upL1, 17, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_btn_upL1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_btn_upL1, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_btn_upL1, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_btn_upL1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_btn_upL1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui_telaMain_btn_upL1, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->ui_telaMain_btn_upL1, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btn_upL1, lv_color_hex(0x18C220), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_btn_upL1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->ui_telaMain_btn_upL1, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->ui_telaMain_btn_upL1, 17, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_btn_upL1, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->ui_telaMain_btn_upL1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->ui_telaMain_btn_upL1, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->ui_telaMain_btn_upL1, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write codes ui_telaMain_img_upL1
    ui->ui_telaMain_img_upL1 = lv_img_create(ui->ui_telaMain_cont_updown);
    lv_obj_add_flag(ui->ui_telaMain_img_upL1, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->ui_telaMain_img_upL1, &_arrow_up_alpha_15x10);
    lv_img_set_pivot(ui->ui_telaMain_img_upL1, 50,50);
    lv_img_set_angle(ui->ui_telaMain_img_upL1, 0);
    lv_obj_set_pos(ui->ui_telaMain_img_upL1, 54, 24);
    lv_obj_set_size(ui->ui_telaMain_img_upL1, 15, 10);
    lv_obj_add_flag(ui->ui_telaMain_img_upL1, LV_OBJ_FLAG_HIDDEN); // esconde o objeto na inicialização

    //Write style for ui_telaMain_img_upL1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_telaMain_img_upL1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_telaMain_img_upL1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_img_upL1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_telaMain_img_upL1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_btn_downL1
    ui->ui_telaMain_btn_downL1 = lv_btn_create(ui->ui_telaMain_cont_updown);
    ui->ui_telaMain_label_btn_downL1 = lv_label_create(ui->ui_telaMain_btn_downL1);
    lv_label_set_text(ui->ui_telaMain_label_btn_downL1, "");
    lv_label_set_long_mode(ui->ui_telaMain_label_btn_downL1, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->ui_telaMain_label_btn_downL1, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->ui_telaMain_btn_downL1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->ui_telaMain_label_btn_downL1, LV_PCT(100));
    lv_obj_set_pos(ui->ui_telaMain_btn_downL1, 110, 3);
    lv_obj_set_size(ui->ui_telaMain_btn_downL1, 70, 50);
    lv_obj_add_flag(ui->ui_telaMain_btn_downL1, LV_OBJ_FLAG_HIDDEN); //esconde o botão

    //Write style for ui_telaMain_btn_downL1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->ui_telaMain_btn_downL1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btn_downL1, lv_color_hex(0x29BAE6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_btn_downL1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_telaMain_btn_downL1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_btn_downL1, 17, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_btn_downL1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_btn_downL1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_btn_downL1, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_btn_downL1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_btn_downL1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui_telaMain_btn_downL1, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->ui_telaMain_btn_downL1, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btn_downL1, lv_color_hex(0x18C220), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_btn_downL1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->ui_telaMain_btn_downL1, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->ui_telaMain_btn_downL1, 17, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_btn_downL1, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->ui_telaMain_btn_downL1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->ui_telaMain_btn_downL1, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->ui_telaMain_btn_downL1, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write codes ui_telaMain_img_downL1
    ui->ui_telaMain_img_downL1 = lv_img_create(ui->ui_telaMain_cont_updown);
    lv_obj_add_flag(ui->ui_telaMain_img_downL1, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->ui_telaMain_img_downL1, &_arrow_down_alpha_15x10);
    lv_img_set_pivot(ui->ui_telaMain_img_downL1, 50,50);
    lv_img_set_angle(ui->ui_telaMain_img_downL1, 0);
    lv_obj_set_pos(ui->ui_telaMain_img_downL1, 139, 24);
    lv_obj_set_size(ui->ui_telaMain_img_downL1, 15, 10);
    lv_obj_add_flag(ui->ui_telaMain_img_downL1, LV_OBJ_FLAG_HIDDEN); // esconde o objeto na inicialização

    //Write style for ui_telaMain_img_downL1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_telaMain_img_downL1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_telaMain_img_downL1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_img_downL1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_telaMain_img_downL1, true, LV_PART_MAIN|LV_STATE_DEFAULT);
//==================================================================================================================
    //Write codes ui_telaMain_btn_upL2
    ui->ui_telaMain_btn_upL2 = lv_btn_create(ui->ui_telaMain_cont_updown);
    ui->ui_telaMain_label_btn_upL2 = lv_label_create(ui->ui_telaMain_btn_upL2);
    lv_label_set_text(ui->ui_telaMain_label_btn_upL2, "");
    lv_label_set_long_mode(ui->ui_telaMain_label_btn_upL2, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->ui_telaMain_label_btn_upL2, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->ui_telaMain_btn_upL2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->ui_telaMain_label_btn_upL2, LV_PCT(100));
    lv_obj_set_pos(ui->ui_telaMain_btn_upL2, 222, 3);
    lv_obj_set_size(ui->ui_telaMain_btn_upL2, 70, 50);

    //Write style for ui_telaMain_btn_upL2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->ui_telaMain_btn_upL2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btn_upL2, lv_color_hex(0x29BAE6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_btn_upL2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_telaMain_btn_upL2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_btn_upL2, 17, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_btn_upL2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_btn_upL2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_btn_upL2, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_btn_upL2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_btn_upL2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui_telaMain_btn_upL2, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->ui_telaMain_btn_upL2, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btn_upL2, lv_color_hex(0x18C220), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_btn_upL2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->ui_telaMain_btn_upL2, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->ui_telaMain_btn_upL2, 17, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_btn_upL2, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->ui_telaMain_btn_upL2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->ui_telaMain_btn_upL2, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->ui_telaMain_btn_upL2, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write codes ui_telaMain_img_upL2
    ui->ui_telaMain_img_upL2 = lv_img_create(ui->ui_telaMain_cont_updown);
    lv_obj_add_flag(ui->ui_telaMain_img_upL2, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->ui_telaMain_img_upL2, &_arrow_up_alpha_15x10);
    lv_img_set_pivot(ui->ui_telaMain_img_upL2, 50,50);
    lv_img_set_angle(ui->ui_telaMain_img_upL2, 0);
    lv_obj_set_pos(ui->ui_telaMain_img_upL2, 249, 23);
    lv_obj_set_size(ui->ui_telaMain_img_upL2, 15, 10);

    //Write style for ui_telaMain_img_upL2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_telaMain_img_upL2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_telaMain_img_upL2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_img_upL2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_telaMain_img_upL2, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_btn_downL2
    ui->ui_telaMain_btn_downL2 = lv_btn_create(ui->ui_telaMain_cont_updown);
    ui->ui_telaMain_label_btn_downL2 = lv_label_create(ui->ui_telaMain_btn_downL2);
    lv_label_set_text(ui->ui_telaMain_label_btn_downL2, "");
    lv_label_set_long_mode(ui->ui_telaMain_label_btn_downL2, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->ui_telaMain_label_btn_downL2, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->ui_telaMain_btn_downL2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->ui_telaMain_label_btn_downL2, LV_PCT(100));
    lv_obj_set_pos(ui->ui_telaMain_btn_downL2, 311, 3);
    lv_obj_set_size(ui->ui_telaMain_btn_downL2, 70, 50);

    //Write style for ui_telaMain_btn_downL2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->ui_telaMain_btn_downL2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btn_downL2, lv_color_hex(0x29BAE6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_btn_downL2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_telaMain_btn_downL2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_btn_downL2, 17, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_btn_downL2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_btn_downL2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_btn_downL2, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_btn_downL2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_btn_downL2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui_telaMain_btn_downL2, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->ui_telaMain_btn_downL2, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btn_downL2, lv_color_hex(0x18C220), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_btn_downL2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->ui_telaMain_btn_downL2, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->ui_telaMain_btn_downL2, 17, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_btn_downL2, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->ui_telaMain_btn_downL2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->ui_telaMain_btn_downL2, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->ui_telaMain_btn_downL2, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write codes ui_telaMain_img_downL2
    ui->ui_telaMain_img_downL2 = lv_img_create(ui->ui_telaMain_cont_updown);
    lv_obj_add_flag(ui->ui_telaMain_img_downL2, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->ui_telaMain_img_downL2, &_arrow_down_alpha_15x10);
    lv_img_set_pivot(ui->ui_telaMain_img_downL2, 50,50);
    lv_img_set_angle(ui->ui_telaMain_img_downL2, 0);
    lv_obj_set_pos(ui->ui_telaMain_img_downL2, 339, 25);
    lv_obj_set_size(ui->ui_telaMain_img_downL2, 15, 10);

    //Write style for ui_telaMain_img_downL2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_telaMain_img_downL2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_telaMain_img_downL2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_img_downL2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_telaMain_img_downL2, true, LV_PART_MAIN|LV_STATE_DEFAULT);
//==================================================================================================================
    //Write codes ui_telaMain_btn_upL3
    ui->ui_telaMain_btn_upL3 = lv_btn_create(ui->ui_telaMain_cont_updown);
    ui->ui_telaMain_label_btn_upL3 = lv_label_create(ui->ui_telaMain_btn_upL3);
    lv_label_set_text(ui->ui_telaMain_label_btn_upL3, "");
    lv_label_set_long_mode(ui->ui_telaMain_label_btn_upL3, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->ui_telaMain_label_btn_upL3, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->ui_telaMain_btn_upL3, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->ui_telaMain_label_btn_upL3, LV_PCT(100));
    lv_obj_set_pos(ui->ui_telaMain_btn_upL3, 432, 3);
    lv_obj_set_size(ui->ui_telaMain_btn_upL3, 70, 50);
    lv_obj_add_flag(ui->ui_telaMain_btn_upL3, LV_OBJ_FLAG_HIDDEN); //esconde o botão

    //Write style for ui_telaMain_btn_upL3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->ui_telaMain_btn_upL3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btn_upL3, lv_color_hex(0x29BAE6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_btn_upL3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_telaMain_btn_upL3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_btn_upL3, 17, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_btn_upL3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_btn_upL3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_btn_upL3, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_btn_upL3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_btn_upL3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui_telaMain_btn_upL3, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->ui_telaMain_btn_upL3, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btn_upL3, lv_color_hex(0x18C220), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_btn_upL3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->ui_telaMain_btn_upL3, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->ui_telaMain_btn_upL3, 17, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_btn_upL3, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->ui_telaMain_btn_upL3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->ui_telaMain_btn_upL3, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->ui_telaMain_btn_upL3, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write codes ui_telaMain_img_upL3
    ui->ui_telaMain_img_upL3 = lv_img_create(ui->ui_telaMain_cont_updown);
    lv_obj_add_flag(ui->ui_telaMain_img_upL3, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->ui_telaMain_img_upL3, &_arrow_up_alpha_15x10);
    lv_img_set_pivot(ui->ui_telaMain_img_upL3, 50,50);
    lv_img_set_angle(ui->ui_telaMain_img_upL3, 0);
    lv_obj_set_pos(ui->ui_telaMain_img_upL3, 462, 24);
    lv_obj_set_size(ui->ui_telaMain_img_upL3, 15, 10);
    lv_obj_add_flag(ui->ui_telaMain_img_upL3, LV_OBJ_FLAG_HIDDEN); // esconde o objeto na inicialização

    //Write style for ui_telaMain_img_upL3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_telaMain_img_upL3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_telaMain_img_upL3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_img_upL3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_telaMain_img_upL3, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_btn_downL3
    ui->ui_telaMain_btn_downL3 = lv_btn_create(ui->ui_telaMain_cont_updown);
    ui->ui_telaMain_label_btn_downL3 = lv_label_create(ui->ui_telaMain_btn_downL3);
    lv_label_set_text(ui->ui_telaMain_label_btn_downL3, "");
    lv_label_set_long_mode(ui->ui_telaMain_label_btn_downL3, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->ui_telaMain_label_btn_downL3, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->ui_telaMain_btn_downL3, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->ui_telaMain_label_btn_downL3, LV_PCT(100));
    lv_obj_set_pos(ui->ui_telaMain_btn_downL3, 521, 3);
    lv_obj_set_size(ui->ui_telaMain_btn_downL3, 70, 50);
    lv_obj_add_flag(ui->ui_telaMain_btn_downL3, LV_OBJ_FLAG_HIDDEN); //esconde o botão

    //Write style for ui_telaMain_btn_downL3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->ui_telaMain_btn_downL3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btn_downL3, lv_color_hex(0x29BAE6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_btn_downL3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_telaMain_btn_downL3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_btn_downL3, 17, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_btn_downL3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_btn_downL3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_btn_downL3, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_btn_downL3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_btn_downL3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui_telaMain_btn_downL3, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->ui_telaMain_btn_downL3, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btn_downL3, lv_color_hex(0x18C220), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_btn_downL3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->ui_telaMain_btn_downL3, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->ui_telaMain_btn_downL3, 17, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_btn_downL3, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->ui_telaMain_btn_downL3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->ui_telaMain_btn_downL3, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->ui_telaMain_btn_downL3, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write codes ui_telaMain_img_downL3
    ui->ui_telaMain_img_downL3 = lv_img_create(ui->ui_telaMain_cont_updown);
    lv_obj_add_flag(ui->ui_telaMain_img_downL3, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->ui_telaMain_img_downL3, &_arrow_down_alpha_15x10);
    lv_img_set_pivot(ui->ui_telaMain_img_downL3, 50,50);
    lv_img_set_angle(ui->ui_telaMain_img_downL3, 0);
    lv_obj_set_pos(ui->ui_telaMain_img_downL3, 550, 24);
    lv_obj_set_size(ui->ui_telaMain_img_downL3, 15, 10);
    lv_obj_add_flag(ui->ui_telaMain_img_downL3, LV_OBJ_FLAG_HIDDEN); // esconde o objeto na inicialização

    //Write style for ui_telaMain_img_downL3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_telaMain_img_downL3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_telaMain_img_downL3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_img_downL3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_telaMain_img_downL3, true, LV_PART_MAIN|LV_STATE_DEFAULT);
//==================================================================================================================
 //Write codes ui_telaMain_cont_avancado
    ui->ui_telaMain_cont_avancado = lv_obj_create(ui->ui_telaMain_containerMain);
    lv_obj_set_pos(ui->ui_telaMain_cont_avancado, 248, 70);
    lv_obj_set_size(ui->ui_telaMain_cont_avancado, 365, 260);
    lv_obj_set_scrollbar_mode(ui->ui_telaMain_cont_avancado, LV_SCROLLBAR_MODE_OFF);

    //Write style for ui_telaMain_cont_avancado, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_telaMain_cont_avancado, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->ui_telaMain_cont_avancado, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->ui_telaMain_cont_avancado, lv_color_hex(0x4A4C4A), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->ui_telaMain_cont_avancado, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_cont_avancado, 35, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_cont_avancado, 242, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_cont_avancado, lv_color_hex(0x5a5b5b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_cont_avancado, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_telaMain_cont_avancado, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_cont_avancado, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_cont_avancado, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_cont_avancado, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_cont_avancado, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_btnPercent1
    ui->ui_telaMain_btnPercent1 = lv_btn_create(ui->ui_telaMain_cont_avancado);
    ui->ui_telaMain_label_btnPercent1 = lv_label_create(ui->ui_telaMain_btnPercent1);
    lv_label_set_text(ui->ui_telaMain_label_btnPercent1, "40%");
    lv_label_set_long_mode(ui->ui_telaMain_label_btnPercent1, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->ui_telaMain_label_btnPercent1, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->ui_telaMain_btnPercent1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->ui_telaMain_label_btnPercent1, LV_PCT(100));
    lv_obj_set_pos(ui->ui_telaMain_btnPercent1, 18, 13);
    lv_obj_set_size(ui->ui_telaMain_btnPercent1, 60, 40);

    //Write style for ui_telaMain_btnPercent1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->ui_telaMain_btnPercent1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btnPercent1, lv_color_hex(0x29BAE6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_btnPercent1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_telaMain_btnPercent1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_btnPercent1, 17, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_btnPercent1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_btnPercent1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_btnPercent1, &lv_font_montserratMedium_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_btnPercent1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_btnPercent1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui_telaMain_btnPercent1, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->ui_telaMain_btnPercent1, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btnPercent1, lv_color_hex(0x18C220), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_btnPercent1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->ui_telaMain_btnPercent1, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->ui_telaMain_btnPercent1, 17, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_btnPercent1, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->ui_telaMain_btnPercent1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->ui_telaMain_btnPercent1, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->ui_telaMain_btnPercent1, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write codes ui_telaMain_btnPercent2
    ui->ui_telaMain_btnPercent2 = lv_btn_create(ui->ui_telaMain_cont_avancado);
    ui->ui_telaMain_label_btnPercent2 = lv_label_create(ui->ui_telaMain_btnPercent2);
    lv_label_set_text(ui->ui_telaMain_label_btnPercent2, "60%");
    lv_label_set_long_mode(ui->ui_telaMain_label_btnPercent2, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->ui_telaMain_label_btnPercent2, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->ui_telaMain_btnPercent2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->ui_telaMain_label_btnPercent2, LV_PCT(100));
    lv_obj_set_pos(ui->ui_telaMain_btnPercent2, 18, 61);
    lv_obj_set_size(ui->ui_telaMain_btnPercent2, 60, 40);

    //Write style for ui_telaMain_btnPercent2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->ui_telaMain_btnPercent2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btnPercent2, lv_color_hex(0x29BAE6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_btnPercent2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_telaMain_btnPercent2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_btnPercent2, 17, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_btnPercent2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_btnPercent2, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_btnPercent2, &lv_font_montserratMedium_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_btnPercent2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_btnPercent2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui_telaMain_btnPercent2, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->ui_telaMain_btnPercent2, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btnPercent2, lv_color_hex(0x18C220), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_btnPercent2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->ui_telaMain_btnPercent2, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->ui_telaMain_btnPercent2, 17, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_btnPercent2, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->ui_telaMain_btnPercent2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->ui_telaMain_btnPercent2, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->ui_telaMain_btnPercent2, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write codes ui_telaMain_btnPercent3
    ui->ui_telaMain_btnPercent3 = lv_btn_create(ui->ui_telaMain_cont_avancado);
    ui->ui_telaMain_label_btnPercent3 = lv_label_create(ui->ui_telaMain_btnPercent3);
    lv_label_set_text(ui->ui_telaMain_label_btnPercent3, "80%");
    lv_label_set_long_mode(ui->ui_telaMain_label_btnPercent3, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->ui_telaMain_label_btnPercent3, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->ui_telaMain_btnPercent3, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->ui_telaMain_label_btnPercent3, LV_PCT(100));
    lv_obj_set_pos(ui->ui_telaMain_btnPercent3, 18, 108);
    lv_obj_set_size(ui->ui_telaMain_btnPercent3, 60, 40);

    //Write style for ui_telaMain_btnPercent3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->ui_telaMain_btnPercent3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btnPercent3, lv_color_hex(0x29BAE6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_btnPercent3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_telaMain_btnPercent3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_btnPercent3, 17, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_btnPercent3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_btnPercent3, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_btnPercent3, &lv_font_montserratMedium_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_btnPercent3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_btnPercent3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui_telaMain_btnPercent3, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->ui_telaMain_btnPercent3, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btnPercent3, lv_color_hex(0x18C220), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_btnPercent3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->ui_telaMain_btnPercent3, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->ui_telaMain_btnPercent3, 17, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_btnPercent3, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->ui_telaMain_btnPercent3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->ui_telaMain_btnPercent3, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->ui_telaMain_btnPercent3, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write codes ui_telaMain_btnPercent4
    ui->ui_telaMain_btnPercent4 = lv_btn_create(ui->ui_telaMain_cont_avancado);
    ui->ui_telaMain_label_btnPercent4 = lv_label_create(ui->ui_telaMain_btnPercent4);
    lv_label_set_text(ui->ui_telaMain_label_btnPercent4, "100%");
    lv_label_set_long_mode(ui->ui_telaMain_label_btnPercent4, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->ui_telaMain_label_btnPercent4, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->ui_telaMain_btnPercent4, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->ui_telaMain_label_btnPercent4, LV_PCT(100));
    lv_obj_set_pos(ui->ui_telaMain_btnPercent4, 18, 157);
    lv_obj_set_size(ui->ui_telaMain_btnPercent4, 60, 40);

    //Write style for ui_telaMain_btnPercent4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->ui_telaMain_btnPercent4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btnPercent4, lv_color_hex(0x29BAE6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_btnPercent4, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_telaMain_btnPercent4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_btnPercent4, 17, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_btnPercent4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_btnPercent4, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_btnPercent4, &lv_font_montserratMedium_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_btnPercent4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_btnPercent4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui_telaMain_btnPercent4, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->ui_telaMain_btnPercent4, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btnPercent4, lv_color_hex(0x18C220), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_btnPercent4, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->ui_telaMain_btnPercent4, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->ui_telaMain_btnPercent4, 17, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_btnPercent4, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->ui_telaMain_btnPercent4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->ui_telaMain_btnPercent4, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->ui_telaMain_btnPercent4, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write codes ui_telaMain_btnPercent5
    ui->ui_telaMain_btnPercent5 = lv_btn_create(ui->ui_telaMain_cont_avancado);
    ui->ui_telaMain_label_btnPercent5 = lv_label_create(ui->ui_telaMain_btnPercent5);
    lv_label_set_text(ui->ui_telaMain_label_btnPercent5, "120%");
    lv_label_set_long_mode(ui->ui_telaMain_label_btnPercent5, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->ui_telaMain_label_btnPercent5, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->ui_telaMain_btnPercent5, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->ui_telaMain_label_btnPercent5, LV_PCT(100));
    lv_obj_set_pos(ui->ui_telaMain_btnPercent5, 18, 205);
    lv_obj_set_size(ui->ui_telaMain_btnPercent5, 60, 40);

    //Write style for ui_telaMain_btnPercent5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_telaMain_btnPercent5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_btnPercent5, 17, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_btnPercent5, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_btnPercent5, &lv_font_montserratMedium_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_btnPercent5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_btnPercent5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_btnPercent5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btnPercent5, lv_color_hex(0x29BAE6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_btnPercent5, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_btnPercent5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui_telaMain_btnPercent5, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->ui_telaMain_btnPercent5, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btnPercent5, lv_color_hex(0x18C220), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_btnPercent5, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->ui_telaMain_btnPercent5, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->ui_telaMain_btnPercent5, 17, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_btnPercent5, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->ui_telaMain_btnPercent5, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->ui_telaMain_btnPercent5, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->ui_telaMain_btnPercent5, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write codes ui_telaMain_btnConfig
    ui->ui_telaMain_btnConfig = lv_btn_create(ui->ui_telaMain_cont_avancado);
    ui->ui_telaMain_label_btnConfig = lv_label_create(ui->ui_telaMain_btnConfig);
    lv_label_set_text(ui->ui_telaMain_label_btnConfig, "Config");
    lv_label_set_long_mode(ui->ui_telaMain_label_btnConfig, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->ui_telaMain_label_btnConfig, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->ui_telaMain_btnConfig, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->ui_telaMain_label_btnConfig, LV_PCT(100));
    lv_obj_set_pos(ui->ui_telaMain_btnConfig, 225, 64);
    lv_obj_set_size(ui->ui_telaMain_btnConfig, 77, 40);

    //Write style for ui_telaMain_btnConfig, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_telaMain_btnConfig, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_btnConfig, 17, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_btnConfig, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_btnConfig, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_btnConfig, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_btnConfig, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_btnConfig, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btnConfig, lv_color_hex(0x29BAE6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_btnConfig, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_btnConfig, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui_telaMain_btnConfig, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->ui_telaMain_btnConfig, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btnConfig, lv_color_hex(0x18C220), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_btnConfig, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->ui_telaMain_btnConfig, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->ui_telaMain_btnConfig, 17, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_btnConfig, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->ui_telaMain_btnConfig, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->ui_telaMain_btnConfig, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->ui_telaMain_btnConfig, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write codes ui_telaMain_btnNominal
    ui->ui_telaMain_btnNominal = lv_btn_create(ui->ui_telaMain_cont_avancado);
    ui->ui_telaMain_label_btnNominal = lv_label_create(ui->ui_telaMain_btnNominal);
    lv_label_set_text(ui->ui_telaMain_label_btnNominal, "Nominal");
    lv_label_set_long_mode(ui->ui_telaMain_label_btnNominal, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->ui_telaMain_label_btnNominal, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->ui_telaMain_btnNominal, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->ui_telaMain_label_btnNominal, LV_PCT(100));
    lv_obj_set_pos(ui->ui_telaMain_btnNominal, 165, 13);
    lv_obj_set_size(ui->ui_telaMain_btnNominal, 90, 45);

    //Write style for ui_telaMain_btnNominal, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_telaMain_btnNominal, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_btnNominal, 17, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_btnNominal, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_btnNominal, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_btnNominal, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_btnNominal, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_btnNominal, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btnNominal, lv_color_hex(0x29BAE6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_btnNominal, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_btnNominal, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui_telaMain_btnNominal, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_shadow_width(ui->ui_telaMain_btnNominal, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_btnNominal, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btnNominal, lv_color_hex(0x18C220), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_btnNominal, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->ui_telaMain_btnNominal, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->ui_telaMain_btnNominal, 17, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->ui_telaMain_btnNominal, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->ui_telaMain_btnNominal, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->ui_telaMain_btnNominal, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write codes ui_telaMain_btnAgrupar
    ui->ui_telaMain_btnAgrupar = lv_btn_create(ui->ui_telaMain_cont_avancado);
    ui->ui_telaMain_label_btnAgrupar = lv_label_create(ui->ui_telaMain_btnAgrupar);
    lv_label_set_text(ui->ui_telaMain_label_btnAgrupar, "Desagrupar");
    lv_label_set_long_mode(ui->ui_telaMain_label_btnAgrupar, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->ui_telaMain_label_btnAgrupar, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->ui_telaMain_btnAgrupar, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->ui_telaMain_label_btnAgrupar, LV_PCT(100));
    lv_obj_set_pos(ui->ui_telaMain_btnAgrupar, 265, 13);
    lv_obj_set_size(ui->ui_telaMain_btnAgrupar, 90, 45);

    //Write style for ui_telaMain_btnAgrupar, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->ui_telaMain_btnAgrupar, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btnAgrupar, lv_color_hex(0x29BAE6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_btnAgrupar, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_btnAgrupar, 17, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_btnAgrupar, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_telaMain_btnAgrupar, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_btnAgrupar, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_btnAgrupar, &lv_font_montserratMedium_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_btnAgrupar, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_btnAgrupar, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui_telaMain_btnAgrupar, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_shadow_width(ui->ui_telaMain_btnAgrupar, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_btnAgrupar, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btnAgrupar, lv_color_hex(0x18C220), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_btnAgrupar, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->ui_telaMain_btnAgrupar, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->ui_telaMain_btnAgrupar, 17, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->ui_telaMain_btnAgrupar, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->ui_telaMain_btnAgrupar, &lv_font_montserratMedium_14, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->ui_telaMain_btnAgrupar, 255, LV_PART_MAIN|LV_STATE_PRESSED);
//==================================================================================================================

    //Write codes ui_telaMain_cont_selMode
    ui->ui_telaMain_cont_selMode = lv_obj_create(ui->ui_telaMain_cont_avancado);
    lv_obj_set_pos(ui->ui_telaMain_cont_selMode, 90, 13);
    lv_obj_set_size(ui->ui_telaMain_cont_selMode, 67, 75);
    lv_obj_set_scrollbar_mode(ui->ui_telaMain_cont_selMode, LV_SCROLLBAR_MODE_OFF);

    //Write style for ui_telaMain_cont_selMode, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_telaMain_cont_selMode, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->ui_telaMain_cont_selMode, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->ui_telaMain_cont_selMode, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->ui_telaMain_cont_selMode, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_cont_selMode, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_cont_selMode, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_cont_selMode, lv_color_hex(0xa2aaa8), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_cont_selMode, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_telaMain_cont_selMode, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_cont_selMode, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_cont_selMode, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_cont_selMode, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_cont_selMode, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_selModePercent
    ui->ui_telaMain_selModePercent = lv_checkbox_create(ui->ui_telaMain_cont_selMode);
    lv_checkbox_set_text(ui->ui_telaMain_selModePercent, "%");
    lv_obj_set_pos(ui->ui_telaMain_selModePercent, 6, 4);
    lv_obj_add_state(ui->ui_telaMain_selModePercent, LV_STATE_CHECKED | LV_STATE_DISABLED); //marca e desabilita a checkbox

    //Write style for ui_telaMain_selModePercent, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->ui_telaMain_selModePercent, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_selModePercent, lv_color_hex(0xa2aaa8), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_selModePercent, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_telaMain_selModePercent, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_selModePercent, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_selModePercent, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_selModePercent, lv_color_hex(0x0D3055), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_selModePercent, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_selModePercent, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_telaMain_selModePercent, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_telaMain_selModePercent, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_selModePercent, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_selModePercent, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_selModePercent, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui_telaMain_selModePercent, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->ui_telaMain_selModePercent, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_selModePercent, lv_color_hex(0xffffff), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_selModePercent, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_telaMain_selModePercent, 2, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->ui_telaMain_selModePercent, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->ui_telaMain_selModePercent, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->ui_telaMain_selModePercent, LV_BORDER_SIDE_FULL, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_selModePercent, 6, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(ui->ui_telaMain_selModePercent, 3, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_selModeGrandeza
    ui->ui_telaMain_selModeGrandeza = lv_checkbox_create(ui->ui_telaMain_cont_selMode);
    lv_checkbox_set_text(ui->ui_telaMain_selModeGrandeza, "V");
    lv_obj_set_pos(ui->ui_telaMain_selModeGrandeza, 6, 39);

    //Write style for ui_telaMain_selModeGrandeza, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_telaMain_selModeGrandeza, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_selModeGrandeza, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_selModeGrandeza, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_selModeGrandeza, lv_color_hex(0xa2aaa8), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_selModeGrandeza, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_selModeGrandeza, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_selModeGrandeza, lv_color_hex(0x0D3055), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_selModeGrandeza, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_selModeGrandeza, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_telaMain_selModeGrandeza, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_telaMain_selModeGrandeza, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_selModeGrandeza, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_selModeGrandeza, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_selModeGrandeza, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui_telaMain_selModeGrandeza, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->ui_telaMain_selModeGrandeza, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_selModeGrandeza, lv_color_hex(0xffffff), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_selModeGrandeza, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_telaMain_selModeGrandeza, 2, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->ui_telaMain_selModeGrandeza, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->ui_telaMain_selModeGrandeza, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->ui_telaMain_selModeGrandeza, LV_BORDER_SIDE_FULL, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_selModeGrandeza, 6, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(ui->ui_telaMain_selModeGrandeza, 3, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_cont_upPasso
    ui->ui_telaMain_cont_upPasso = lv_obj_create(ui->ui_telaMain_cont_avancado);
    lv_obj_set_pos(ui->ui_telaMain_cont_upPasso, 90, 110);
    lv_obj_set_size(ui->ui_telaMain_cont_upPasso, 67, 135);
    lv_obj_set_scrollbar_mode(ui->ui_telaMain_cont_upPasso, LV_SCROLLBAR_MODE_OFF);

    //Write style for ui_telaMain_cont_upPasso, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_telaMain_cont_upPasso, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->ui_telaMain_cont_upPasso, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->ui_telaMain_cont_upPasso, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->ui_telaMain_cont_upPasso, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_cont_upPasso, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_cont_upPasso, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_cont_upPasso, lv_color_hex(0xa2aaa8), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_cont_upPasso, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_telaMain_cont_upPasso, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_cont_upPasso, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_cont_upPasso, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_cont_upPasso, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_cont_upPasso, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_selPasso1
    ui->ui_telaMain_selPasso1 = lv_checkbox_create(ui->ui_telaMain_cont_upPasso);
    lv_checkbox_set_text(ui->ui_telaMain_selPasso1, "0,5");
    lv_obj_set_pos(ui->ui_telaMain_selPasso1, 2, 3);
    lv_obj_add_state(ui->ui_telaMain_selPasso1, LV_STATE_CHECKED | LV_STATE_DISABLED); //marca e desabilita a checkbox

    //Write style for ui_telaMain_selPasso1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->ui_telaMain_selPasso1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_selPasso1, lv_color_hex(0xa2aaa8), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_selPasso1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_telaMain_selPasso1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_selPasso1, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_selPasso1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_selPasso1, lv_color_hex(0x0D3055), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_selPasso1, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_selPasso1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_telaMain_selPasso1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_telaMain_selPasso1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_selPasso1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_selPasso1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_selPasso1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui_telaMain_selPasso1, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->ui_telaMain_selPasso1, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_selPasso1, lv_color_hex(0xffffff), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_selPasso1, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_telaMain_selPasso1, 2, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->ui_telaMain_selPasso1, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->ui_telaMain_selPasso1, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->ui_telaMain_selPasso1, LV_BORDER_SIDE_FULL, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_selPasso1, 6, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(ui->ui_telaMain_selPasso1, 3, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_selPasso2
    ui->ui_telaMain_selPasso2 = lv_checkbox_create(ui->ui_telaMain_cont_upPasso);
    lv_checkbox_set_text(ui->ui_telaMain_selPasso2, "1");
    lv_obj_set_pos(ui->ui_telaMain_selPasso2, 2, 33);

    //Write style for ui_telaMain_selPasso2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->ui_telaMain_selPasso2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_selPasso2, lv_color_hex(0xa2aaa8), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_selPasso2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_telaMain_selPasso2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_selPasso2, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_selPasso2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_selPasso2, lv_color_hex(0x0D3055), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_selPasso2, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_selPasso2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_telaMain_selPasso2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_telaMain_selPasso2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_selPasso2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_selPasso2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_selPasso2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui_telaMain_selPasso2, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->ui_telaMain_selPasso2, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_selPasso2, lv_color_hex(0xffffff), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_selPasso2, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_telaMain_selPasso2, 2, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->ui_telaMain_selPasso2, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->ui_telaMain_selPasso2, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->ui_telaMain_selPasso2, LV_BORDER_SIDE_FULL, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_selPasso2, 6, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(ui->ui_telaMain_selPasso2, 3, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_selPasso3
    ui->ui_telaMain_selPasso3 = lv_checkbox_create(ui->ui_telaMain_cont_upPasso);
    lv_checkbox_set_text(ui->ui_telaMain_selPasso3, "5");
    lv_obj_set_pos(ui->ui_telaMain_selPasso3, 2, 63);

    //Write style for ui_telaMain_selPasso3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->ui_telaMain_selPasso3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_selPasso3, lv_color_hex(0xa2aaa8), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_selPasso3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_telaMain_selPasso3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_selPasso3, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_selPasso3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_selPasso3, lv_color_hex(0x0D3055), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_selPasso3, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_selPasso3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_telaMain_selPasso3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_telaMain_selPasso3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_selPasso3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_selPasso3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_selPasso3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui_telaMain_selPasso3, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->ui_telaMain_selPasso3, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_selPasso3, lv_color_hex(0xffffff), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_selPasso3, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_telaMain_selPasso3, 2, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->ui_telaMain_selPasso3, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->ui_telaMain_selPasso3, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->ui_telaMain_selPasso3, LV_BORDER_SIDE_FULL, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_selPasso3, 6, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(ui->ui_telaMain_selPasso3, 3, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_selPasso4
    ui->ui_telaMain_selPasso4 = lv_checkbox_create(ui->ui_telaMain_cont_upPasso);
    lv_checkbox_set_text(ui->ui_telaMain_selPasso4, "10");
    lv_obj_set_pos(ui->ui_telaMain_selPasso4, 2, 93);

    //Write style for ui_telaMain_selPasso4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_telaMain_selPasso4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_selPasso4, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_selPasso4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_selPasso4, lv_color_hex(0xa2aaa8), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_selPasso4, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_selPasso4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_selPasso4, lv_color_hex(0x0D3055), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_selPasso4, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_selPasso4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_telaMain_selPasso4, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_telaMain_selPasso4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_selPasso4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_selPasso4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_selPasso4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui_telaMain_selPasso4, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->ui_telaMain_selPasso4, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_selPasso4, lv_color_hex(0xffffff), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_selPasso4, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_telaMain_selPasso4, 2, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->ui_telaMain_selPasso4, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->ui_telaMain_selPasso4, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->ui_telaMain_selPasso4, LV_BORDER_SIDE_FULL, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_selPasso4, 6, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(ui->ui_telaMain_selPasso4, 3, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_cont_sequencia
    ui->ui_telaMain_cont_sequencia = lv_obj_create(ui->ui_telaMain_cont_avancado);
    lv_obj_set_pos(ui->ui_telaMain_cont_sequencia, 164, 108);
    lv_obj_set_size(ui->ui_telaMain_cont_sequencia, 191, 145);
    lv_obj_set_scrollbar_mode(ui->ui_telaMain_cont_sequencia, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(ui->ui_telaMain_cont_sequencia, LV_OBJ_FLAG_SCROLLABLE); //Make the object non-scrollable      

    //Write style for ui_telaMain_cont_sequencia, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_telaMain_cont_sequencia, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->ui_telaMain_cont_sequencia, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->ui_telaMain_cont_sequencia, lv_color_hex(0x4A4C4A), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->ui_telaMain_cont_sequencia, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_cont_sequencia, 35, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_cont_sequencia, 242, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_cont_sequencia, lv_color_hex(0x414242), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_cont_sequencia, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_telaMain_cont_sequencia, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_cont_sequencia, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_cont_sequencia, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_cont_sequencia, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_cont_sequencia, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_label_seqFase
    ui->ui_telaMain_label_seqFase = lv_label_create(ui->ui_telaMain_cont_sequencia);
    lv_label_set_text(ui->ui_telaMain_label_seqFase, "Sequencia de Fase");
    lv_label_set_long_mode(ui->ui_telaMain_label_seqFase, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_telaMain_label_seqFase, 15, 125);
    lv_obj_set_size(ui->ui_telaMain_label_seqFase, 158, 28);

    //Write style for ui_telaMain_label_seqFase, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->ui_telaMain_label_seqFase, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_telaMain_label_seqFase, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_label_seqFase, lv_color_hex(0xa6ff00), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_label_seqFase, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_label_seqFase, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_telaMain_label_seqFase, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_telaMain_label_seqFase, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_label_seqFase, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_label_seqFase, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_telaMain_label_seqFase, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_label_seqFase, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_label_seqFase, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_label_seqFase, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_label_seqFase, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_label_seq_l1
    ui->ui_telaMain_label_seq_l1 = lv_label_create(ui->ui_telaMain_cont_sequencia);
    lv_label_set_text(ui->ui_telaMain_label_seq_l1, "L1");
    lv_label_set_long_mode(ui->ui_telaMain_label_seq_l1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_telaMain_label_seq_l1, 15, 5);
    lv_obj_set_size(ui->ui_telaMain_label_seq_l1, 33, 28);

    //Write style for ui_telaMain_label_seq_l1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->ui_telaMain_label_seq_l1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_telaMain_label_seq_l1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_label_seq_l1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_label_seq_l1, &lv_font_montserratMedium_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_label_seq_l1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_telaMain_label_seq_l1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_telaMain_label_seq_l1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_label_seq_l1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_label_seq_l1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_telaMain_label_seq_l1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_label_seq_l1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_label_seq_l1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_label_seq_l1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_label_seq_l1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_label_seq_l2
    ui->ui_telaMain_label_seq_l2 = lv_label_create(ui->ui_telaMain_cont_sequencia);
    lv_label_set_text(ui->ui_telaMain_label_seq_l2, "L2");
    lv_label_set_long_mode(ui->ui_telaMain_label_seq_l2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_telaMain_label_seq_l2, 80, 6);
    lv_obj_set_size(ui->ui_telaMain_label_seq_l2, 33, 28);

    //Write style for ui_telaMain_label_seq_l2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->ui_telaMain_label_seq_l2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_telaMain_label_seq_l2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_label_seq_l2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_label_seq_l2, &lv_font_montserratMedium_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_label_seq_l2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_telaMain_label_seq_l2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_telaMain_label_seq_l2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_label_seq_l2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_label_seq_l2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_telaMain_label_seq_l2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_label_seq_l2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_label_seq_l2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_label_seq_l2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_label_seq_l2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_label_seq_l3
    ui->ui_telaMain_label_seq_l3 = lv_label_create(ui->ui_telaMain_cont_sequencia);
    lv_label_set_text(ui->ui_telaMain_label_seq_l3, "L3");
    lv_label_set_long_mode(ui->ui_telaMain_label_seq_l3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_telaMain_label_seq_l3, 140, 5);
    lv_obj_set_size(ui->ui_telaMain_label_seq_l3, 33, 28);

    //Write style for ui_telaMain_label_seq_l3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->ui_telaMain_label_seq_l3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_telaMain_label_seq_l3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_label_seq_l3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_label_seq_l3, &lv_font_montserratMedium_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_label_seq_l3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_telaMain_label_seq_l3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_telaMain_label_seq_l3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_label_seq_l3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_label_seq_l3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_telaMain_label_seq_l3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_label_seq_l3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_label_seq_l3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_label_seq_l3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_label_seq_l3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_btnSeqL1L2
    ui->ui_telaMain_btnSeqL1L2 = lv_btn_create(ui->ui_telaMain_cont_sequencia);
    ui->ui_telaMain_label_btnSeqL1L2 = lv_label_create(ui->ui_telaMain_btnSeqL1L2);
    lv_label_set_text(ui->ui_telaMain_label_btnSeqL1L2, "L1..L2");
    lv_label_set_long_mode(ui->ui_telaMain_label_btnSeqL1L2, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->ui_telaMain_label_btnSeqL1L2, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->ui_telaMain_btnSeqL1L2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->ui_telaMain_label_btnSeqL1L2, LV_PCT(100));
    lv_obj_set_pos(ui->ui_telaMain_btnSeqL1L2, 5, 30);
    lv_obj_set_size(ui->ui_telaMain_btnSeqL1L2, 55, 40);

    //Write style for ui_telaMain_btnSeqL1L2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->ui_telaMain_btnSeqL1L2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btnSeqL1L2, lv_color_hex(0x29BAE6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_btnSeqL1L2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_telaMain_btnSeqL1L2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_btnSeqL1L2, 17, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_btnSeqL1L2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_btnSeqL1L2, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_btnSeqL1L2, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_btnSeqL1L2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_btnSeqL1L2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui_telaMain_btnSeqL1L2, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->ui_telaMain_btnSeqL1L2, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btnSeqL1L2, lv_color_hex(0x18C220), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_btnSeqL1L2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->ui_telaMain_btnSeqL1L2, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->ui_telaMain_btnSeqL1L2, 17, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_btnSeqL1L2, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->ui_telaMain_btnSeqL1L2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->ui_telaMain_btnSeqL1L2, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->ui_telaMain_btnSeqL1L2, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write codes ui_telaMain_btnSeqL2L3
    ui->ui_telaMain_btnSeqL2L3 = lv_btn_create(ui->ui_telaMain_cont_sequencia);
    ui->ui_telaMain_label_btnSeqL2L3 = lv_label_create(ui->ui_telaMain_btnSeqL2L3);
    lv_label_set_text(ui->ui_telaMain_label_btnSeqL2L3, "L2..L3");
    lv_label_set_long_mode(ui->ui_telaMain_label_btnSeqL2L3, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->ui_telaMain_label_btnSeqL2L3, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->ui_telaMain_btnSeqL2L3, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->ui_telaMain_label_btnSeqL2L3, LV_PCT(100));
    lv_obj_set_pos(ui->ui_telaMain_btnSeqL2L3, 70, 30);
    lv_obj_set_size(ui->ui_telaMain_btnSeqL2L3, 55, 40);

    //Write style for ui_telaMain_btnSeqL2L3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->ui_telaMain_btnSeqL2L3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btnSeqL2L3, lv_color_hex(0x29BAE6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_btnSeqL2L3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_telaMain_btnSeqL2L3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_btnSeqL2L3, 17, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_btnSeqL2L3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_btnSeqL2L3, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_btnSeqL2L3, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_btnSeqL2L3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_btnSeqL2L3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui_telaMain_btnSeqL2L3, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->ui_telaMain_btnSeqL2L3, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btnSeqL2L3, lv_color_hex(0x18C220), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_btnSeqL2L3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->ui_telaMain_btnSeqL2L3, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->ui_telaMain_btnSeqL2L3, 17, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_btnSeqL2L3, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->ui_telaMain_btnSeqL2L3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->ui_telaMain_btnSeqL2L3, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->ui_telaMain_btnSeqL2L3, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write codes ui_telaMain_btnSeqL1L3
    ui->ui_telaMain_btnSeqL1L3 = lv_btn_create(ui->ui_telaMain_cont_sequencia);
    ui->ui_telaMain_label_btnSeqL1L3 = lv_label_create(ui->ui_telaMain_btnSeqL1L3);
    lv_label_set_text(ui->ui_telaMain_label_btnSeqL1L3, "L1..L3");
    lv_label_set_long_mode(ui->ui_telaMain_label_btnSeqL1L3, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->ui_telaMain_label_btnSeqL1L3, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->ui_telaMain_btnSeqL1L3, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->ui_telaMain_label_btnSeqL1L3, LV_PCT(100));
    lv_obj_set_pos(ui->ui_telaMain_btnSeqL1L3, 130, 30);
    lv_obj_set_size(ui->ui_telaMain_btnSeqL1L3, 55, 40);

    //Write style for ui_telaMain_btnSeqL1L3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->ui_telaMain_btnSeqL1L3, 17, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_btnSeqL1L3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btnSeqL1L3, lv_color_hex(0x29BAE6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_btnSeqL1L3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_telaMain_btnSeqL1L3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_btnSeqL1L3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_btnSeqL1L3, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_btnSeqL1L3, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_btnSeqL1L3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_btnSeqL1L3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui_telaMain_btnSeqL1L3, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->ui_telaMain_btnSeqL1L3, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btnSeqL1L3, lv_color_hex(0x18C220), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_btnSeqL1L3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->ui_telaMain_btnSeqL1L3, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->ui_telaMain_btnSeqL1L3, 17, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_btnSeqL1L3, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->ui_telaMain_btnSeqL1L3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->ui_telaMain_btnSeqL1L3, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->ui_telaMain_btnSeqL1L3, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write codes ui_telaMain_btnSeqL1L2L3
    ui->ui_telaMain_btnSeqL1L2L3 = lv_btn_create(ui->ui_telaMain_cont_sequencia);
    ui->ui_telaMain_label_btnSeqL1L2L3 = lv_label_create(ui->ui_telaMain_btnSeqL1L2L3);
    lv_label_set_text(ui->ui_telaMain_label_btnSeqL1L2L3, "L1.L2.L3");
    lv_label_set_long_mode(ui->ui_telaMain_label_btnSeqL1L2L3, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->ui_telaMain_label_btnSeqL1L2L3, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->ui_telaMain_btnSeqL1L2L3, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->ui_telaMain_label_btnSeqL1L2L3, LV_PCT(100));
    lv_obj_set_pos(ui->ui_telaMain_btnSeqL1L2L3, 30, 79);
    lv_obj_set_size(ui->ui_telaMain_btnSeqL1L2L3, 131, 40);

    //Write style for ui_telaMain_btnSeqL1L2L3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->ui_telaMain_btnSeqL1L2L3, 17, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_btnSeqL1L2L3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btnSeqL1L2L3, lv_color_hex(0x29BAE6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_btnSeqL1L2L3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_telaMain_btnSeqL1L2L3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_btnSeqL1L2L3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_btnSeqL1L2L3, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_btnSeqL1L2L3, &lv_font_montserratMedium_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_btnSeqL1L2L3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_btnSeqL1L2L3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui_telaMain_btnSeqL1L2L3, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->ui_telaMain_btnSeqL1L2L3, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btnSeqL1L2L3, lv_color_hex(0x18C220), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_btnSeqL1L2L3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->ui_telaMain_btnSeqL1L2L3, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->ui_telaMain_btnSeqL1L2L3, 17, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_btnSeqL1L2L3, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->ui_telaMain_btnSeqL1L2L3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->ui_telaMain_btnSeqL1L2L3, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->ui_telaMain_btnSeqL1L2L3, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write codes ui_telaMain_cont_teclado
    ui->ui_telaMain_cont_teclado = lv_obj_create(ui->ui_telaMain_containerMain);
    lv_obj_set_pos(ui->ui_telaMain_cont_teclado, 6, 70);
    lv_obj_set_size(ui->ui_telaMain_cont_teclado, 235, 260);
    lv_obj_set_scrollbar_mode(ui->ui_telaMain_cont_teclado, LV_SCROLLBAR_MODE_OFF);

    //Write style for ui_telaMain_cont_teclado, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_telaMain_cont_teclado, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->ui_telaMain_cont_teclado, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->ui_telaMain_cont_teclado, lv_color_hex(0x4A4C4A), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->ui_telaMain_cont_teclado, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_cont_teclado, 35, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_cont_teclado, 242, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_cont_teclado, lv_color_hex(0x5a5b5b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_cont_teclado, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_telaMain_cont_teclado, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_cont_teclado, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_cont_teclado, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_cont_teclado, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_cont_teclado, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_btn_n0
    ui->ui_telaMain_btn_n0 = lv_btn_create(ui->ui_telaMain_cont_teclado);
    ui->ui_telaMain_label_btn_n0 = lv_label_create(ui->ui_telaMain_btn_n0);
    lv_label_set_text(ui->ui_telaMain_label_btn_n0, "0");
    lv_label_set_long_mode(ui->ui_telaMain_label_btn_n0, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->ui_telaMain_label_btn_n0, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->ui_telaMain_btn_n0, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->ui_telaMain_label_btn_n0, LV_PCT(100));
    lv_obj_set_pos(ui->ui_telaMain_btn_n0, 90, 190);
    lv_obj_set_size(ui->ui_telaMain_btn_n0, 55, 55);

    //Write style for ui_telaMain_btn_n0, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_telaMain_btn_n0, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_btn_n0, 17, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_btn_n0, lv_color_hex(0x050505), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_btn_n0, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_btn_n0, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_btn_n0, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_btn_n0, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btn_n0, lv_color_hex(0X1E444f), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_btn_n0, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_btn_n0, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui_telaMain_btn_n0, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->ui_telaMain_btn_n0, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btn_n0, lv_color_hex(0x18C220), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_btn_n0, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->ui_telaMain_btn_n0, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->ui_telaMain_btn_n0, 17, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_btn_n0, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->ui_telaMain_btn_n0, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->ui_telaMain_btn_n0, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->ui_telaMain_btn_n0, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write codes ui_telaMain_btn_n1
    ui->ui_telaMain_btn_n1 = lv_btn_create(ui->ui_telaMain_cont_teclado);
    ui->ui_telaMain_label_btn_n1 = lv_label_create(ui->ui_telaMain_btn_n1);
    lv_label_set_text(ui->ui_telaMain_label_btn_n1, "1");
    lv_label_set_long_mode(ui->ui_telaMain_label_btn_n1, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->ui_telaMain_label_btn_n1, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->ui_telaMain_btn_n1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->ui_telaMain_label_btn_n1, LV_PCT(100));
    lv_obj_set_pos(ui->ui_telaMain_btn_n1, 15, 10);
    lv_obj_set_size(ui->ui_telaMain_btn_n1, 55, 55);

    //Write style for ui_telaMain_btn_n1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->ui_telaMain_btn_n1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btn_n1, lv_color_hex(0X1E444f), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_btn_n1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_telaMain_btn_n1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_btn_n1, 17, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_btn_n1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_btn_n1, lv_color_hex(0x050505), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_btn_n1, &lv_font_montserratMedium_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_btn_n1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_btn_n1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui_telaMain_btn_n1, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->ui_telaMain_btn_n1, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btn_n1, lv_color_hex(0x18C220), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_btn_n1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->ui_telaMain_btn_n1, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->ui_telaMain_btn_n1, 17, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_btn_n1, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->ui_telaMain_btn_n1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->ui_telaMain_btn_n1, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->ui_telaMain_btn_n1, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write codes ui_telaMain_btn_n2
    ui->ui_telaMain_btn_n2 = lv_btn_create(ui->ui_telaMain_cont_teclado);
    ui->ui_telaMain_label_btn_n2 = lv_label_create(ui->ui_telaMain_btn_n2);
    lv_label_set_text(ui->ui_telaMain_label_btn_n2, "2");
    lv_label_set_long_mode(ui->ui_telaMain_label_btn_n2, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->ui_telaMain_label_btn_n2, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->ui_telaMain_btn_n2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->ui_telaMain_label_btn_n2, LV_PCT(100));
    lv_obj_set_pos(ui->ui_telaMain_btn_n2, 90, 10);
    lv_obj_set_size(ui->ui_telaMain_btn_n2, 55, 55);

    //Write style for ui_telaMain_btn_n2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->ui_telaMain_btn_n2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btn_n2, lv_color_hex(0X1E444f), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_btn_n2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_telaMain_btn_n2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_btn_n2, 17, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_btn_n2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_btn_n2, lv_color_hex(0x050505), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_btn_n2, &lv_font_montserratMedium_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_btn_n2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_btn_n2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui_telaMain_btn_n2, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->ui_telaMain_btn_n2, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btn_n2, lv_color_hex(0x18C220), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_btn_n2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->ui_telaMain_btn_n2, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->ui_telaMain_btn_n2, 17, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_btn_n2, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->ui_telaMain_btn_n2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->ui_telaMain_btn_n2, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->ui_telaMain_btn_n2, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write codes ui_telaMain_btn_n3
    ui->ui_telaMain_btn_n3 = lv_btn_create(ui->ui_telaMain_cont_teclado);
    ui->ui_telaMain_label_btn_n3 = lv_label_create(ui->ui_telaMain_btn_n3);
    lv_label_set_text(ui->ui_telaMain_label_btn_n3, "3");
    lv_label_set_long_mode(ui->ui_telaMain_label_btn_n3, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->ui_telaMain_label_btn_n3, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->ui_telaMain_btn_n3, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->ui_telaMain_label_btn_n3, LV_PCT(100));
    lv_obj_set_pos(ui->ui_telaMain_btn_n3, 165, 10);
    lv_obj_set_size(ui->ui_telaMain_btn_n3, 55, 55);

    //Write style for ui_telaMain_btn_n3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->ui_telaMain_btn_n3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btn_n3, lv_color_hex(0X1E444f), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_btn_n3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_telaMain_btn_n3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_btn_n3, 17, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_btn_n3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_btn_n3, lv_color_hex(0x050505), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_btn_n3, &lv_font_montserratMedium_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_btn_n3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_btn_n3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui_telaMain_btn_n3, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->ui_telaMain_btn_n3, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btn_n3, lv_color_hex(0x18C220), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_btn_n3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->ui_telaMain_btn_n3, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->ui_telaMain_btn_n3, 17, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_btn_n3, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->ui_telaMain_btn_n3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->ui_telaMain_btn_n3, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->ui_telaMain_btn_n3, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write codes ui_telaMain_btn_n4
    ui->ui_telaMain_btn_n4 = lv_btn_create(ui->ui_telaMain_cont_teclado);
    ui->ui_telaMain_label_btn_n4 = lv_label_create(ui->ui_telaMain_btn_n4);
    lv_label_set_text(ui->ui_telaMain_label_btn_n4, "4");
    lv_label_set_long_mode(ui->ui_telaMain_label_btn_n4, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->ui_telaMain_label_btn_n4, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->ui_telaMain_btn_n4, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->ui_telaMain_label_btn_n4, LV_PCT(100));
    lv_obj_set_pos(ui->ui_telaMain_btn_n4, 15, 70);
    lv_obj_set_size(ui->ui_telaMain_btn_n4, 55, 55);

    //Write style for ui_telaMain_btn_n4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->ui_telaMain_btn_n4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btn_n4, lv_color_hex(0X1E444f), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_btn_n4, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_telaMain_btn_n4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_btn_n4, 17, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_btn_n4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_btn_n4, lv_color_hex(0x050505), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_btn_n4, &lv_font_montserratMedium_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_btn_n4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_btn_n4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui_telaMain_btn_n4, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->ui_telaMain_btn_n4, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btn_n4, lv_color_hex(0x18C220), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_btn_n4, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->ui_telaMain_btn_n4, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->ui_telaMain_btn_n4, 17, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_btn_n4, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->ui_telaMain_btn_n4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->ui_telaMain_btn_n4, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->ui_telaMain_btn_n4, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write codes ui_telaMain_btn_n5
    ui->ui_telaMain_btn_n5 = lv_btn_create(ui->ui_telaMain_cont_teclado);
    ui->ui_telaMain_label_btn_n5 = lv_label_create(ui->ui_telaMain_btn_n5);
    lv_label_set_text(ui->ui_telaMain_label_btn_n5, "5");
    lv_label_set_long_mode(ui->ui_telaMain_label_btn_n5, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->ui_telaMain_label_btn_n5, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->ui_telaMain_btn_n5, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->ui_telaMain_label_btn_n5, LV_PCT(100));
    lv_obj_set_pos(ui->ui_telaMain_btn_n5, 90, 70);
    lv_obj_set_size(ui->ui_telaMain_btn_n5, 55, 55);

    //Write style for ui_telaMain_btn_n5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->ui_telaMain_btn_n5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btn_n5, lv_color_hex(0X1E444f), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_btn_n5, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_telaMain_btn_n5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_btn_n5, 17, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_btn_n5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_btn_n5, lv_color_hex(0x050505), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_btn_n5, &lv_font_montserratMedium_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_btn_n5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_btn_n5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui_telaMain_btn_n5, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->ui_telaMain_btn_n5, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btn_n5, lv_color_hex(0x18C220), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_btn_n5, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->ui_telaMain_btn_n5, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->ui_telaMain_btn_n5, 17, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_btn_n5, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->ui_telaMain_btn_n5, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->ui_telaMain_btn_n5, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->ui_telaMain_btn_n5, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write codes ui_telaMain_btn_n6
    ui->ui_telaMain_btn_n6 = lv_btn_create(ui->ui_telaMain_cont_teclado);
    ui->ui_telaMain_label_btn_n6 = lv_label_create(ui->ui_telaMain_btn_n6);
    lv_label_set_text(ui->ui_telaMain_label_btn_n6, "6");
    lv_label_set_long_mode(ui->ui_telaMain_label_btn_n6, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->ui_telaMain_label_btn_n6, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->ui_telaMain_btn_n6, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->ui_telaMain_label_btn_n6, LV_PCT(100));
    lv_obj_set_pos(ui->ui_telaMain_btn_n6, 165, 70);
    lv_obj_set_size(ui->ui_telaMain_btn_n6, 55, 55);

    //Write style for ui_telaMain_btn_n6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->ui_telaMain_btn_n6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btn_n6, lv_color_hex(0X1E444f), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_btn_n6, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_telaMain_btn_n6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_btn_n6, 17, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_btn_n6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_btn_n6, lv_color_hex(0x050505), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_btn_n6, &lv_font_montserratMedium_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_btn_n6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_btn_n6, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui_telaMain_btn_n6, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->ui_telaMain_btn_n6, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btn_n6, lv_color_hex(0x18C220), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_btn_n6, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->ui_telaMain_btn_n6, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->ui_telaMain_btn_n6, 17, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_btn_n6, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->ui_telaMain_btn_n6, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->ui_telaMain_btn_n6, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->ui_telaMain_btn_n6, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write codes ui_telaMain_btn_n7
    ui->ui_telaMain_btn_n7 = lv_btn_create(ui->ui_telaMain_cont_teclado);
    ui->ui_telaMain_label_btn_n7 = lv_label_create(ui->ui_telaMain_btn_n7);
    lv_label_set_text(ui->ui_telaMain_label_btn_n7, "7");
    lv_label_set_long_mode(ui->ui_telaMain_label_btn_n7, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->ui_telaMain_label_btn_n7, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->ui_telaMain_btn_n7, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->ui_telaMain_label_btn_n7, LV_PCT(100));
    lv_obj_set_pos(ui->ui_telaMain_btn_n7, 15, 130);
    lv_obj_set_size(ui->ui_telaMain_btn_n7, 55, 55);

    //Write style for ui_telaMain_btn_n7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_telaMain_btn_n7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_btn_n7, 17, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_btn_n7, lv_color_hex(0x050505), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_btn_n7, &lv_font_montserratMedium_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_btn_n7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_btn_n7, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_btn_n7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btn_n7, lv_color_hex(0X1E444f), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_btn_n7, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_btn_n7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui_telaMain_btn_n7, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->ui_telaMain_btn_n7, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btn_n7, lv_color_hex(0x18C220), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_btn_n7, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->ui_telaMain_btn_n7, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->ui_telaMain_btn_n7, 17, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_btn_n7, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->ui_telaMain_btn_n7, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->ui_telaMain_btn_n7, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->ui_telaMain_btn_n7, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write codes ui_telaMain_btn_n8
    ui->ui_telaMain_btn_n8 = lv_btn_create(ui->ui_telaMain_cont_teclado);
    ui->ui_telaMain_label_btn_n8 = lv_label_create(ui->ui_telaMain_btn_n8);
    lv_label_set_text(ui->ui_telaMain_label_btn_n8, "8");
    lv_label_set_long_mode(ui->ui_telaMain_label_btn_n8, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->ui_telaMain_label_btn_n8, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->ui_telaMain_btn_n8, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->ui_telaMain_label_btn_n8, LV_PCT(100));
    lv_obj_set_pos(ui->ui_telaMain_btn_n8, 90, 130);
    lv_obj_set_size(ui->ui_telaMain_btn_n8, 55, 55);

    //Write style for ui_telaMain_btn_n8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_telaMain_btn_n8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_btn_n8, 17, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_btn_n8, lv_color_hex(0x050505), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_btn_n8, &lv_font_montserratMedium_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_btn_n8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_btn_n8, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_btn_n8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btn_n8, lv_color_hex(0X1E444f), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_btn_n8, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_btn_n8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui_telaMain_btn_n8, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->ui_telaMain_btn_n8, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btn_n8, lv_color_hex(0x18C220), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_btn_n8, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->ui_telaMain_btn_n8, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->ui_telaMain_btn_n8, 17, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_btn_n8, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->ui_telaMain_btn_n8, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->ui_telaMain_btn_n8, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->ui_telaMain_btn_n8, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write codes ui_telaMain_btn_n9
    ui->ui_telaMain_btn_n9 = lv_btn_create(ui->ui_telaMain_cont_teclado);
    ui->ui_telaMain_label_btn_n9 = lv_label_create(ui->ui_telaMain_btn_n9);
    lv_label_set_text(ui->ui_telaMain_label_btn_n9, "9");
    lv_label_set_long_mode(ui->ui_telaMain_label_btn_n9, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->ui_telaMain_label_btn_n9, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->ui_telaMain_btn_n9, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->ui_telaMain_label_btn_n9, LV_PCT(100));
    lv_obj_set_pos(ui->ui_telaMain_btn_n9, 165, 130);
    lv_obj_set_size(ui->ui_telaMain_btn_n9, 55, 55);

    //Write style for ui_telaMain_btn_n9, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_telaMain_btn_n9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_btn_n9, 17, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_btn_n9, lv_color_hex(0x050505), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_btn_n9, &lv_font_montserratMedium_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_btn_n9, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_btn_n9, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_btn_n9, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btn_n9, lv_color_hex(0X1E444f), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_btn_n9, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_btn_n9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui_telaMain_btn_n9, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->ui_telaMain_btn_n9, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btn_n9, lv_color_hex(0x18C220), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_btn_n9, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->ui_telaMain_btn_n9, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->ui_telaMain_btn_n9, 17, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_btn_n9, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->ui_telaMain_btn_n9, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->ui_telaMain_btn_n9, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->ui_telaMain_btn_n9, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write codes ui_telaMain_btn_ok
    ui->ui_telaMain_btn_ok = lv_btn_create(ui->ui_telaMain_cont_teclado);
    ui->ui_telaMain_label_btn_ok = lv_label_create(ui->ui_telaMain_btn_ok);
    lv_label_set_text(ui->ui_telaMain_label_btn_ok, "ok");
    lv_label_set_long_mode(ui->ui_telaMain_label_btn_ok, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->ui_telaMain_label_btn_ok, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->ui_telaMain_btn_ok, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->ui_telaMain_label_btn_ok, LV_PCT(100));
    lv_obj_set_pos(ui->ui_telaMain_btn_ok, 165, 190);
    lv_obj_set_size(ui->ui_telaMain_btn_ok, 55, 55);

    //Write style for ui_telaMain_btn_ok, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->ui_telaMain_btn_ok, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btn_ok, lv_color_hex(0xecf713), LV_PART_MAIN|LV_STATE_DEFAULT); //Altera a cor do botao de ok
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_btn_ok, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_btn_ok, 17, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_btn_ok, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_telaMain_btn_ok, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_btn_ok, lv_color_hex(0x050505), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_btn_ok, &lv_font_montserratMedium_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_btn_ok, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_btn_ok, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui_telaMain_btn_ok, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_shadow_width(ui->ui_telaMain_btn_ok, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_btn_ok, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btn_ok, lv_color_hex(0x18C220), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_btn_ok, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->ui_telaMain_btn_ok, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->ui_telaMain_btn_ok, 17, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->ui_telaMain_btn_ok, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->ui_telaMain_btn_ok, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->ui_telaMain_btn_ok, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write codes ui_telaMain_btn_cancel
    ui->ui_telaMain_btn_cancel = lv_btn_create(ui->ui_telaMain_cont_teclado);
    ui->ui_telaMain_label_btn_cancel = lv_label_create(ui->ui_telaMain_btn_cancel);
    lv_label_set_text(ui->ui_telaMain_label_btn_cancel, "canc");
    lv_label_set_long_mode(ui->ui_telaMain_label_btn_cancel, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->ui_telaMain_label_btn_cancel, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->ui_telaMain_btn_cancel, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->ui_telaMain_label_btn_cancel, LV_PCT(100));
    lv_obj_set_pos(ui->ui_telaMain_btn_cancel, 15, 190);
    lv_obj_set_size(ui->ui_telaMain_btn_cancel, 55, 55);

    //Write style for ui_telaMain_btn_cancel, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_telaMain_btn_cancel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_btn_cancel, 17, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_btn_cancel, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btn_cancel, lv_color_hex(0X1E444f), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_btn_cancel, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_btn_cancel, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_btn_cancel, lv_color_hex(0x050505), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_btn_cancel, &lv_font_montserratMedium_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_btn_cancel, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_btn_cancel, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui_telaMain_btn_cancel, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->ui_telaMain_btn_cancel, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btn_cancel, lv_color_hex(0x18C220), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_btn_cancel, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->ui_telaMain_btn_cancel, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->ui_telaMain_btn_cancel, 17, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_btn_cancel, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->ui_telaMain_btn_cancel, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->ui_telaMain_btn_cancel, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->ui_telaMain_btn_cancel, 255, LV_PART_MAIN|LV_STATE_PRESSED);
//==================================================================================================================
    //Write codes ui_telaMain_cont_escala
    ui->ui_telaMain_cont_escala = lv_obj_create(ui->ui_telaMain_dashboard);
    lv_obj_set_pos(ui->ui_telaMain_cont_escala, 629, 69);
    lv_obj_set_size(ui->ui_telaMain_cont_escala, 170, 412);
    lv_obj_set_scrollbar_mode(ui->ui_telaMain_cont_escala, LV_SCROLLBAR_MODE_OFF);

    //Write style for ui_telaMain_cont_escala, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_telaMain_cont_escala, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->ui_telaMain_cont_escala, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->ui_telaMain_cont_escala, lv_color_hex(0x4A4C4A), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->ui_telaMain_cont_escala, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_cont_escala, 35, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_cont_escala, 250, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_cont_escala, lv_color_hex(0x242424), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_cont_escala, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_telaMain_cont_escala, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_cont_escala, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_cont_escala, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_cont_escala, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_cont_escala, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_cont_escala_tensoes
    ui->ui_telaMain_cont_escala_tensoes = lv_obj_create(ui->ui_telaMain_cont_escala);
    lv_obj_set_pos(ui->ui_telaMain_cont_escala_tensoes, 16, 6);
    lv_obj_set_size(ui->ui_telaMain_cont_escala_tensoes, 136, 253);
    lv_obj_set_scrollbar_mode(ui->ui_telaMain_cont_escala_tensoes, LV_SCROLLBAR_MODE_OFF);

    //Write style for ui_telaMain_cont_escala_tensoes, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_telaMain_cont_escala_tensoes, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->ui_telaMain_cont_escala_tensoes, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->ui_telaMain_cont_escala_tensoes, lv_color_hex(0x4A4C4A), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->ui_telaMain_cont_escala_tensoes, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_cont_escala_tensoes, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_cont_escala_tensoes, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_cont_escala_tensoes, lv_color_hex(0x5a5b5b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_cont_escala_tensoes, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_telaMain_cont_escala_tensoes, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_cont_escala_tensoes, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_cont_escala_tensoes, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_cont_escala_tensoes, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_cont_escala_tensoes, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_selEscala0
    ui->ui_telaMain_selEscala0 = lv_checkbox_create(ui->ui_telaMain_cont_escala_tensoes);
    lv_checkbox_set_text(ui->ui_telaMain_selEscala0, "12Vac");
    lv_obj_set_pos(ui->ui_telaMain_selEscala0, 5, 6);

    //Write style for ui_telaMain_selEscala0, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_pad_top(ui->ui_telaMain_selEscala0, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_selEscala0, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_selEscala0, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_selEscala0, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_selEscala0, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_selEscala0, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_selEscala0, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_telaMain_selEscala0, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_telaMain_selEscala0, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_selEscala0, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_selEscala0, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_selEscala0, lv_color_hex(0x5a5b5b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_selEscala0, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_selEscala0, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui_telaMain_selEscala0, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_pad_all(ui->ui_telaMain_selEscala0, 3, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_telaMain_selEscala0, 2, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->ui_telaMain_selEscala0, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->ui_telaMain_selEscala0, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->ui_telaMain_selEscala0, LV_BORDER_SIDE_FULL, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_selEscala0, 6, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_selEscala0, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_selEscala0, lv_color_hex(0xffffff), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_selEscala0, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_selEscala1
    ui->ui_telaMain_selEscala1 = lv_checkbox_create(ui->ui_telaMain_cont_escala_tensoes);
    lv_checkbox_set_text(ui->ui_telaMain_selEscala1, "24Vac");
    lv_obj_set_pos(ui->ui_telaMain_selEscala1, 5, 37);

    //Write style for ui_telaMain_selEscala1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_pad_top(ui->ui_telaMain_selEscala1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_selEscala1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_selEscala1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_selEscala1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_selEscala1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_selEscala1, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_selEscala1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_telaMain_selEscala1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_telaMain_selEscala1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_selEscala1, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_selEscala1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_selEscala1, lv_color_hex(0x5a5b5b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_selEscala1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_selEscala1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui_telaMain_selEscala1, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_pad_all(ui->ui_telaMain_selEscala1, 3, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_telaMain_selEscala1, 2, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->ui_telaMain_selEscala1, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->ui_telaMain_selEscala1, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->ui_telaMain_selEscala1, LV_BORDER_SIDE_FULL, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_selEscala1, 6, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_selEscala1, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_selEscala1, lv_color_hex(0xffffff), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_selEscala1, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_selEscala2
    ui->ui_telaMain_selEscala2 = lv_checkbox_create(ui->ui_telaMain_cont_escala_tensoes);
    lv_checkbox_set_text(ui->ui_telaMain_selEscala2, "110Vac");
    lv_obj_set_pos(ui->ui_telaMain_selEscala2, 5, 68);
    lv_obj_add_state(ui->ui_telaMain_selEscala2, LV_STATE_CHECKED | LV_STATE_DISABLED);  //Marca a e desabilita a checkbox 

    //Write style for ui_telaMain_selEscala2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_pad_top(ui->ui_telaMain_selEscala2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_selEscala2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_selEscala2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_selEscala2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_selEscala2, lv_color_hex(0xfdfdfd), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_selEscala2, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_selEscala2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_telaMain_selEscala2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_telaMain_selEscala2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_selEscala2, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_selEscala2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_selEscala2, lv_color_hex(0x5a5b5b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_selEscala2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_selEscala2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui_telaMain_selEscala2, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_pad_all(ui->ui_telaMain_selEscala2, 3, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_telaMain_selEscala2, 2, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->ui_telaMain_selEscala2, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->ui_telaMain_selEscala2, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->ui_telaMain_selEscala2, LV_BORDER_SIDE_FULL, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_selEscala2, 6, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_selEscala2, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_selEscala2, lv_color_hex(0xffffff), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_selEscala2, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_selEscala3
    ui->ui_telaMain_selEscala3 = lv_checkbox_create(ui->ui_telaMain_cont_escala_tensoes);
    lv_checkbox_set_text(ui->ui_telaMain_selEscala3, "220Vac");
    lv_obj_set_pos(ui->ui_telaMain_selEscala3, 5, 99);

    //Write style for ui_telaMain_selEscala3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_pad_top(ui->ui_telaMain_selEscala3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_selEscala3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_selEscala3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_selEscala3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_selEscala3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_selEscala3, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_selEscala3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_telaMain_selEscala3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_telaMain_selEscala3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_selEscala3, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_selEscala3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_selEscala3, lv_color_hex(0x5a5b5b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_selEscala3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_selEscala3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui_telaMain_selEscala3, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_pad_all(ui->ui_telaMain_selEscala3, 3, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_telaMain_selEscala3, 2, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->ui_telaMain_selEscala3, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->ui_telaMain_selEscala3, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->ui_telaMain_selEscala3, LV_BORDER_SIDE_FULL, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_selEscala3, 6, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_selEscala3, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_selEscala3, lv_color_hex(0xffffff), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_selEscala3, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_selEscala4
    ui->ui_telaMain_selEscala4 = lv_checkbox_create(ui->ui_telaMain_cont_escala_tensoes);
    lv_checkbox_set_text(ui->ui_telaMain_selEscala4, "380Vac");
    lv_obj_set_pos(ui->ui_telaMain_selEscala4, 5, 130);

    //Write style for ui_telaMain_selEscala4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_pad_top(ui->ui_telaMain_selEscala4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_selEscala4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_selEscala4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_selEscala4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_selEscala4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_selEscala4, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_selEscala4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_telaMain_selEscala4, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_telaMain_selEscala4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_selEscala4, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_selEscala4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_selEscala4, lv_color_hex(0x5a5b5b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_selEscala4, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_selEscala4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui_telaMain_selEscala4, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_pad_all(ui->ui_telaMain_selEscala4, 3, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_telaMain_selEscala4, 2, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->ui_telaMain_selEscala4, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->ui_telaMain_selEscala4, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->ui_telaMain_selEscala4, LV_BORDER_SIDE_FULL, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_selEscala4, 6, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_selEscala4, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_selEscala4, lv_color_hex(0xffffff), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_selEscala4, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_selEscala5
    ui->ui_telaMain_selEscala5 = lv_checkbox_create(ui->ui_telaMain_cont_escala_tensoes);
    lv_checkbox_set_text(ui->ui_telaMain_selEscala5, "440Vac");
    lv_obj_set_pos(ui->ui_telaMain_selEscala5, 5, 161);

    //Write style for ui_telaMain_selEscala5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_pad_top(ui->ui_telaMain_selEscala5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_selEscala5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_selEscala5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_selEscala5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_selEscala5, lv_color_hex(0xf9f9f9), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_selEscala5, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_selEscala5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_telaMain_selEscala5, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_telaMain_selEscala5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_selEscala5, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_selEscala5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_selEscala5, lv_color_hex(0x5a5b5b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_selEscala5, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_selEscala5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui_telaMain_selEscala5, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_pad_all(ui->ui_telaMain_selEscala5, 3, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_telaMain_selEscala5, 2, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->ui_telaMain_selEscala5, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->ui_telaMain_selEscala5, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->ui_telaMain_selEscala5, LV_BORDER_SIDE_FULL, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_selEscala5, 6, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_selEscala5, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_selEscala5, lv_color_hex(0xffffff), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_selEscala5, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_selEscala6
    ui->ui_telaMain_selEscala6 = lv_checkbox_create(ui->ui_telaMain_cont_escala_tensoes);
    lv_checkbox_set_text(ui->ui_telaMain_selEscala6, "480Vac");
    lv_obj_set_pos(ui->ui_telaMain_selEscala6, 5, 192);

    //Write style for ui_telaMain_selEscala6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_pad_top(ui->ui_telaMain_selEscala6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_selEscala6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_selEscala6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_selEscala6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_selEscala6, lv_color_hex(0xf5f5f5), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_selEscala6, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_selEscala6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_telaMain_selEscala6, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_telaMain_selEscala6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_selEscala6, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_selEscala6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_selEscala6, lv_color_hex(0x5a5b5b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_selEscala6, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_selEscala6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui_telaMain_selEscala6, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_pad_all(ui->ui_telaMain_selEscala6, 3, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_telaMain_selEscala6, 2, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->ui_telaMain_selEscala6, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->ui_telaMain_selEscala6, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->ui_telaMain_selEscala6, LV_BORDER_SIDE_FULL, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_selEscala6, 6, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_selEscala6, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_selEscala6, lv_color_hex(0xffffff), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_selEscala6, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_selEscala7
    ui->ui_telaMain_selEscala7 = lv_checkbox_create(ui->ui_telaMain_cont_escala_tensoes);
    lv_checkbox_set_text(ui->ui_telaMain_selEscala7, "64Vdc");
    lv_obj_set_pos(ui->ui_telaMain_selEscala7, 5, 223);

    //Write style for ui_telaMain_selEscala7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_pad_top(ui->ui_telaMain_selEscala7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_selEscala7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_selEscala7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_selEscala7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_selEscala7, lv_color_hex(0xfefefe), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_selEscala7, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_selEscala7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_telaMain_selEscala7, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_telaMain_selEscala7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_selEscala7, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_selEscala7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_selEscala7, lv_color_hex(0x5a5b5b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_selEscala7, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_selEscala7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui_telaMain_selEscala7, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_pad_all(ui->ui_telaMain_selEscala7, 3, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_telaMain_selEscala7, 2, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->ui_telaMain_selEscala7, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->ui_telaMain_selEscala7, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->ui_telaMain_selEscala7, LV_BORDER_SIDE_FULL, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_selEscala7, 6, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_selEscala7, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_selEscala7, lv_color_hex(0xffffff), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_selEscala7, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
//=============================================================================================================
    //Write codes ui_telaMain_cont_frequencia
    ui->ui_telaMain_cont_frequencia = lv_obj_create(ui->ui_telaMain_cont_escala);
    lv_obj_set_pos(ui->ui_telaMain_cont_frequencia, 5, 262);
    lv_obj_set_size(ui->ui_telaMain_cont_frequencia, 157, 145);
    lv_obj_set_scrollbar_mode(ui->ui_telaMain_cont_frequencia, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(ui->ui_telaMain_cont_frequencia, LV_OBJ_FLAG_SCROLLABLE); // Disable scrolling

    //Write style for ui_telaMain_cont_frequencia, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_telaMain_cont_frequencia, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->ui_telaMain_cont_frequencia, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->ui_telaMain_cont_frequencia, lv_color_hex(0x4A4C4A), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->ui_telaMain_cont_frequencia, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_cont_frequencia, 35, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_cont_frequencia, 242, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_cont_frequencia, lv_color_hex(0x5a5b5b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_cont_frequencia, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_telaMain_cont_frequencia, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_cont_frequencia, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_cont_frequencia, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_cont_frequencia, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_cont_frequencia, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_label_frequencia
    ui->ui_telaMain_label_frequencia = lv_label_create(ui->ui_telaMain_cont_frequencia);
    lv_label_set_text(ui->ui_telaMain_label_frequencia, "Frequencia");
    lv_label_set_long_mode(ui->ui_telaMain_label_frequencia, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_telaMain_label_frequencia, -4, 126);
    lv_obj_set_size(ui->ui_telaMain_label_frequencia, 158, 28);

    //Write style for ui_telaMain_label_frequencia, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->ui_telaMain_label_frequencia, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_telaMain_label_frequencia, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_label_frequencia, lv_color_hex(0xa6ff00), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_label_frequencia, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_label_frequencia, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_telaMain_label_frequencia, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_telaMain_label_frequencia, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_label_frequencia, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_label_frequencia, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_telaMain_label_frequencia, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_label_frequencia, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_label_frequencia, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_label_frequencia, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_label_frequencia, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_label_pointEsq
    ui->ui_telaMain_label_pointEsq = lv_label_create(ui->ui_telaMain_cont_frequencia);
    lv_label_set_text(ui->ui_telaMain_label_pointEsq, "•\n>");
    lv_label_set_long_mode(ui->ui_telaMain_label_pointEsq, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_telaMain_label_pointEsq, 103, 28);
    lv_obj_set_size(ui->ui_telaMain_label_pointEsq, 50, 54);

    //Write style for ui_telaMain_label_pointEsq, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->ui_telaMain_label_pointEsq, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_label_pointEsq, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_telaMain_label_pointEsq, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_label_pointEsq, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_label_pointEsq, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_label_pointEsq, &lv_font_Antonio_Regular_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_label_pointEsq, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_telaMain_label_pointEsq, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_telaMain_label_pointEsq, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_label_pointEsq, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_telaMain_label_pointEsq, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_label_pointEsq, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_label_pointEsq, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_label_pointEsq, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_label_freqAtual
    ui->ui_telaMain_label_freqAtual = lv_label_create(ui->ui_telaMain_cont_frequencia);
    lv_label_set_text(ui->ui_telaMain_label_freqAtual, "•\n60.0Hz");
    lv_label_set_long_mode(ui->ui_telaMain_label_freqAtual, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_telaMain_label_freqAtual, 43, 27);
    lv_obj_set_size(ui->ui_telaMain_label_freqAtual, 57, 61);

    //Write style for ui_telaMain_label_freqAtual, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->ui_telaMain_label_freqAtual, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_telaMain_label_freqAtual, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_label_freqAtual, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_label_freqAtual, &lv_font_Antonio_Regular_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_label_freqAtual, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_telaMain_label_freqAtual, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_telaMain_label_freqAtual, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_label_freqAtual, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_label_freqAtual, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_telaMain_label_freqAtual, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_label_freqAtual, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_label_freqAtual, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_label_freqAtual, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_label_freqAtual, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_label_pointDir
    ui->ui_telaMain_label_pointDir = lv_label_create(ui->ui_telaMain_cont_frequencia);
    lv_label_set_text(ui->ui_telaMain_label_pointDir, "•\n<");
    lv_label_set_long_mode(ui->ui_telaMain_label_pointDir, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_telaMain_label_pointDir, -8, 28);
    lv_obj_set_size(ui->ui_telaMain_label_pointDir, 50, 54);

    //Write style for ui_telaMain_label_pointDir, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->ui_telaMain_label_pointDir, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_telaMain_label_pointDir, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_label_pointDir, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_label_pointDir, &lv_font_Antonio_Regular_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_label_pointDir, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_telaMain_label_pointDir, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_telaMain_label_pointDir, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_label_pointDir, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_label_pointDir, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_telaMain_label_pointDir, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_label_pointDir, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_label_pointDir, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_label_pointDir, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_label_pointDir, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_sliderFreq
    ui->ui_telaMain_sliderFreq = lv_slider_create(ui->ui_telaMain_cont_frequencia);
    lv_slider_set_range(ui->ui_telaMain_sliderFreq, 500, 700);
    lv_slider_set_mode(ui->ui_telaMain_sliderFreq, LV_SLIDER_MODE_NORMAL);
    lv_slider_set_value(ui->ui_telaMain_sliderFreq, 600, LV_ANIM_OFF);
    lv_obj_set_pos(ui->ui_telaMain_sliderFreq, 18, 26);
    lv_obj_set_size(ui->ui_telaMain_sliderFreq, 105, 3);

    //Write style for ui_telaMain_sliderFreq, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->ui_telaMain_sliderFreq, 88, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_sliderFreq, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_sliderFreq, lv_color_hex(0x6A6A6A), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_sliderFreq, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_sliderFreq, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->ui_telaMain_sliderFreq, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui_telaMain_sliderFreq, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->ui_telaMain_sliderFreq, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_sliderFreq, lv_color_hex(0x29BAE6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_sliderFreq, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_sliderFreq, 88, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write style for ui_telaMain_sliderFreq, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->ui_telaMain_sliderFreq, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_sliderFreq, lv_color_hex(0xffffff), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_sliderFreq, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_sliderFreq, 88, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_btnFreq50
    ui->ui_telaMain_btnFreq50 = lv_btn_create(ui->ui_telaMain_cont_frequencia);
    ui->ui_telaMain_label_btnFreq50 = lv_label_create(ui->ui_telaMain_btnFreq50);
    lv_label_set_text(ui->ui_telaMain_label_btnFreq50, "50Hz");
    lv_label_set_long_mode(ui->ui_telaMain_label_btnFreq50, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->ui_telaMain_label_btnFreq50, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->ui_telaMain_btnFreq50, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->ui_telaMain_label_btnFreq50, LV_PCT(100));
    lv_obj_set_pos(ui->ui_telaMain_btnFreq50, 3, 81);
    lv_obj_set_size(ui->ui_telaMain_btnFreq50, 70, 40);

    //Write style for ui_telaMain_btnFreq50, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->ui_telaMain_btnFreq50, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btnFreq50, lv_color_hex(0x29BAE6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_btnFreq50, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_telaMain_btnFreq50, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_btnFreq50, 17, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_btnFreq50, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_btnFreq50, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_btnFreq50, &lv_font_montserratMedium_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_btnFreq50, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_btnFreq50, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui_telaMain_btnFreq50, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->ui_telaMain_btnFreq50, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btnFreq50, lv_color_hex(0x18C220), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_btnFreq50, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->ui_telaMain_btnFreq50, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->ui_telaMain_btnFreq50, 17, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_btnFreq50, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->ui_telaMain_btnFreq50, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->ui_telaMain_btnFreq50, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->ui_telaMain_btnFreq50, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write codes ui_telaMain_btnFreq60
    ui->ui_telaMain_btnFreq60 = lv_btn_create(ui->ui_telaMain_cont_frequencia);
    ui->ui_telaMain_label_btnFreq60 = lv_label_create(ui->ui_telaMain_btnFreq60);
    lv_label_set_text(ui->ui_telaMain_label_btnFreq60, "60Hz");
    lv_label_set_long_mode(ui->ui_telaMain_label_btnFreq60, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->ui_telaMain_label_btnFreq60, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->ui_telaMain_btnFreq60, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->ui_telaMain_label_btnFreq60, LV_PCT(100));
    lv_obj_set_pos(ui->ui_telaMain_btnFreq60, 80, 81);
    lv_obj_set_size(ui->ui_telaMain_btnFreq60, 70, 40);

    //Write style for ui_telaMain_btnFreq60, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->ui_telaMain_btnFreq60, 17, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_telaMain_btnFreq60, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_btnFreq60, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_btnFreq60, &lv_font_montserratMedium_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_btnFreq60, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_btnFreq60, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_btnFreq60, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btnFreq60, lv_color_hex(0x29BAE6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_btnFreq60, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_btnFreq60, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui_telaMain_btnFreq60, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->ui_telaMain_btnFreq60, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btnFreq60, lv_color_hex(0x18C220), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_btnFreq60, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->ui_telaMain_btnFreq60, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->ui_telaMain_btnFreq60, 17, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_btnFreq60, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->ui_telaMain_btnFreq60, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->ui_telaMain_btnFreq60, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->ui_telaMain_btnFreq60, 255, LV_PART_MAIN|LV_STATE_PRESSED);

//===================================================================================================================
    //Write codes ui_telaMain_cont_L1
    ui->ui_telaMain_cont_L1 = lv_obj_create(ui->ui_telaMain_dashboard);
    lv_obj_set_pos(ui->ui_telaMain_cont_L1, 1, 1);
    lv_obj_set_size(ui->ui_telaMain_cont_L1, 205, 142);
    lv_obj_set_scrollbar_mode(ui->ui_telaMain_cont_L1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(ui->ui_telaMain_cont_L1, LV_OBJ_FLAG_SCROLLABLE); //TIRAR SCROLL DO CONTAINER

    //Write style for ui_telaMain_cont_L1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_telaMain_cont_L1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->ui_telaMain_cont_L1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->ui_telaMain_cont_L1, lv_color_hex(0x1fdc2a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->ui_telaMain_cont_L1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_cont_L1, 35, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_cont_L1, 250, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_cont_L1, lv_color_hex(0x242424), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_cont_L1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_telaMain_cont_L1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_cont_L1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_cont_L1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_cont_L1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_cont_L1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_label_L1
    ui->ui_telaMain_label_L1 = lv_label_create(ui->ui_telaMain_cont_L1);
    lv_label_set_text(ui->ui_telaMain_label_L1, "L1");
    lv_label_set_long_mode(ui->ui_telaMain_label_L1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_telaMain_label_L1, 10, 10);
    lv_obj_set_size(ui->ui_telaMain_label_L1, 35, 31);

    //Write style for ui_telaMain_label_L1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_telaMain_label_L1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_label_L1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_label_L1, lv_color_hex(0x52DAFF), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_label_L1, &lv_font_Antonio_Regular_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_label_L1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_telaMain_label_L1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_telaMain_label_L1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_label_L1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_label_L1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_telaMain_label_L1, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_label_L1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_label_L1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_label_L1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_label_L1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_label_v_L1
    ui->ui_telaMain_label_v_L1 = lv_label_create(ui->ui_telaMain_cont_L1);
    lv_label_set_text(ui->ui_telaMain_label_v_L1, "V");
    lv_label_set_long_mode(ui->ui_telaMain_label_v_L1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_telaMain_label_v_L1, 155, 24);
    lv_obj_set_size(ui->ui_telaMain_label_v_L1, 45, 42);

    //Write style for ui_telaMain_label_v_L1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_telaMain_label_v_L1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_label_v_L1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_label_v_L1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_label_v_L1, &lv_font_Alatsi_Regular_26, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_label_v_L1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_telaMain_label_v_L1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_telaMain_label_v_L1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_label_v_L1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_label_v_L1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_telaMain_label_v_L1, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_label_v_L1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_label_v_L1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_label_v_L1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_label_v_L1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_label_mA_L1
    ui->ui_telaMain_label_mA_L1 = lv_label_create(ui->ui_telaMain_cont_L1);
    lv_label_set_text(ui->ui_telaMain_label_mA_L1, "mA");
    lv_label_set_long_mode(ui->ui_telaMain_label_mA_L1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_telaMain_label_mA_L1, 56, 68);
    lv_obj_set_size(ui->ui_telaMain_label_mA_L1, 45, 33);

    //Write style for ui_telaMain_label_mA_L1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_telaMain_label_mA_L1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_label_mA_L1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_label_mA_L1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_label_mA_L1, &lv_font_Alatsi_Regular_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_label_mA_L1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_telaMain_label_mA_L1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_telaMain_label_mA_L1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_label_mA_L1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_label_mA_L1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_telaMain_label_mA_L1, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_label_mA_L1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_label_mA_L1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_label_mA_L1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_label_mA_L1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_label_fp_L1
    ui->ui_telaMain_label_fp_L1 = lv_label_create(ui->ui_telaMain_cont_L1);
    lv_label_set_text(ui->ui_telaMain_label_fp_L1, "FP:");
    lv_label_set_long_mode(ui->ui_telaMain_label_fp_L1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_telaMain_label_fp_L1, 101, 68);
    lv_obj_set_size(ui->ui_telaMain_label_fp_L1, 45, 33);

    //Write style for ui_telaMain_label_fp_L1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_telaMain_label_fp_L1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_label_fp_L1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_label_fp_L1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_label_fp_L1, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_label_fp_L1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_telaMain_label_fp_L1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_telaMain_label_fp_L1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_label_fp_L1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_label_fp_L1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_telaMain_label_fp_L1, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_label_fp_L1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_label_fp_L1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_label_fp_L1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_label_fp_L1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_linhaSup_L1
    ui->ui_telaMain_linhaSup_L1 = lv_line_create(ui->ui_telaMain_cont_L1);
    static lv_point_t ui_telaMain_linhaSup_L1[] = {{0, 0},{600, 0},};
    lv_line_set_points(ui->ui_telaMain_linhaSup_L1, ui_telaMain_linhaSup_L1, 2);
    lv_obj_set_pos(ui->ui_telaMain_linhaSup_L1, 6, 68);
    lv_obj_set_size(ui->ui_telaMain_linhaSup_L1, 186, 4);

    //Write style for ui_telaMain_linhaSup_L1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->ui_telaMain_linhaSup_L1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->ui_telaMain_linhaSup_L1, lv_color_hex(0x656461), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->ui_telaMain_linhaSup_L1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_linhaInf_L1
    ui->ui_telaMain_linhaInf_L1 = lv_line_create(ui->ui_telaMain_cont_L1);
    static lv_point_t ui_telaMain_linhaInf_L1[] = {{0, 0},{600, 0},};
    lv_line_set_points(ui->ui_telaMain_linhaInf_L1, ui_telaMain_linhaInf_L1, 2);
    lv_obj_set_pos(ui->ui_telaMain_linhaInf_L1, 4, 100);
    lv_obj_set_size(ui->ui_telaMain_linhaInf_L1, 186, 4);

    //Write style for ui_telaMain_linhaInf_L1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->ui_telaMain_linhaInf_L1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->ui_telaMain_linhaInf_L1, lv_color_hex(0x656461), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->ui_telaMain_linhaInf_L1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_label_set_L1
    ui->ui_telaMain_label_set_L1 = lv_label_create(ui->ui_telaMain_cont_L1);
    lv_label_set_text(ui->ui_telaMain_label_set_L1, "SET:");
    lv_label_set_long_mode(ui->ui_telaMain_label_set_L1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_telaMain_label_set_L1, 4, 101);
    lv_obj_set_size(ui->ui_telaMain_label_set_L1, 60, 30);

    //Write style for ui_telaMain_label_set_L1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_telaMain_label_set_L1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_label_set_L1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_label_set_L1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_label_set_L1, &lv_font_montserratMedium_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_label_set_L1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_telaMain_label_set_L1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_telaMain_label_set_L1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_label_set_L1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_label_set_L1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_telaMain_label_set_L1, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_label_set_L1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_label_set_L1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_label_set_L1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_label_set_L1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_label_saida_L1
    ui->ui_telaMain_label_saida_L1 = lv_label_create(ui->ui_telaMain_cont_L1);
    lv_label_set_text(ui->ui_telaMain_label_saida_L1, "Saida:");
    lv_label_set_long_mode(ui->ui_telaMain_label_saida_L1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_telaMain_label_saida_L1, 1, 36);
    lv_obj_set_size(ui->ui_telaMain_label_saida_L1, 60, 30);

    //Write style for ui_telaMain_label_saida_L1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_telaMain_label_saida_L1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_label_saida_L1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_label_saida_L1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_label_saida_L1, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_label_saida_L1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_telaMain_label_saida_L1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_telaMain_label_saida_L1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_label_saida_L1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_label_saida_L1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_telaMain_label_saida_L1, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_label_saida_L1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_label_saida_L1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_label_saida_L1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_label_saida_L1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_lbDisplayL1
    ui->ui_telaMain_lbDisplayL1 = lv_label_create(ui->ui_telaMain_cont_L1);
    lv_label_set_text(ui->ui_telaMain_lbDisplayL1, "0.0");
    lv_label_set_long_mode(ui->ui_telaMain_lbDisplayL1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_telaMain_lbDisplayL1, 36, -5);
    lv_obj_set_size(ui->ui_telaMain_lbDisplayL1, 144, 82);

    //Write style for ui_telaMain_lbDisplayL1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_telaMain_lbDisplayL1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_lbDisplayL1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_lbDisplayL1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_lbDisplayL1, &lv_font_Antonio_Regular_56, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_lbDisplayL1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_telaMain_lbDisplayL1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_telaMain_lbDisplayL1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_lbDisplayL1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_lbDisplayL1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_telaMain_lbDisplayL1, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_lbDisplayL1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_lbDisplayL1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_lbDisplayL1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_lbDisplayL1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_lbCorrenteL1
    ui->ui_telaMain_lbCorrenteL1 = lv_label_create(ui->ui_telaMain_cont_L1);
    lv_label_set_text(ui->ui_telaMain_lbCorrenteL1, "123,4");
    lv_label_set_long_mode(ui->ui_telaMain_lbCorrenteL1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_telaMain_lbCorrenteL1, 1, 68);
    lv_obj_set_size(ui->ui_telaMain_lbCorrenteL1, 73, 33);

    //Write style for ui_telaMain_lbCorrenteL1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_telaMain_lbCorrenteL1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_lbCorrenteL1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_lbCorrenteL1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_lbCorrenteL1, &lv_font_Antonio_Regular_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_lbCorrenteL1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_telaMain_lbCorrenteL1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_telaMain_lbCorrenteL1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_lbCorrenteL1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_lbCorrenteL1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_telaMain_lbCorrenteL1, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_lbCorrenteL1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_lbCorrenteL1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_lbCorrenteL1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_lbCorrenteL1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_lbFatorL1
    ui->ui_telaMain_lbFatorL1 = lv_label_create(ui->ui_telaMain_cont_L1);
    lv_label_set_text(ui->ui_telaMain_lbFatorL1, "-0,99");
    lv_label_set_long_mode(ui->ui_telaMain_lbFatorL1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_telaMain_lbFatorL1, 130, 68);
    lv_obj_set_size(ui->ui_telaMain_lbFatorL1, 73, 33);

    //Write style for ui_telaMain_lbFatorL1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_telaMain_lbFatorL1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_lbFatorL1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_lbFatorL1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_lbFatorL1, &lv_font_Antonio_Regular_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_lbFatorL1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_telaMain_lbFatorL1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_telaMain_lbFatorL1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_lbFatorL1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_lbFatorL1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_telaMain_lbFatorL1, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_lbFatorL1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_lbFatorL1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_lbFatorL1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_lbFatorL1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_lbSetL1
    ui->ui_telaMain_lbSetL1 = lv_label_create(ui->ui_telaMain_cont_L1);
    lv_label_set_text(ui->ui_telaMain_lbSetL1, "0.0%");
    lv_label_set_long_mode(ui->ui_telaMain_lbSetL1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_telaMain_lbSetL1, 53, 99);
    lv_obj_set_size(ui->ui_telaMain_lbSetL1, 73, 33);

    //Write style for ui_telaMain_lbSetL1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_telaMain_lbSetL1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_lbSetL1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_lbSetL1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_lbSetL1, &lv_font_Antonio_Regular_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_lbSetL1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_telaMain_lbSetL1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_telaMain_lbSetL1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_lbSetL1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_lbSetL1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_telaMain_lbSetL1, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_lbSetL1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_lbSetL1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_lbSetL1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_lbSetL1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_cbHabL1
    ui->ui_telaMain_cbHabL1 = lv_checkbox_create(ui->ui_telaMain_cont_L1);
    lv_checkbox_set_text(ui->ui_telaMain_cbHabL1, "HAB");
    lv_obj_set_pos(ui->ui_telaMain_cbHabL1, 122, 107);
    lv_obj_add_state(ui->ui_telaMain_cbHabL1, LV_STATE_CHECKED);

    //Write style for ui_telaMain_cbHabL1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_pad_top(ui->ui_telaMain_cbHabL1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_cbHabL1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_cbHabL1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_cbHabL1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_cbHabL1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_cbHabL1, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_cbHabL1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_telaMain_cbHabL1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_telaMain_cbHabL1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_cbHabL1, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_cbHabL1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_cbHabL1, lv_color_hex(0x5a5b5b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_cbHabL1, LV_GRAD_DIR_HOR, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->ui_telaMain_cbHabL1, lv_color_hex(0x5a5b5b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui->ui_telaMain_cbHabL1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui->ui_telaMain_cbHabL1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_cbHabL1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui_telaMain_cbHabL1, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_pad_all(ui->ui_telaMain_cbHabL1, 3, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_telaMain_cbHabL1, 2, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->ui_telaMain_cbHabL1, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->ui_telaMain_cbHabL1, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->ui_telaMain_cbHabL1, LV_BORDER_SIDE_FULL, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_cbHabL1, 6, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_cbHabL1, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_cbHabL1, lv_color_hex(0xffffff), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_cbHabL1, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);

//---------------------------------------------------------------------------------------------------------------------

    //Write codes ui_telaMain_cont_L2
    ui->ui_telaMain_cont_L2 = lv_obj_create(ui->ui_telaMain_dashboard);
    lv_obj_set_pos(ui->ui_telaMain_cont_L2, 209, 1);
    lv_obj_set_size(ui->ui_telaMain_cont_L2, 205, 142);
    lv_obj_set_scrollbar_mode(ui->ui_telaMain_cont_L2, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(ui->ui_telaMain_cont_L2, LV_OBJ_FLAG_SCROLLABLE); //TIRAR SCROLL DO CONTAINER

    //Write style for ui_telaMain_cont_L2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_telaMain_cont_L2, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->ui_telaMain_cont_L2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->ui_telaMain_cont_L2, lv_color_hex(0x1fdc2a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->ui_telaMain_cont_L2, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_cont_L2, 35, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_cont_L2, 250, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_cont_L2, lv_color_hex(0x242424), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_cont_L2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_telaMain_cont_L2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_cont_L2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_cont_L2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_cont_L2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_cont_L2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_label_L2
    ui->ui_telaMain_label_L2 = lv_label_create(ui->ui_telaMain_cont_L2);
    lv_label_set_text(ui->ui_telaMain_label_L2, "L2");
    lv_label_set_long_mode(ui->ui_telaMain_label_L2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_telaMain_label_L2, 10, 10);
    lv_obj_set_size(ui->ui_telaMain_label_L2, 35, 31);

    //Write style for ui_telaMain_label_L2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_telaMain_label_L2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_label_L2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_label_L2, lv_color_hex(0x52DAFF), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_label_L2, &lv_font_Antonio_Regular_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_label_L2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_telaMain_label_L2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_telaMain_label_L2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_label_L2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_label_L2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_telaMain_label_L2, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_label_L2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_label_L2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_label_L2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_label_L2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_label_v_L2
    ui->ui_telaMain_label_v_L2 = lv_label_create(ui->ui_telaMain_cont_L2);
    lv_label_set_text(ui->ui_telaMain_label_v_L2, "V");
    lv_label_set_long_mode(ui->ui_telaMain_label_v_L2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_telaMain_label_v_L2, 155, 24);
    lv_obj_set_size(ui->ui_telaMain_label_v_L2, 45, 42);

    //Write style for ui_telaMain_label_v_L2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_telaMain_label_v_L2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_label_v_L2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_label_v_L2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_label_v_L2, &lv_font_Alatsi_Regular_26, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_label_v_L2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_telaMain_label_v_L2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_telaMain_label_v_L2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_label_v_L2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_label_v_L2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_telaMain_label_v_L2, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_label_v_L2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_label_v_L2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_label_v_L2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_label_v_L2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_label_mA_L2
    ui->ui_telaMain_label_mA_L2 = lv_label_create(ui->ui_telaMain_cont_L2);
    lv_label_set_text(ui->ui_telaMain_label_mA_L2, "mA");
    lv_label_set_long_mode(ui->ui_telaMain_label_mA_L2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_telaMain_label_mA_L2, 56, 68);
    lv_obj_set_size(ui->ui_telaMain_label_mA_L2, 45, 33);

    //Write style for ui_telaMain_label_mA_L2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_telaMain_label_mA_L2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_label_mA_L2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_label_mA_L2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_label_mA_L2, &lv_font_Alatsi_Regular_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_label_mA_L2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_telaMain_label_mA_L2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_telaMain_label_mA_L2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_label_mA_L2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_label_mA_L2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_telaMain_label_mA_L2, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_label_mA_L2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_label_mA_L2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_label_mA_L2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_label_mA_L2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_label_fp_L2
    ui->ui_telaMain_label_fp_L2 = lv_label_create(ui->ui_telaMain_cont_L2);
    lv_label_set_text(ui->ui_telaMain_label_fp_L2, "FP:");
    lv_label_set_long_mode(ui->ui_telaMain_label_fp_L2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_telaMain_label_fp_L2, 101, 68);
    lv_obj_set_size(ui->ui_telaMain_label_fp_L2, 45, 33);

    //Write style for ui_telaMain_label_fp_L2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_telaMain_label_fp_L2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_label_fp_L2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_label_fp_L2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_label_fp_L2, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_label_fp_L2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_telaMain_label_fp_L2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_telaMain_label_fp_L2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_label_fp_L2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_label_fp_L2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_telaMain_label_fp_L2, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_label_fp_L2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_label_fp_L2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_label_fp_L2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_label_fp_L2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_linhaSup_L2
    ui->ui_telaMain_linhaSup_L2 = lv_line_create(ui->ui_telaMain_cont_L2);
    static lv_point_t ui_telaMain_linhaSup_L2[] = {{0, 0},{600, 0},};
    lv_line_set_points(ui->ui_telaMain_linhaSup_L2, ui_telaMain_linhaSup_L2, 2);
    lv_obj_set_pos(ui->ui_telaMain_linhaSup_L2, 6, 68);
    lv_obj_set_size(ui->ui_telaMain_linhaSup_L2, 186, 4);

    //Write style for ui_telaMain_linhaSup_L2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->ui_telaMain_linhaSup_L2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->ui_telaMain_linhaSup_L2, lv_color_hex(0x656461), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->ui_telaMain_linhaSup_L2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_linhaInf_L2
    ui->ui_telaMain_linhaInf_L2 = lv_line_create(ui->ui_telaMain_cont_L2);
    static lv_point_t ui_telaMain_linhaInf_L2[] = {{0, 0},{600, 0},};
    lv_line_set_points(ui->ui_telaMain_linhaInf_L2, ui_telaMain_linhaInf_L2, 2);
    lv_obj_set_pos(ui->ui_telaMain_linhaInf_L2, 4, 100);
    lv_obj_set_size(ui->ui_telaMain_linhaInf_L2, 186, 4);

    //Write style for ui_telaMain_linhaInf_L2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->ui_telaMain_linhaInf_L2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->ui_telaMain_linhaInf_L2, lv_color_hex(0x656461), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->ui_telaMain_linhaInf_L2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_label_set_L2
    ui->ui_telaMain_label_set_L2 = lv_label_create(ui->ui_telaMain_cont_L2);
    lv_label_set_text(ui->ui_telaMain_label_set_L2, "SET:");
    lv_label_set_long_mode(ui->ui_telaMain_label_set_L2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_telaMain_label_set_L2, 4, 101);
    lv_obj_set_size(ui->ui_telaMain_label_set_L2, 60, 30);

    //Write style for ui_telaMain_label_set_L2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_telaMain_label_set_L2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_label_set_L2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_label_set_L2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_label_set_L2, &lv_font_montserratMedium_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_label_set_L2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_telaMain_label_set_L2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_telaMain_label_set_L2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_label_set_L2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_label_set_L2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_telaMain_label_set_L2, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_label_set_L2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_label_set_L2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_label_set_L2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_label_set_L2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_label_saida_L2
    ui->ui_telaMain_label_saida_L2 = lv_label_create(ui->ui_telaMain_cont_L2);
    lv_label_set_text(ui->ui_telaMain_label_saida_L2, "Saida:");
    lv_label_set_long_mode(ui->ui_telaMain_label_saida_L2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_telaMain_label_saida_L2, 1, 36);
    lv_obj_set_size(ui->ui_telaMain_label_saida_L2, 60, 30);

    //Write style for ui_telaMain_label_saida_L2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_telaMain_label_saida_L2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_label_saida_L2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_label_saida_L2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_label_saida_L2, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_label_saida_L2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_telaMain_label_saida_L2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_telaMain_label_saida_L2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_label_saida_L2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_label_saida_L2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_telaMain_label_saida_L2, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_label_saida_L2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_label_saida_L2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_label_saida_L2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_label_saida_L2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_lbDisplayL2
    ui->ui_telaMain_lbDisplayL2 = lv_label_create(ui->ui_telaMain_cont_L2);
    lv_label_set_text(ui->ui_telaMain_lbDisplayL2, "0.0");
    lv_label_set_long_mode(ui->ui_telaMain_lbDisplayL2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_telaMain_lbDisplayL2, 36, -5);
    lv_obj_set_size(ui->ui_telaMain_lbDisplayL2, 144, 82);

    //Write style for ui_telaMain_lbDisplayL2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_telaMain_lbDisplayL2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_lbDisplayL2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_lbDisplayL2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_lbDisplayL2, &lv_font_Antonio_Regular_56, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_lbDisplayL2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_telaMain_lbDisplayL2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_telaMain_lbDisplayL2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_lbDisplayL2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_lbDisplayL2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_telaMain_lbDisplayL2, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_lbDisplayL2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_lbDisplayL2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_lbDisplayL2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_lbDisplayL2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_lbCorrenteL2
    ui->ui_telaMain_lbCorrenteL2 = lv_label_create(ui->ui_telaMain_cont_L2);
    lv_label_set_text(ui->ui_telaMain_lbCorrenteL2, "123,4");
    lv_label_set_long_mode(ui->ui_telaMain_lbCorrenteL2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_telaMain_lbCorrenteL2, 1, 68);
    lv_obj_set_size(ui->ui_telaMain_lbCorrenteL2, 73, 33);

    //Write style for ui_telaMain_lbCorrenteL2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_telaMain_lbCorrenteL2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_lbCorrenteL2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_lbCorrenteL2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_lbCorrenteL2, &lv_font_Antonio_Regular_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_lbCorrenteL2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_telaMain_lbCorrenteL2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_telaMain_lbCorrenteL2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_lbCorrenteL2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_lbCorrenteL2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_telaMain_lbCorrenteL2, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_lbCorrenteL2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_lbCorrenteL2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_lbCorrenteL2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_lbCorrenteL2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_lbFatorL2
    ui->ui_telaMain_lbFatorL2 = lv_label_create(ui->ui_telaMain_cont_L2);
    lv_label_set_text(ui->ui_telaMain_lbFatorL2, "-0,99");
    lv_label_set_long_mode(ui->ui_telaMain_lbFatorL2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_telaMain_lbFatorL2, 130, 68);
    lv_obj_set_size(ui->ui_telaMain_lbFatorL2, 73, 33);

    //Write style for ui_telaMain_lbFatorL2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_telaMain_lbFatorL2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_lbFatorL2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_lbFatorL2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_lbFatorL2, &lv_font_Antonio_Regular_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_lbFatorL2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_telaMain_lbFatorL2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_telaMain_lbFatorL2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_lbFatorL2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_lbFatorL2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_telaMain_lbFatorL2, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_lbFatorL2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_lbFatorL2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_lbFatorL2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_lbFatorL2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_lbSetL2
    ui->ui_telaMain_lbSetL2 = lv_label_create(ui->ui_telaMain_cont_L2);
    lv_label_set_text(ui->ui_telaMain_lbSetL2, "0.0%");
    lv_label_set_long_mode(ui->ui_telaMain_lbSetL2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_telaMain_lbSetL2, 53, 99);
    lv_obj_set_size(ui->ui_telaMain_lbSetL2, 73, 33);

    //Write style for ui_telaMain_lbSetL2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_telaMain_lbSetL2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_lbSetL2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_lbSetL2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_lbSetL2, &lv_font_Antonio_Regular_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_lbSetL2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_telaMain_lbSetL2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_telaMain_lbSetL2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_lbSetL2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_lbSetL2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_telaMain_lbSetL2, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_lbSetL2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_lbSetL2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_lbSetL2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_lbSetL2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_cbHabL2
    ui->ui_telaMain_cbHabL2 = lv_checkbox_create(ui->ui_telaMain_cont_L2);
    lv_checkbox_set_text(ui->ui_telaMain_cbHabL2, "HAB");
    lv_obj_set_pos(ui->ui_telaMain_cbHabL2, 122, 107);
    lv_obj_add_state(ui->ui_telaMain_cbHabL2, LV_STATE_CHECKED);

    //Write style for ui_telaMain_cbHabL2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_pad_top(ui->ui_telaMain_cbHabL2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_cbHabL2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_cbHabL2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_cbHabL2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_cbHabL2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_cbHabL2, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_cbHabL2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_telaMain_cbHabL2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_telaMain_cbHabL2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_cbHabL2, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_cbHabL2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_cbHabL2, lv_color_hex(0x5a5b5b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_cbHabL2, LV_GRAD_DIR_HOR, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->ui_telaMain_cbHabL2, lv_color_hex(0x5a5b5b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui->ui_telaMain_cbHabL2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui->ui_telaMain_cbHabL2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_cbHabL2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui_telaMain_cbHabL2, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_pad_all(ui->ui_telaMain_cbHabL2, 3, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_telaMain_cbHabL2, 2, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->ui_telaMain_cbHabL2, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->ui_telaMain_cbHabL2, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->ui_telaMain_cbHabL2, LV_BORDER_SIDE_FULL, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_cbHabL2, 6, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_cbHabL2, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_cbHabL2, lv_color_hex(0xffffff), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_cbHabL2, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);

//---------------------------------------------------------------------------------------------------------------------

    //Write codes ui_telaMain_cont_L3
    ui->ui_telaMain_cont_L3 = lv_obj_create(ui->ui_telaMain_dashboard);
    lv_obj_set_pos(ui->ui_telaMain_cont_L3, 420, 1);
    lv_obj_set_size(ui->ui_telaMain_cont_L3, 205, 142);
    lv_obj_set_scrollbar_mode(ui->ui_telaMain_cont_L3, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(ui->ui_telaMain_cont_L3, LV_OBJ_FLAG_SCROLLABLE); //TIRAR SCROLL DO CONTAINER

    //Write style for ui_telaMain_cont_L3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_telaMain_cont_L3, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->ui_telaMain_cont_L3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->ui_telaMain_cont_L3, lv_color_hex(0x1fdc2a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->ui_telaMain_cont_L3, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_cont_L3, 35, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_cont_L3, 250, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_cont_L3, lv_color_hex(0x242424), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_cont_L3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_telaMain_cont_L3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_cont_L3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_cont_L3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_cont_L3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_cont_L3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_label_L3
    ui->ui_telaMain_label_L3 = lv_label_create(ui->ui_telaMain_cont_L3);
    lv_label_set_text(ui->ui_telaMain_label_L3, "L3");
    lv_label_set_long_mode(ui->ui_telaMain_label_L3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_telaMain_label_L3, 10, 10);
    lv_obj_set_size(ui->ui_telaMain_label_L3, 35, 31);

    //Write style for ui_telaMain_label_L3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_telaMain_label_L3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_label_L3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_label_L3, lv_color_hex(0x52DAFF), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_label_L3, &lv_font_Antonio_Regular_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_label_L3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_telaMain_label_L3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_telaMain_label_L3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_label_L3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_label_L3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_telaMain_label_L3, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_label_L3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_label_L3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_label_L3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_label_L3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_label_v_L3
    ui->ui_telaMain_label_v_L3 = lv_label_create(ui->ui_telaMain_cont_L3);
    lv_label_set_text(ui->ui_telaMain_label_v_L3, "V");
    lv_label_set_long_mode(ui->ui_telaMain_label_v_L3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_telaMain_label_v_L3, 155, 24);
    lv_obj_set_size(ui->ui_telaMain_label_v_L3, 45, 42);

    //Write style for ui_telaMain_label_v_L3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_telaMain_label_v_L3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_label_v_L3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_label_v_L3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_label_v_L3, &lv_font_Alatsi_Regular_26, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_label_v_L3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_telaMain_label_v_L3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_telaMain_label_v_L3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_label_v_L3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_label_v_L3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_telaMain_label_v_L3, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_label_v_L3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_label_v_L3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_label_v_L3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_label_v_L3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_label_mA_L3
    ui->ui_telaMain_label_mA_L3 = lv_label_create(ui->ui_telaMain_cont_L3);
    lv_label_set_text(ui->ui_telaMain_label_mA_L3, "mA");
    lv_label_set_long_mode(ui->ui_telaMain_label_mA_L3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_telaMain_label_mA_L3, 56, 68);
    lv_obj_set_size(ui->ui_telaMain_label_mA_L3, 45, 33);

    //Write style for ui_telaMain_label_mA_L3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_telaMain_label_mA_L3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_label_mA_L3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_label_mA_L3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_label_mA_L3, &lv_font_Alatsi_Regular_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_label_mA_L3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_telaMain_label_mA_L3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_telaMain_label_mA_L3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_label_mA_L3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_label_mA_L3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_telaMain_label_mA_L3, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_label_mA_L3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_label_mA_L3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_label_mA_L3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_label_mA_L3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_label_fp_L3
    ui->ui_telaMain_label_fp_L3 = lv_label_create(ui->ui_telaMain_cont_L3);
    lv_label_set_text(ui->ui_telaMain_label_fp_L3, "FP:");
    lv_label_set_long_mode(ui->ui_telaMain_label_fp_L3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_telaMain_label_fp_L3, 101, 68);
    lv_obj_set_size(ui->ui_telaMain_label_fp_L3, 45, 33);

    //Write style for ui_telaMain_label_fp_L3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_telaMain_label_fp_L3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_label_fp_L3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_label_fp_L3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_label_fp_L3, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_label_fp_L3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_telaMain_label_fp_L3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_telaMain_label_fp_L3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_label_fp_L3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_label_fp_L3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_telaMain_label_fp_L3, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_label_fp_L3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_label_fp_L3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_label_fp_L3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_label_fp_L3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_linhaSup_L3
    ui->ui_telaMain_linhaSup_L3 = lv_line_create(ui->ui_telaMain_cont_L3);
    static lv_point_t ui_telaMain_linhaSup_L3[] = {{0, 0},{600, 0},};
    lv_line_set_points(ui->ui_telaMain_linhaSup_L3, ui_telaMain_linhaSup_L3, 2);
    lv_obj_set_pos(ui->ui_telaMain_linhaSup_L3, 6, 68);
    lv_obj_set_size(ui->ui_telaMain_linhaSup_L3, 186, 4);

    //Write style for ui_telaMain_linhaSup_L3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->ui_telaMain_linhaSup_L3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->ui_telaMain_linhaSup_L3, lv_color_hex(0x656461), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->ui_telaMain_linhaSup_L3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_linhaInf_L3
    ui->ui_telaMain_linhaInf_L3 = lv_line_create(ui->ui_telaMain_cont_L3);
    static lv_point_t ui_telaMain_linhaInf_L3[] = {{0, 0},{600, 0},};
    lv_line_set_points(ui->ui_telaMain_linhaInf_L3, ui_telaMain_linhaInf_L3, 2);
    lv_obj_set_pos(ui->ui_telaMain_linhaInf_L3, 4, 100);
    lv_obj_set_size(ui->ui_telaMain_linhaInf_L3, 186, 4);

    //Write style for ui_telaMain_linhaInf_L3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->ui_telaMain_linhaInf_L3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->ui_telaMain_linhaInf_L3, lv_color_hex(0x656461), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->ui_telaMain_linhaInf_L3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_label_set_L3
    ui->ui_telaMain_label_set_L3 = lv_label_create(ui->ui_telaMain_cont_L3);
    lv_label_set_text(ui->ui_telaMain_label_set_L3, "SET:");
    lv_label_set_long_mode(ui->ui_telaMain_label_set_L3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_telaMain_label_set_L3, 4, 101);
    lv_obj_set_size(ui->ui_telaMain_label_set_L3, 60, 30);

    //Write style for ui_telaMain_label_set_L3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_telaMain_label_set_L3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_label_set_L3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_label_set_L3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_label_set_L3, &lv_font_montserratMedium_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_label_set_L3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_telaMain_label_set_L3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_telaMain_label_set_L3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_label_set_L3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_label_set_L3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_telaMain_label_set_L3, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_label_set_L3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_label_set_L3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_label_set_L3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_label_set_L3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_label_saida_L3
    ui->ui_telaMain_label_saida_L3 = lv_label_create(ui->ui_telaMain_cont_L3);
    lv_label_set_text(ui->ui_telaMain_label_saida_L3, "Saida:");
    lv_label_set_long_mode(ui->ui_telaMain_label_saida_L3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_telaMain_label_saida_L3, 1, 36);
    lv_obj_set_size(ui->ui_telaMain_label_saida_L3, 60, 30);

    //Write style for ui_telaMain_label_saida_L3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_telaMain_label_saida_L3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_label_saida_L3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_label_saida_L3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_label_saida_L3, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_label_saida_L3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_telaMain_label_saida_L3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_telaMain_label_saida_L3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_label_saida_L3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_label_saida_L3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_telaMain_label_saida_L3, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_label_saida_L3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_label_saida_L3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_label_saida_L3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_label_saida_L3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_lbDisplayL3
    ui->ui_telaMain_lbDisplayL3 = lv_label_create(ui->ui_telaMain_cont_L3);
    lv_label_set_text(ui->ui_telaMain_lbDisplayL3, "0.0");
    lv_label_set_long_mode(ui->ui_telaMain_lbDisplayL3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_telaMain_lbDisplayL3, 36, -5);
    lv_obj_set_size(ui->ui_telaMain_lbDisplayL3, 144, 82);

    //Write style for ui_telaMain_lbDisplayL3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_telaMain_lbDisplayL3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_lbDisplayL3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_lbDisplayL3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_lbDisplayL3, &lv_font_Antonio_Regular_56, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_lbDisplayL3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_telaMain_lbDisplayL3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_telaMain_lbDisplayL3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_lbDisplayL3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_lbDisplayL3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_telaMain_lbDisplayL3, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_lbDisplayL3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_lbDisplayL3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_lbDisplayL3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_lbDisplayL3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_lbCorrenteL3
    ui->ui_telaMain_lbCorrenteL3 = lv_label_create(ui->ui_telaMain_cont_L3);
    lv_label_set_text(ui->ui_telaMain_lbCorrenteL3, "123,4");
    lv_label_set_long_mode(ui->ui_telaMain_lbCorrenteL3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_telaMain_lbCorrenteL3, 1, 68);
    lv_obj_set_size(ui->ui_telaMain_lbCorrenteL3, 73, 33);

    //Write style for ui_telaMain_lbCorrenteL3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_telaMain_lbCorrenteL3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_lbCorrenteL3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_lbCorrenteL3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_lbCorrenteL3, &lv_font_Antonio_Regular_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_lbCorrenteL3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_telaMain_lbCorrenteL3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_telaMain_lbCorrenteL3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_lbCorrenteL3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_lbCorrenteL3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_telaMain_lbCorrenteL3, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_lbCorrenteL3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_lbCorrenteL3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_lbCorrenteL3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_lbCorrenteL3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_lbFatorL3
    ui->ui_telaMain_lbFatorL3 = lv_label_create(ui->ui_telaMain_cont_L3);
    lv_label_set_text(ui->ui_telaMain_lbFatorL3, "-0,99");
    lv_label_set_long_mode(ui->ui_telaMain_lbFatorL3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_telaMain_lbFatorL3, 130, 68);
    lv_obj_set_size(ui->ui_telaMain_lbFatorL3, 73, 33);

    //Write style for ui_telaMain_lbFatorL3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_telaMain_lbFatorL3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_lbFatorL3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_lbFatorL3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_lbFatorL3, &lv_font_Antonio_Regular_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_lbFatorL3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_telaMain_lbFatorL3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_telaMain_lbFatorL3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_lbFatorL3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_lbFatorL3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_telaMain_lbFatorL3, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_lbFatorL3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_lbFatorL3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_lbFatorL3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_lbFatorL3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_lbSetL3
    ui->ui_telaMain_lbSetL3 = lv_label_create(ui->ui_telaMain_cont_L3);
    lv_label_set_text(ui->ui_telaMain_lbSetL3, "0.0%");
    lv_label_set_long_mode(ui->ui_telaMain_lbSetL3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ui_telaMain_lbSetL3, 53, 99);
    lv_obj_set_size(ui->ui_telaMain_lbSetL3, 73, 33);

    //Write style for ui_telaMain_lbSetL3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_telaMain_lbSetL3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_lbSetL3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_lbSetL3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_lbSetL3, &lv_font_Antonio_Regular_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_lbSetL3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_telaMain_lbSetL3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->ui_telaMain_lbSetL3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_lbSetL3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_lbSetL3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_telaMain_lbSetL3, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_lbSetL3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_lbSetL3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_lbSetL3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_lbSetL3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_cbHabL3
    ui->ui_telaMain_cbHabL3 = lv_checkbox_create(ui->ui_telaMain_cont_L3);
    lv_checkbox_set_text(ui->ui_telaMain_cbHabL3, "HAB");
    lv_obj_set_pos(ui->ui_telaMain_cbHabL3, 122, 107);
    lv_obj_add_state(ui->ui_telaMain_cbHabL3, LV_STATE_CHECKED);

    //Write style for ui_telaMain_cbHabL3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_pad_top(ui->ui_telaMain_cbHabL3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_cbHabL3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_cbHabL3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_cbHabL3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_cbHabL3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_cbHabL3, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_cbHabL3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->ui_telaMain_cbHabL3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_telaMain_cbHabL3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_cbHabL3, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_cbHabL3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_cbHabL3, lv_color_hex(0x5a5b5b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_cbHabL3, LV_GRAD_DIR_HOR, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->ui_telaMain_cbHabL3, lv_color_hex(0x5a5b5b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui->ui_telaMain_cbHabL3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui->ui_telaMain_cbHabL3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_cbHabL3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui_telaMain_cbHabL3, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_pad_all(ui->ui_telaMain_cbHabL3, 3, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_telaMain_cbHabL3, 2, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->ui_telaMain_cbHabL3, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->ui_telaMain_cbHabL3, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->ui_telaMain_cbHabL3, LV_BORDER_SIDE_FULL, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_cbHabL3, 6, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_cbHabL3, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_cbHabL3, lv_color_hex(0xffffff), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_cbHabL3, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);

//---------------------------------------------------------------------------------------------------------------------

//Write codes ui_telaMain_cont_OnOff
    ui->ui_telaMain_cont_OnOff = lv_obj_create(ui->ui_telaMain_dashboard);
    lv_obj_set_pos(ui->ui_telaMain_cont_OnOff, 629, 1);
    lv_obj_set_size(ui->ui_telaMain_cont_OnOff, 167, 68);
    lv_obj_set_scrollbar_mode(ui->ui_telaMain_cont_OnOff, LV_SCROLLBAR_MODE_OFF);

    //Write style for ui_telaMain_cont_OnOff, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->ui_telaMain_cont_OnOff, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->ui_telaMain_cont_OnOff, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->ui_telaMain_cont_OnOff, lv_color_hex(0x4A4C4A), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->ui_telaMain_cont_OnOff, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_cont_OnOff, 35, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->ui_telaMain_cont_OnOff, 250, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_cont_OnOff, lv_color_hex(0x242424), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_cont_OnOff, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->ui_telaMain_cont_OnOff, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->ui_telaMain_cont_OnOff, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->ui_telaMain_cont_OnOff, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->ui_telaMain_cont_OnOff, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_cont_OnOff, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes ui_telaMain_btnOnOff
    ui->ui_telaMain_btnOnOff = lv_btn_create(ui->ui_telaMain_cont_OnOff);
    ui->ui_telaMain_label_btnOnOff = lv_label_create(ui->ui_telaMain_btnOnOff);
    lv_label_set_text(ui->ui_telaMain_label_btnOnOff, "LIGAR");
    lv_label_set_long_mode(ui->ui_telaMain_label_btnOnOff, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->ui_telaMain_label_btnOnOff, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->ui_telaMain_btnOnOff, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->ui_telaMain_label_btnOnOff, LV_PCT(100));
    lv_obj_set_pos(ui->ui_telaMain_btnOnOff, 23, 6);
    lv_obj_set_size(ui->ui_telaMain_btnOnOff, 120, 53);

    //Write style for ui_telaMain_btnOnOff, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->ui_telaMain_btnOnOff, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btnOnOff, lv_color_hex(0x2FDA64), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_btnOnOff, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->ui_telaMain_btnOnOff, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_btnOnOff, 17, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_btnOnOff, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->ui_telaMain_btnOnOff, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->ui_telaMain_btnOnOff, &lv_font_montserratMedium_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->ui_telaMain_btnOnOff, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->ui_telaMain_btnOnOff, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for ui_telaMain_btnOnOff, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->ui_telaMain_btnOnOff, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->ui_telaMain_btnOnOff, lv_color_hex(0x18C220), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->ui_telaMain_btnOnOff, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->ui_telaMain_btnOnOff, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->ui_telaMain_btnOnOff, 17, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->ui_telaMain_btnOnOff, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->ui_telaMain_btnOnOff, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->ui_telaMain_btnOnOff, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->ui_telaMain_btnOnOff, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //Init events for screen.
    events_init_ui_telaMain(ui);
    // sinaliza que pode atualizar os valores
    dashboardCreated = 1;

}

//*******************************************************************************************
// ponteiro para ui
//*******************************************************************************************

lv_ui  *getUiTelaMain(void){
    return &uiTelaMain;
}

void ihmTelaMainInit() {
    createMainUI(&uiTelaMain);
}

void ihmTelaMainTask() {
    // Tarefas periódicas, se necessário
}