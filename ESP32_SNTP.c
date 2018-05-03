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
// MAY 03, 2018
//
// ANKIT BHATNAGAR
// ANKIT.BHATNAGARINDIA@GMAIL.COM
//////////////////////////////////////////////////////////////////

#include <string.h>
#include <time.h>
#include <sys/time.h>
#include "lwip/err.h"
#include "apps/sntp/sntp.h"
#include "ESP32_SNTP.h"


//INTERNAL VARIABLES
static bool s_debug;

//NTP  RELATED
char* s_ntp_server_name;

//INTERNAL FUNCTIONS

void ESP32_WS2812B_SNTP_SetDebug(bool enable)
{
	//SET MODULE DEBUG

	s_debug = enable;
}

void ESP32_SNTP_Initialize(char* ntp_server)
{
    //INITIALIZE ESP32 SNTP

    sntp_setoperatingmode(SNTP_OPMODE_POLL);
    sntp_setservername(0, ntp_server);
    s_ntp_server_name = ntp_server;
    sntp_init();

    ets_printf(ESP32_SNTP_TAG" : Initialized\n");
    ets_printf(ESP32_SNTP_TAG" : NTP Server = %s\n", s_ntp_server_name);
}