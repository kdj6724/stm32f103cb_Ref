/*
 * esp8266_dev.c
 *
 *  Created on: 2018. 10. 31.
 *      Author: kdj6724
 */
#include <string.h>
#include "esp8266_dev.h"

#define ESP8266_ATCMD_PREFIX "AT+"
UART_HandleTypeDef* esp8266UART_ = NULL;
uint8_t rxbuf_[2];
char ssid_[64];
char pwd_[64];

int esp8266_send_uart_cmd(UART_HandleTypeDef* uart, uint8_t* data, int len) {
	HAL_StatusTypeDef status;
	if (uart == NULL) {
		printf("[esp8266-dev] uart is NULL(%d)\r\n", __LINE__);
		return -1;
	}
	printf("[esp8266-dev] send : %s\r\n", data);
	status = HAL_UART_Transmit(uart, (uint8_t*)data, len, 1000);
	return (status == HAL_OK ? len : 0);
}

void esp8266_init(UART_HandleTypeDef* uart) {
	if (uart != NULL)
		esp8266UART_ = uart;
	memset(ssid_, 0, sizeof(ssid_));
	memset(pwd_, 0, sizeof(pwd_));
}

// AP mode, station mode
int esp8266_setmode(int mode) {
	uint8_t cmd[128];

	if (ssid_ == "")
		return -1;
	memset(cmd, 0, sizeof(cmd));
	sprintf((char*)cmd, "%sCWMODE=%d\r\n",ESP8266_ATCMD_PREFIX, mode);
	return esp8266_send_uart_cmd(esp8266UART_, cmd, strlen((char*)cmd));
}

int esp8266_set_ssid(char* ssid) {
	if (ssid == NULL)
		return -1;
	return strcpy(ssid_, ssid);
}

int esp8266_set_pwd(char* pwd) {
	if (pwd == NULL) {
		return strcpy(pwd_, "None");
	}
	return strcpy(pwd_, pwd);
}
// station mode 에서만 동작
// 128 byte넘지 않게 주의
int esp8266_connect() {
	uint8_t cmd[128];

	if (ssid_ == "")
		return -1;
	memset(cmd, 0, sizeof(cmd));
	sprintf((char*)cmd, "%sCWJAP=\"%s\",\"%s\"\r\n",ESP8266_ATCMD_PREFIX, ssid_, pwd_);
	return esp8266_send_uart_cmd(esp8266UART_, cmd, strlen((char*)cmd));
}

// station mode 에서만 동작
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

int esp8266_set_mac_address() {
	return 0;
}
