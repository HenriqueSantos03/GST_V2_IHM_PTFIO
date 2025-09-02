#include <Arduino.h>
#include <lvgl.h>
#include "ihmTelaMain.h"
#include "events.h"
#include "fonts/fonts.h"
#include "images/images.h"

void createMainUI(ui_t *ui) {
    // Criar container principal (equivalente a ui_telaMain)
    ui->ui_telaMain_dashboard = lv_obj_create(lv_scr_act());
    lv_obj_set_size(ui->ui_telaMain_dashboard, 800, 480);
    lv_obj_set_scrollbar_mode(ui->ui_telaMain_dashboard, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(ui->ui_telaMain_dashboard, LV_OBJ_FLAG_SCROLLABLE); // Desativar scroll
    lv_obj_set_style_bg_opa(ui->ui_telaMain_dashboard, 0, LV_PART_MAIN | LV_STATE_DEFAULT); // Fundo transparente

    // Criar container principal (equivalente a ui_telaMain_cont_Main)
    ui->ui_telaMain_containerMain = lv_obj_create(ui->ui_telaMain_dashboard);
    lv_obj_set_pos(ui->ui_telaMain_containerMain, -20, 120); // Ajustado para começar no canto superior esquerdo
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
    //lv_obj_add_flag(ui->ui_telaMain_btn_upL1, LV_OBJ_FLAG_HIDDEN); //esconde o botão

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
    //lv_obj_add_flag(ui->ui_telaMain_img_upL1, LV_OBJ_FLAG_HIDDEN); // esconde o objeto na inicialização

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
    //lv_obj_add_flag(ui->ui_telaMain_btn_downL1, LV_OBJ_FLAG_HIDDEN); //esconde o botão

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
    //lv_obj_add_flag(ui->ui_telaMain_img_downL1, LV_OBJ_FLAG_HIDDEN); // esconde o objeto na inicialização

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
    //lv_obj_add_flag(ui->ui_telaMain_btn_upL3, LV_OBJ_FLAG_HIDDEN); //esconde o botão

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
    //lv_obj_add_flag(ui->ui_telaMain_img_upL3, LV_OBJ_FLAG_HIDDEN); // esconde o objeto na inicialização

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
    //lv_obj_add_flag(ui->ui_telaMain_btn_downL3, LV_OBJ_FLAG_HIDDEN); //esconde o botão

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
    //lv_obj_add_flag(ui->ui_telaMain_img_downL3, LV_OBJ_FLAG_HIDDEN); // esconde o objeto na inicialização

    //Write style for ui_telaMain_img_downL3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->ui_telaMain_img_downL3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->ui_telaMain_img_downL3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->ui_telaMain_img_downL3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->ui_telaMain_img_downL3, true, LV_PART_MAIN|LV_STATE_DEFAULT);
//==================================================================================================================


}

void ihmTelaMainInit() {
    static ui_t ui;
    createMainUI(&ui);
}

void ihmTelaMainTask() {
    // Tarefas periódicas, se necessário
}