#include <Arduino.h>
#include "masterControl.h"
STATUS_GST statusGst;

uint8_t bufferTx[48];
uint32_t LRefresh = 0;

//*******************************************************************************************
// ponteiro para o status do gst
//*******************************************************************************************

STATUS_GST *getPtrStatusGst(void){
    return &statusGst;
}

void masterControlInit(){
  // Aqui você pode adicionar a inicialização de sensores, atuadores, etc.
  statusGst.statusBtnOnOff = STATUS_BTN_ONOFF;
  statusGst.modeVolt = 0;
  
  statusGst.atvL1 = STATUS_L1;
  statusGst.atvL2 = STATUS_L2;
  statusGst.atvL3 = STATUS_L3;

  statusGst.outL1 = CONST_FASE_L1;
  statusGst.outL2 = CONST_FASE_L2;
  statusGst.outL3 = CONST_FASE_L3;

  statusGst.atvGrupoFases = STATUS_GRUPO_FASES;
  statusGst.vEscala = ESCALA_PADRAO;
  statusGst.valPasso = PASSO_PADRAO;
  statusGst.freqSlider = FREQ_SLIDER_PADRAO;
  statusGst.freqAt = FREQ_PADRAO;
  statusGst.setPointL1 = SETPOINT_L1;
  statusGst.setPointL2 = SETPOINT_L2;
  statusGst.setPointL3 = SETPOINT_L3;
  statusGst.habL1 = 1;
  statusGst.habL2 = 1;
  statusGst.habL3 = 1;
  
  statusGst.correnteL1 = 0;
  statusGst.correnteL2 = 0;
  statusGst.correnteL3 = 0;
  statusGst.fatorDePotenciaL1 = 0;
  statusGst.fatorDePotenciaL2 = 0;
  statusGst.fatorDePotenciaL3 = 0;
  statusGst.statusPlacaL1 = 0;
  statusGst.statusPlacaL2 = 0;
  statusGst.statusPlacaL3 = 0;
}

void masterControlTask() {
    if(millis() > LRefresh + TIME_REFRESH) {
        //sendRefreshCommand();
        LRefresh = millis();
    }
}