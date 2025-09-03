#include <Arduino.h>
#include "UartTron.h"

void uartTronInit(){
    // Inicializa serial 1 nos pinos 18 (RX) e 17 (TX) com baud rate de 115200
    Serial1.begin(115200, SERIAL_8N1, UART_RX_PIN, UART_TX_PIN);
    Serial1.println("UART Tron initialized");
}

void uartTronTask() {
    // Check if data is available to read
    if (Serial1.available()) {
        String data = Serial1.readStringUntil('\n'); // Read until newline
        Serial.println("Received: " + data); // Print received data to Serial
    }
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