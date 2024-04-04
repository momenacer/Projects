/*
 * NTP.h
 *
 *  Created on: 21 mars 2023
 *      Author: Rania
 */

#ifndef MAIN_NTP_H_
#define MAIN_NTP_H_







//SNTP
//#include <string.h>
#include "esp_event.h"
#include "nvs_flash.h"
//#include "lwip/err.h"
//#include "lwip/sys.h"
#include "freertos/event_groups.h"
//#include "time.h"
//#include "sys/time.h"
#include "esp_wifi.h"
#include "esp_sntp.h"
#include "esp_log.h"		//  for debug fct :ESP_LOGI/W/E/D/V( )





//NTP
#define EXAMPLE_ESP_WIFI_SSID      "57eeb3b8"
#define EXAMPLE_ESP_WIFI_PASS      "123456788"

#define EXAMPLE_ESP_MAXIMUM_RETRY  CONFIG_ESP_MAXIMUM_RETRY

#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT      BIT1



 void initialize_sntp(void);
 void initialize_rtc(void);
 void wifi_init_sta(void);
 void wait_for_time(void);
 void event_handler(void* arg, esp_event_base_t event_base,int32_t event_id, void* event_data);
 void got_ip_event_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data);

 void update_time_task(void *pvParameters);
 void display_time_task(void *pvParameters);



#endif /* MAIN_NTP_H_ */
