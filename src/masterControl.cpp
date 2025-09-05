#include <Arduino.h>
#include "masterControl.h"
#include "UartTron.h"
#include "events.h"

STATUS_GST statusGst;

uint8_t bufferTx[48];
uint32_t LRefresh = 0;
static uint8_t currentState = STATE_IDLE;
static uint8_t lastPacketBuffer[MAX_PACKET_SIZE];
static uint8_t lastPacketSize = 0;
static unsigned long stateTimeout = 0;

STATUS_GST *getPtrStatusGst(void){
    return &statusGst;
}

void masterControlInit(){
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
    statusGst.tensaoL1 = 0;       
    statusGst.tensaoL2 = 0;      
    statusGst.tensaoL3 = 0;      
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
    setUartReceivedCallback(masterControlHandlePacket); // Configura o callback
}

void masterControlTask() {
    /* Serial.print("Estado atual: "); // Depuração
    Serial.println(currentState); */
    switch (currentState) {
        case STATE_IDLE:
            if (millis() > LRefresh + TIME_REFRESH) {
                currentState = STATE_SEND_REFRESH;
            }
            break;
        case STATE_SEND_REFRESH:
            sendRefreshCommand();
            stateTimeout = millis();
            currentState = STATE_WAIT_STATUS;
            break;
        case STATE_WAIT_STATUS:
            if (millis() > stateTimeout + TIMEOUT_STATUS) {
                //Serial.println("Timeout aguardando STATUS");
                currentState = STATE_IDLE;
                LRefresh = millis();
            }
            break;
        case STATE_PROCESS_COMMAND:
            processStatusCommand();
            break;
    }
}

void sendRefreshCommand() {
    STATUS_GST *gst = getPtrStatusGst();
    uint8_t indexTx = 0;
    bufferTx[indexTx++] = START_BYTE;
    bufferTx[indexTx++] = CMD_REFRESH;
    bufferTx[indexTx++] = REFRESH_PAYLOAD_SIZE;
    //bufferTx[indexTx++] = !gst->statusBtnOnOff;
    bufferTx[indexTx++] = (gst->habL1 << 0) | (gst->habL2 << 1) | (gst->habL3 << 2);
    uint16_t freq = static_cast<uint16_t>(gst->freqAt * 10);
    bufferTx[indexTx++] = (freq >> 8) & 0xFF;
    bufferTx[indexTx++] = freq & 0xFF;
    uint16_t setpointL1 = static_cast<uint16_t>(gst->setPointL1 * 10);
    bufferTx[indexTx++] = (setpointL1 >> 8) & 0xFF;
    bufferTx[indexTx++] = setpointL1 & 0xFF;
    uint16_t setpointL2 = static_cast<uint16_t>(gst->setPointL2 * 10);
    bufferTx[indexTx++] = (setpointL2 >> 8) & 0xFF;
    bufferTx[indexTx++] = setpointL2 & 0xFF;
    uint16_t setpointL3 = static_cast<uint16_t>(gst->setPointL3 * 10);
    bufferTx[indexTx++] = (setpointL3 >> 8) & 0xFF;
    bufferTx[indexTx++] = setpointL3 & 0xFF;
    bufferTx[indexTx++] = gst->outL1;
    bufferTx[indexTx++] = gst->outL2;
    bufferTx[indexTx++] = gst->outL3;
    bufferTx[indexTx++] = (gst->correnteMaxL1 >> 8) & 0xFF;
    bufferTx[indexTx++] = gst->correnteMaxL1 & 0xFF;
    bufferTx[indexTx++] = (gst->correnteMaxL2 >> 8) & 0xFF;
    bufferTx[indexTx++] = gst->correnteMaxL2 & 0xFF;
    bufferTx[indexTx++] = (gst->correnteMaxL3 >> 8) & 0xFF;
    bufferTx[indexTx++] = gst->correnteMaxL3 & 0xFF;
    bufferTx[indexTx++] = gst->modeAcDc;
    uint16_t escala = static_cast<uint16_t>(gst->vEscala * 10);
    bufferTx[indexTx++] = (escala >> 8) & 0xFF;
    bufferTx[indexTx++] = escala & 0xFF;
    uint16_t percentL1 = static_cast<uint16_t>(gst->setPointPercentL1 * 10);
    bufferTx[indexTx++] = (percentL1 >> 8) & 0xFF;
    bufferTx[indexTx++] = percentL1 & 0xFF;
    uint16_t percentL2 = static_cast<uint16_t>(gst->setPointPercentL2 * 10);
    bufferTx[indexTx++] = (percentL2 >> 8) & 0xFF;
    bufferTx[indexTx++] = percentL2 & 0xFF;
    uint16_t percentL3 = static_cast<uint16_t>(gst->setPointPercentL3 * 10);
    bufferTx[indexTx++] = (percentL3 >> 8) & 0xFF;
    bufferTx[indexTx++] = percentL3 & 0xFF;
    uint8_t crc = uartTronCrcSlow(bufferTx, indexTx);
    bufferTx[indexTx++] = crc;
    Serial.print("Pacote enviado: ");
    for (uint8_t i = 0; i < indexTx; i++) {
        Serial.print("0x"); Serial.print(bufferTx[i], HEX); Serial.print(" ");
    }
    Serial.println();
    uartTronSendBuffer(bufferTx, indexTx);
}

