/*
 * uart_string.h
 *
 *  Created on: 2018. 11. 6.
 *      Author: kdj6724
 */

#ifndef DEV_SERIAL_UART_STRING_H_
#define DEV_SERIAL_UART_STRING_H_
#include "stm32f1xx_hal.h"
#include "../data/queue.h"
#define UARTSTR_BYTE_BUFFLEN  128
typedef struct UartstrQueue {
  UART_HandleTypeDef* uart;
  Queue queue;
  char* byteBuff;
  int cnt;
}UartstrQueue;
// 주의 딱한번만 호출되도록
int uartstr_init(UartstrQueue* uart);
void uartstr_get_byte(UartstrQueue* uart, char val);
int uartstr_receive_string(UartstrQueue* uart, char* data, int reqlen);
int uartstr_send_string(UartstrQueue* uart, char* data, int reqlen);

#endif /* DEV_SERIAL_UART_STRING_H_ */
