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
    lv_obj_set_style_text_font(ui->ui_telaMain_btnAgrupar, &lv_font_SourceHanSerifSC_Regular_18, LV_PART_MAIN|LV_STATE_PRESSED);
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

}

void ihmTelaMainInit() {
    static ui_t ui;
    createMainUI(&ui);
}

void ihmTelaMainTask() {
    // Tarefas periódicas, se necessário
}