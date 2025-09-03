#include <Arduino.h>
#include <lvgl.h>
#include "events.h"
#include "masterControl.h"

//*****************************************************************************
// evento inicializacao da tela
//*****************************************************************************
void ui_telaMain_event_handler (lv_event_t *e){
    lv_event_code_t code = lv_event_get_code(e);

    switch (code) {
        case LV_EVENT_SCREEN_LOADED:
            Serial.println("LV_EVENT_SCREEN_LOADED");
            break;
        default:

            break;
    }
}
//*****************************************************************************
// Botão ON/OFF 
//*****************************************************************************
static void ui_telaMain_btn_onoff_event_handler (lv_event_t *e){
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t *id_btn = lv_event_get_target(e);
  lv_ui *ui = getUiTelaMain();
  STATUS_GST *gst = getPtrStatusGst();
  char convstr[32];

  if (code == LV_EVENT_CLICKED) {
    if (id_btn == ui->ui_telaMain_btnOnOff) {
      Serial.println("Clique ON/OFF");
      //Verifica o status do botao de ON/OFF.
      if(gst->statusBtnOnOff==0){
        gst->statusBtnOnOff = 1;
        lv_obj_set_style_bg_color(ui->ui_telaMain_btnOnOff, lv_color_hex(0x2FDA64), LV_PART_MAIN|LV_STATE_DEFAULT);
        lv_label_set_text(ui->ui_telaMain_label_btnOnOff, "LIGAR");
      }else{
        gst->statusBtnOnOff = 0;
        lv_obj_set_style_bg_color(ui->ui_telaMain_btnOnOff, lv_color_hex(0xFF002D), LV_PART_MAIN|LV_STATE_DEFAULT);
        lv_label_set_text(ui->ui_telaMain_label_btnOnOff, "DESLIGAR");
      }
    }
  }
}


//*****************************************************************************
// Inicialização dos eventos da Dashboard
//*****************************************************************************
void events_init_ui_telaMain(lv_ui *ui) {
    lv_obj_add_event_cb(ui->ui_telaMain_dashboard, ui_telaMain_event_handler, LV_EVENT_SCREEN_LOADED, ui); // LV_EVENT_ALL
    lv_obj_add_event_cb(ui->ui_telaMain_btnOnOff, ui_telaMain_btn_onoff_event_handler, LV_EVENT_ALL, ui);
}
//=============================================================================
void eventsInit() {
    // Inicialização de eventos, se necessário
}

void eventsTask() {
    // Tarefas periódicas de eventos, se necessário
}
