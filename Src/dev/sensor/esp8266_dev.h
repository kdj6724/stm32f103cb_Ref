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
#ifdef __cplusplus
}
#endif

#endif /* DEV_SENSOR_ESP8266_DEV_H_ */
