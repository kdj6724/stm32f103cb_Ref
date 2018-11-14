/*
 * uart_string.c
 *
 *  Created on: 2018. 11. 6.
 *      Author: kdj6724
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dev/serial/uart_string.h"

// 주의 딱한번만 호출되도록
int uartstr_init(UartstrQueue* uart) {
  if (uart == NULL)
    return -1;
  uart->byteBuff = malloc(UARTSTR_BYTE_BUFFLEN);
  memset((char*)uart->byteBuff, 0, UARTSTR_BYTE_BUFFLEN);
  uart->cnt = 0;
  return 0;
}

int uartstr_clear(UartstrQueue* uart) {
  if (uart == NULL)
      return -1;
  free(uart->byteBuff);
  return 0;
}

void uartstr_get_byte(UartstrQueue* uart, char val) {
  if (val == '\r' || val == '\n' || uart->cnt >= UARTSTR_BYTE_BUFFLEN-1) {
    enqueue(&(uart->queue), uart->byteBuff, uart->cnt);
    memset((char*)uart->byteBuff, 0, UARTSTR_BYTE_BUFFLEN);
    uart->cnt = 0;
  } else {
    *(uart->byteBuff + uart->cnt) = val;
    uart->cnt++;
  }
}

int uartstr_receive_string(UartstrQueue* uart, char* data, int reqlen) {
  if (data == NULL || reqlen <= 0)
    return 0;
  memset(data, 0, reqlen);
  // 예외처리 필요 위험해보임
  return dequeue(&(uart->queue), data);
}

int uartstr_send_string(UartstrQueue* uart, char* data, int reqlen) {
  if (data == NULL || reqlen <= 0)
    return 0;
  return HAL_UART_Transmit(uart->uart, (uint8_t*)data, reqlen, 1000);
}