void processStatusCommand() {
    if (lastPacketSize != STATUS_PAYLOAD_SIZE + 1 || lastPacketBuffer[1] != CMD_STATUS) {
        Serial.println("Erro: Pacote Status inválido ou tamanho incorreto! Tamanho: " + String(lastPacketSize));
        currentState = STATE_IDLE;
        return;
    }
    Serial.println("Pacote Status recebido com sucesso.");
    STATUS_GST *gst = getPtrStatusGst();
    uint8_t index = 3;
    gst->statusBtnOnOff = lastPacketBuffer[index++];
    gst->tensaoL1 = ((lastPacketBuffer[index] << 8) | lastPacketBuffer[index + 1]) / 10.0;
    index += 2;
    gst->tensaoL2 = ((lastPacketBuffer[index] << 8) | lastPacketBuffer[index + 1]) / 10.0;
    index += 2;
    gst->tensaoL3 = ((lastPacketBuffer[index] << 8) | lastPacketBuffer[index + 1]) / 10.0;
    index += 2;
    gst->correnteL1 = (lastPacketBuffer[index] << 8) | lastPacketBuffer[index + 1];
    index += 2;
    gst->correnteL2 = (lastPacketBuffer[index] << 8) | lastPacketBuffer[index + 1];
    index += 2;
    gst->correnteL3 = (lastPacketBuffer[index] << 8) | lastPacketBuffer[index + 1];
    index += 2;
    gst->fatorDePotenciaL1 = (lastPacketBuffer[index] << 8) | lastPacketBuffer[index + 1];
    index += 2;
    gst->fatorDePotenciaL2 = (lastPacketBuffer[index] << 8) | lastPacketBuffer[index + 1];
    index += 2;
    gst->fatorDePotenciaL3 = (lastPacketBuffer[index] << 8) | lastPacketBuffer[index + 1];
    index += 2;
    gst->statusPlacaL1 = lastPacketBuffer[index++];
    gst->statusPlacaL2 = lastPacketBuffer[index++];
    gst->statusPlacaL3 = lastPacketBuffer[index++];
    Serial.println("Valores atualizados: VL1=" + String(gst->tensaoL1) + ", correnteL1=" + String(gst->correnteL1) + ", FPL1="+ String(gst->fatorDePotenciaL1)+ ", VL2=" + String(gst->tensaoL2)+ ", correnteL2=" + String(gst->correnteL2) + ", FPL2="+ String(gst->fatorDePotenciaL2)+ ", VL3=" + String(gst->tensaoL3)+ ", correnteL3=" + String(gst->correnteL3) + ", FPL3="+ String(gst->fatorDePotenciaL3));
    ihmDashboardRefresh();
    LRefresh = millis();
    currentState = STATE_IDLE;
}

void masterControlHandlePacket(uint8_t* packet, uint8_t size) {
    Serial.print("Pacote recebido: ");
    for (uint8_t i = 0; i < size; i++) {
        Serial.print("0x"); Serial.print(packet[i], HEX); Serial.print(" ");
    }
    Serial.println();
    if (size <= MAX_PACKET_SIZE) {
        memcpy(lastPacketBuffer, packet, size);
        lastPacketSize = size;
        currentState = STATE_PROCESS_COMMAND;
        stateTimeout = millis();
    } else {
        Serial.println("Erro: Pacote da excede tamanho máximo!");
        currentState = STATE_IDLE;
    }
}