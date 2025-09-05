#ifndef UART_TRON_H
#define UART_TRON_H

#define UART_TX_PIN 17
#define UART_RX_PIN 18

//----------------------------------------------------------------------------
// Tipo do Callback
//----------------------------------------------------------------------------
typedef void (*UartReceivedCallback)(uint8_t* packet, uint8_t size);

//----------------------------------------------------------------------------
#define TEMPO_MAX_RECEVING 200  // Timeout de recepção em ms
#define START_BYTE 0x7E
#define CMD_REFRESH 'R'
#define CMD_STATUS 'S'
#define MAX_PACKET_SIZE 64  // Tamanho máximo esperado para um pacote

#define REFRESH_PAYLOAD_SIZE 30 //era 31, diminuir para 30 (retirar o status on/off)
#define STATUS_PAYLOAD_SIZE 25 //era 24, aumentar pra 25 (adicionar o status on/off)
//----------------------------------------------------------------------------

void uartTronInit();
void uartTronTask();

uint8_t uartTronCrcSlow(uint8_t message[], int nBytes);
void uartTronSendBuffer(uint8_t *buffer, uint8_t size);
void setUartReceivedCallback(UartReceivedCallback callback);

#endif