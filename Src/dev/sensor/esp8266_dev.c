/*
 * esp8266_dev.c
 *
 *  Created on: 2018. 10. 31.
 *      Author: kdj6724
 */
#include <string.h>
#include "esp8266_dev.h"

#define ESP8266_ATCMD_PREFIX "AT+"
#define ESP8266_UART_RXLEN  32

USART_TypeDef* esp8266UART_ = NULL;
uint8_t rxbuf_[ESP8266_UART_RXLEN];
char ssid_[64];
char pwd_[64];

void USART_Rx_Callback(USART_TypeDef* uart) {
  static uint16_t cnt = 0;
  char t;
  static char skipFirstCR = 0;
  int i = 0;
#if 1
  if(LL_USART_IsActiveFlag_RXNE(uart)) {
    t = LL_USART_ReceiveData8(uart);
    if (skipFirstCR == 0) {
      if (t == '\r')
        skipFirstCR = 1;
      return;
    }

    if((t!='\r') && (cnt < (ESP8266_UART_RXLEN-1))) {
      rxbuf_[cnt] = t;
      cnt++;
    }
    else {
      printf("[esp8266-dev] received : %s\r\n", rxbuf_);
      memset(rxbuf_, 0, sizeof(rxbuf_));
      skipFirstCR = 0;
      cnt = 0;
    }
  }
#else
  if(LL_USART_IsActiveFlag_RXNE(uart)) {
      t = LL_USART_ReceiveData8(uart);

      if(t == 0 || cnt < (ESP8266_UART_RXLEN-1)) {
        rxbuf_[cnt] = t;
        cnt++;
      }
      else {
        printf("[esp8266-dev] received : ");
        for (i=0; i<ESP8266_UART_RXLEN; i++) {
          printf("0x%x ", rxbuf_[i]);
        }
        printf("\r\n");
        //printf("[esp8266-dev] received : %s\r\n", rxbuf_);
        memset(rxbuf_, 0, sizeof(rxbuf_));
        skipFirstCR = 0;
        cnt = 0;
      }
    }
#endif
}

int esp8266_uart_send(USART_TypeDef* uart, uint8_t *Buffer, int reqLen){
  int len = 0;

  if (uart == NULL) {
    printf("[esp8266-dev] uart is NULL(%d)\r\n", __LINE__);
    return -1;
  }

  if (reqLen == 0)
    return 0;

  while(*Buffer){
    while(!LL_USART_IsActiveFlag_TXE(uart)) {
      HAL_Delay(10);
    };
    LL_USART_TransmitData8(uart,*Buffer++);
    len++;
    reqLen--;
    if (reqLen == 0)
      break;
  }
  return len;
}

int esp8266_send_uart_cmd(USART_TypeDef* uart, uint8_t* data, int len) {
	if (uart == NULL) {
		printf("[esp8266-dev] uart is NULL(%d)\r\n", __LINE__);
		return -1;
	}
	printf("[esp8266-dev] send : %s\r\n", data);
	esp8266_uart_send(uart, data, len);
	return 0;
}

int esp8266_init(USART_TypeDef* uart) {
	if (uart == NULL) {
		printf("[esp8266-dev] uart is NULL(%d)\r\n", __LINE__);
		return -1;
	}
	//LL_USART_Enable(uart);
	LL_USART_EnableIT_RXNE(uart);
	esp8266UART_ = uart;
	memset(ssid_, 0, sizeof(ssid_));
	memset(pwd_, 0, sizeof(pwd_));
	esp8266_send_uart_cmd(esp8266UART_, "ATE\r\n", 5);

	return 0;
}

// AP mode, station mode
int esp8266_setmode(int mode) {
	uint8_t cmd[128];

	if (ssid_ == NULL)
		return -1;
	memset(cmd, 0, sizeof(cmd));
	sprintf((char*)cmd, "%sCWMODE=%d\r\n",ESP8266_ATCMD_PREFIX, mode);
	return esp8266_send_uart_cmd(esp8266UART_, cmd, strlen((char*)cmd));
}

int esp8266_set_ssid(char* ssid) {
	if (ssid == NULL)
		return -1;
	strcpy(ssid_, ssid);
	return 0;
}

int esp8266_set_pwd(char* pwd) {
	if (pwd == NULL) {
		strcpy(pwd_, "None");
		return 0;
	}
	strcpy(pwd_, pwd);
	return 0;
}
// station mode ������ ����
// 128 byte���� �ʰ� ����
int esp8266_connect() {
	uint8_t cmd[128];

	if (ssid_ == NULL)
		return -1;
	memset(cmd, 0, sizeof(cmd));
	sprintf((char*)cmd, "%sCWJAP=\"%s\",\"%s\"\r\n",ESP8266_ATCMD_PREFIX, ssid_, pwd_);
	return esp8266_send_uart_cmd(esp8266UART_, cmd, strlen((char*)cmd));
}

// station mode ������ ����
int esp8266_scan() {

	return 0;
}

int esp8266_disconnect() {
	return 0;
}

int esp8266_set_mac_address() {
	return 0;
}

int esp8266_set_ip_address() {
	return 0;
}

int esp8266_AP_get_station_list() {
	return 0;
}

int esp8266_AP_DHCP_enable() {
	return 0;
}

int esp8266_AP_set_mac_address() {
	return 0;
}

