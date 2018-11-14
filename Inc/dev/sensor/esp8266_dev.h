/*
 * esp8266_dev.h
 *
 *  Created on: 2018. 10. 31.
 *      Author: kdj6724
 */
#include "stm32f1xx_hal.h"
#include "dev/data/queue.h"

#ifndef DEV_SENSOR_ESP8266_DEV_H_
#define DEV_SENSOR_ESP8266_DEV_H_

#ifdef __cplusplus
extern "C" {
#endif
#define ESP8266_MACADDR_LENGTH  17
#define ESP8266_SCAN_RESET_KEY  "AT+CWLAP"
#define ESP8266_SCAN_INFO_KEY "+CWLAP:("
Queue esp8266MessageQueue_;

enum esp8266_mode {
	esp8266_STATION = 0,
	esp8266_AP,
	esp8266_DUAL,
};

typedef struct esp8266ScanInfo {
  char wps;
  char* ssid;
  int rssi;
  char* mac;
  char channel;
} esp8266ScanInfo;


#define ESP8266_TEST_CONNECT  'c'
#define ESP8266_TEST_SCAN     's'
#define ESP8266_TEST_GETIP    'i'

void esp8266_usart_rx_callback(USART_TypeDef* uart);
void esp8266_print_test_menu();
int esp8266_select_test_menu(char index);
int esp8266_init(USART_TypeDef* uart);
int esp8266_setmode(int mode);
int esp8266_set_ssid(char* ssid);
int esp8266_set_pwd(char* pwd);
int esp8266_connect();
int esp8266_scan();
int esp8266_get_ip_address();
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
