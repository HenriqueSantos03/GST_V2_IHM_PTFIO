#include <Arduino.h>
#include "UartTron.h"

//----------------------------------------------------------------------------
// Variáveis Globais
//----------------------------------------------------------------------------
uint8_t uartRxBuffer[MAX_PACKET_SIZE];
uint8_t uartRxIndex = 0;
uint32_t uartTimeoutRx = 0;
size_t uartRxSize = 0;
UartReceivedCallback uartReceivedCallback = nullptr; // Callback para pacotes válidos

void uartTronInit(){
    // Inicializa serial 1 nos pinos 18 (RX) e 17 (TX) com baud rate de 115200
    Serial1.begin(115200, SERIAL_8N1, UART_RX_PIN, UART_TX_PIN);
    Serial1.println("UART Tron initialized");
}

void uartTronTask(void) {
    uint8_t data;

    // Recepção de dados
    while (Serial1.available()) {
        data = Serial1.read();
        
        // Aguardando início do pacote
        if (uartRxIndex == 0) {
            if (data == START_BYTE) {
                // Salva o start byte
                uartRxBuffer[uartRxIndex++] = START_BYTE;
                uartRxSize = 1;
            }
        }
        else {  // Já iniciou a captura de um pacote
            // Armazena o dado
            uartRxBuffer[uartRxIndex++] = data;
            uartRxSize = uartRxIndex;
            
            // Valida a quantidade máxima
            if (uartRxIndex >= MAX_PACKET_SIZE) {
                // Cancela recepção - estouro do buffer
                uartRxIndex = 0;
                break;
            }
            
            // Atualiza timeout
            uartTimeoutRx = millis();
        }
    }

    // Timeout - finalização da recepção do pacote
    if ((uartRxIndex > 0) && (millis() > (uartTimeoutRx + TEMPO_MAX_RECEVING))) {
        // Tamanho mínimo de um pacote (start + cmd + size + payload + crc)
        if (uartRxIndex >= 4) {
            // Valida o CRC
            uint8_t crcCalc = uartTronCrcSlow(uartRxBuffer, uartRxIndex - 1);
            if (crcCalc == uartRxBuffer[uartRxIndex - 1]) {
                // Chama o callback se estiver configurado
                if (uartReceivedCallback != nullptr) {
                    uartReceivedCallback(uartRxBuffer, uartRxIndex);
                }
            }
        }
        // Libera para próxima recepção
        uartRxIndex = 0;
    }
}

void setUartReceivedCallback(UartReceivedCallback callback) {
    uartReceivedCallback = callback;
}

// Cálculo CRC
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