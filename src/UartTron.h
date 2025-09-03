#ifndef UART_TRON_H
#define UART_TRON_H

#define UART_TX_PIN 17
#define UART_RX_PIN 18
//----------------------------------------------------------------------
#define TEMPO_MAX_RECEVING      200     // Timeout de recepção em ms
#define START_BYTE 0x7E
#define CMD_REFRESH 'R'
#define CMD_STATUS 'S'
#define MAX_PACKET_SIZE 64  // Tamanho máximo esperado para um pacote

#define REFRESH_PAYLOAD_SIZE 31
#define STATUS_PAYLOAD_SIZE 24
//----------------------------------------------------------------------
void uartTronInit();
void uartTronTask();

uint8_t uartTronCrcSlow(uint8_t message[], int nBytes);
void uartTronSendBuffer(uint8_t *buffer, uint8_t size);

#endif