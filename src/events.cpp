#include <Arduino.h>
#include <lvgl.h>
#include "events.h"

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
// Inicialização dos eventos da Dashboard
//*****************************************************************************
void events_init_ui_telaMain(lv_ui *ui) {
    lv_obj_add_event_cb(ui->ui_telaMain_dashboard, ui_telaMain_event_handler, LV_EVENT_SCREEN_LOADED, ui); // LV_EVENT_ALL
}
//=============================================================================
void eventsInit() {
    // Inicialização de eventos, se necessário
}

void eventsTask() {
    // Tarefas periódicas de eventos, se necessário
}
