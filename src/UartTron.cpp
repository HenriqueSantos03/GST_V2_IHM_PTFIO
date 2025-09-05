#include <Arduino.h>
#include "UartTron.h"

//----------------------------------------------------------------------------
// Variáveis Globais
//----------------------------------------------------------------------------
uint8_t uartRxBuffer[MAX_PACKET_SIZE];
uint8_t uartRxIndex = 0;
uint32_t uartTimeoutRx = 0;
size_t uartRxSize = 0;
UartReceivedCallback uartReceivedCallback = nullptr;

void uartTronInit(){
    Serial1.begin(115200, SERIAL_8N1, UART_RX_PIN, UART_TX_PIN);
    Serial1.println("UART Tron initialized");
}

void uartTronTask(void) {
    uint8_t data;
    while (Serial1.available()) {
        data = Serial1.read();
        Serial.print("Byte recebido: 0x"); Serial.println(data, HEX);
        if (uartRxIndex == 0) {
            if (data == START_BYTE) {
                uartRxBuffer[uartRxIndex++] = START_BYTE;
                uartRxSize = 1;
                Serial.println("Start byte detectado");
            }
        } else {
            uartRxBuffer[uartRxIndex++] = data;
            uartRxSize = uartRxIndex;
            if (uartRxIndex >= MAX_PACKET_SIZE) {
                Serial.println("Erro: Estouro de buffer");
                uartRxIndex = 0;
                break;
            }
            uartTimeoutRx = millis();
        }
    }
    if ((uartRxIndex >= 3) && (millis() > (uartTimeoutRx + TEMPO_MAX_RECEVING))) {
        uint8_t expectedSize = uartRxBuffer[2] + 1; // Tamanho do payload + 1 (CRC)
        Serial.print("Tamanho esperado: "); Serial.println(expectedSize);
        if (uartRxIndex >= expectedSize) {
            Serial.print("Pacote recebido, tamanho: "); Serial.println(uartRxIndex);
            uint8_t crcCalc = uartTronCrcSlow(uartRxBuffer, uartRxIndex - 1);
            Serial.print("CRC calculado: 0x"); Serial.println(crcCalc, HEX);
            Serial.print("CRC recebido: 0x"); Serial.println(uartRxBuffer[uartRxIndex - 1], HEX);
            if (crcCalc == uartRxBuffer[uartRxIndex - 1]) {
                Serial.println("CRC válido, chamando callback");
                if (uartReceivedCallback != nullptr) {
                    uartReceivedCallback(uartRxBuffer, uartRxIndex);
                }
            } else {
                Serial.println("Erro: CRC inválido");
            }
            uartRxIndex = 0;
        } else {
            Serial.println("Erro: Pacote incompleto, aguardando mais bytes");
        }
    } else if ((uartRxIndex > 0) && (millis() > (uartTimeoutRx + TEMPO_MAX_RECEVING))) {
        Serial.println("Erro: Timeout com pacote parcial, tamanho: " + String(uartRxIndex));
        uartRxIndex = 0;
    }
}

void setUartReceivedCallback(UartReceivedCallback callback) {
    uartReceivedCallback = callback;
}

uint8_t uartTronCrcSlow(uint8_t message[], int nBytes) {
    const uint8_t POLYNOMIAL = 0xD8;
    uint8_t crc = 0;
    for (int byte = 0; byte < nBytes; ++byte) {
        crc ^= message[byte];
        for (uint8_t bit = 0; bit < 8; ++bit) {
            crc = (crc & 0x80) ? ((crc << 1) ^ POLYNOMIAL) : (crc << 1);
        }
    }
    return crc;
}

void uartTronSendBuffer(uint8_t *buffer, uint8_t size) {
    Serial1.write(buffer, size);
    Serial1.flush();
}