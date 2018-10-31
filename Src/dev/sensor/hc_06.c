// hc_06.c
// kdj6724@naver.com
// 2018-10-26
#include <string.h>
#include "hc_06.h"

UART_HandleTypeDef* hc06UART_ = NULL;
uint8_t rxbuf_[2];

int hc06_send_atcmd(uint8_t* data, int len) {
	HAL_StatusTypeDef status;
  if (hc06UART_ == NULL) {
    printf("[hc-06] uart is NULL(%d)\r\n", __LINE__);
    return -1;
  }
  printf("[hc-06] send : %s\r\n", data);
	status = HAL_UART_Transmit(hc06UART_, (uint8_t*)data, len, 1000);
	return (status == HAL_OK ? len : 0);
}

int hc06_init(UART_HandleTypeDef* uart) {
  hc06UART_ = uart;
  HAL_UART_Receive_IT(uart, rxbuf_, 1);
  //hc06_set_baudrate(HC06_BAUD_9600);
  hc06_set_bluetoothname("co-m", 4);
  return 0;
}

int hc06_receive_byte(void) {
  int res = HC06_CMD0;

  if (hc06UART_ == NULL) {
    printf("[hc-06] uart is NULL(%d)\r\n", __LINE__);
    return -1;
  }
  if (rxbuf_[0] == HC06_UART_ENDBYTE) {
    res = HC06_CMD1;
  } else {
    printf("[hc-06] receive : 0x%x(%c)\r\n", rxbuf_[0], rxbuf_[0]);
  }
  memset(rxbuf_, 0, sizeof(rxbuf_));
  HAL_UART_Receive_IT(hc06UART_, rxbuf_, 1);
  return res;
}

int hc06_set_baudrate(int val) {
  uint8_t cmd[32];
  memset(cmd, 0, sizeof(cmd));
  sprintf((char*)cmd, "%sBAUD%d",HC06_ATCMD_PREFIX, val);
  return hc06_send_atcmd(cmd, strlen((char*)cmd));
}

int hc06_set_bluetoothname(char* name, int len) {
  uint8_t cmd[32];
  memset(cmd, 0, sizeof(cmd));
  sprintf((char*)cmd, "%sNAME%s",HC06_ATCMD_PREFIX, name);
  return hc06_send_atcmd(cmd, strlen((char*)cmd));
}

int hc06_set_pin(char* pin, int len) {
  uint8_t cmd[32];
  memset(cmd, 0, sizeof(cmd));
  sprintf((char*)cmd, "%sPIN%s",HC06_ATCMD_PREFIX, pin);
  return hc06_send_atcmd(cmd, strlen((char*)cmd));
}

