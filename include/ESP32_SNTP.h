//////////////////////////////////////////////////////////////////
// ESP32 - SNTP
//
// USES ESP32 SNTP (THAT USES ESP32 LWIP) TO GET NTP AND MAINTAIN
// SYSTEM TIME BASED ON THAY
//
// REFERENCE:
//  (1) https://github.com/espressif/esp-idf/blob/master/examples/protocols/sntp/main/sntp_example_main.c
//
// MAY 03, 2018
//
// ANKIT BHATNAGAR
// ANKIT.BHATNAGARINDIA@GMAIL.COM
//////////////////////////////////////////////////////////////////

#ifndef _ESP32_SNTP_
#define _ESP32_SNTP_

#include "esp_system.h"
#include "esp_err.h"
#include "esp_log.h"

#define ESP32_SNTP_TAG         "ESP32:SNTP"

void ESP32_WS2812B_SNTP_SetDebug(bool enable);
void ESP32_SNTP_Initialize(void);

#endif