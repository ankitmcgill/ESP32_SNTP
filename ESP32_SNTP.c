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

#include <string.h>
#include "lwip/err.h"
#include "apps/sntp/sntp.h"
#include "ESP32_SNTP.h"
#include "ESP32_UTIL.h"

//INTERNAL VARIABLES
static bool s_debug;

//NTP  RELATED
char* s_ntp_server_name;

//INTERNAL FUNCTIONS

void ESP32_SNTP_SetDebug(bool enable)
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

void ESP32_SNTP_SetTimeZone(char* tz_string)
{
    //SET MODULE TIMEZONE USING LINUX STANDARD 
    //TIMEZONE STRING
    //http://www.gnu.org/software/libc/manual/html_node/TZ-Variable.html
    //https://github.com/nayarsystems/posix_tz_db/blob/master/zones.csv

    setenv("TZ", tz_string, true);
    tzset();

    if(s_debug)
    {
        ets_printf(ESP32_SNTP_TAG" : Timezone set to %s\n", tz_string);
    }
}

bool ESP32_SNTP_GetTime(struct tm* retval)
{
    //RETURN CURRENT TIME

    time_t now = 0;
    struct tm timeinfo = {0};
    uint8_t retry = 0;
    
    while(timeinfo.tm_year < (2018 - 1900) &&
            retry++ < ESP32_SNTP_GET_TIME_RETRY_COUNT)
    {
        ESP32_UTIL_DelayBlockingMs(ESP32_SNTP_GET_TIME_RETRY_DELAY_MS);
        if(s_debug)
        {
            ets_printf(ESP32_SNTP_TAG" : getting time attempt %u\n", retry);
        }
        time(&now);
        localtime_r(&now, &timeinfo);
    }

    if(retry == ESP32_SNTP_GET_TIME_RETRY_COUNT)
    {
        //TIME GETTING ERROR
        if(s_debug)
        {
            ets_printf(ESP32_SNTP_TAG" : error ! all attempts finished\n", retry);
        }
        return false;
    }

    //GOT THE TIME
    //COPY THE VALUES
    memcpy((void*)retval, (void*)&timeinfo, sizeof(struct tm));
    return true;
}

bool ESP32_SNTP_GetTimeString(char* retval, uint8_t retval_size, char* time_fmt)
{
    //RETURN CURRENT TIME AS STRING

    struct tm current_time;

    if(!ESP32_SNTP_GetTime(&current_time))
    {
        if(s_debug)
        {
            ets_printf(ESP32_SNTP_TAG" : error ! could not get current time string\n");
        }
        return false;
    }

    //GOT THE TIME
    strftime(retval, retval_size, time_fmt, &current_time);
    return true;
}