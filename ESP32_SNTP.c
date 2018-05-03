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


#include "ESP32_SNTP.h"


//INTERNAL VARIABLES
static bool s_debug;

//INTERNAL FUNCTIONS

void ESP32_WS2812B_SNTP_SetDebug(bool enable)
{
	//SET MODULE DEBUG

	s_debug = enable;
}

void ESP32_SNTP_Initialize(void)
{
    //INITIALIZE ESP32 SNTP

    ets_printf(ESP32_SNTP_TAG" : Initialized\n");
}