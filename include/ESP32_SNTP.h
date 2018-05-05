//////////////////////////////////////////////////////////////////
// ESP32 - SNTP
//
// USES ESP32 SNTP (THAT USES ESP32 LWIP) TO GET NTP AND MAINTAIN
// SYSTEM TIME BASED ON THAY
//  
// ESP32 SNTP ONLY SUPPORTS 1 NTP SERVER
//
// REFERENCE:
//  (1) https://github.com/espressif/esp-idf/blob/master/examples/protocols/sntp/main/sntp_example_main.c
//
//  (2) TimeZone String List
//      https://github.com/nayarsystems/posix_tz_db/blob/master/zones.csv
//
// MAY 03, 2018
//
// ANKIT BHATNAGAR
// ANKIT.BHATNAGARINDIA@GMAIL.COM
/////////////////////////////////////////////////////////////////

#ifndef _ESP32_SNTP_
#define _ESP32_SNTP_

#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "esp_system.h"
#include "esp_err.h"
#include "esp_log.h"

#define ESP32_SNTP_TAG                      "ESP32:SNTP"

#define ESP32_SNTP_GET_TIME_RETRY_COUNT     (10)
#define ESP32_SNTP_GET_TIME_RETRY_DELAY_MS  (1500)

void ESP32_WS2812B_SNTP_SetDebug(bool enable);

void ESP32_SNTP_Initialize(char* ntp_server);
void ESP32_SNTP_SetTimeZone(char* tz_string);

bool ESP32_SNTP_GetTime(struct tm* retval);
bool ESP32_SNTP_GetTimeString(char* retval, uint8_t retval_size, char* time_fmt);

#endif