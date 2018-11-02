/*
 * esp8266_dev.h
 *
 *  Created on: 2018. 10. 31.
 *      Author: kdj6724
 */
#include "stm32f1xx_hal.h"

#ifndef DEV_SENSOR_ESP8266_DEV_H_
#define DEV_SENSOR_ESP8266_DEV_H_

#ifdef __cplusplus
extern "C" {
#endif
enum esp8266_mode {
	esp8266_STATION = 0,
	esp8266_AP,
	esp8266_DUAL,
};

int esp8266_init(USART_TypeDef* uart);
int esp8266_setmode(int mode);
int esp8266_set_ssid(char* ssid);
int esp8266_set_pwd(char* pwd);
int esp8266_connect();
int esp8266_scan();
int esp8266_disconnect();
int esp8266_set_mac_address();
int esp8266_set_ip_address();
int esp8266_AP_get_station_list();
int esp8266_AP_DHCP_enable();
int esp8266_AP_set_mac_address();

#ifdef __cplusplus
}
#endif

#endif /* DEV_SENSOR_ESP8266_DEV_H_ */
