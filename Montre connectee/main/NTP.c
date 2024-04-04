/*
 * NTP.c
 *
 *  Created on: 21 mars 2024
 *
 */

#include "NTP.h"


 int s_retry_num = 0;

//Time
time_t now;
struct tm timeinfo;
int heure, minute, mois, jour, annee;

 const char *TAG = "wifi station";
 EventGroupHandle_t s_wifi_event_group;


void wifi_init_sta(void)
{
    s_wifi_event_group = xEventGroupCreate();
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    esp_event_handler_instance_t instance_any_id;
    esp_event_handler_instance_t instance_got_ip;
    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
                                                        ESP_EVENT_ANY_ID,
                                                        &event_handler,
                                                        NULL,
                                                        &instance_any_id));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT,
                                                        IP_EVENT_STA_GOT_IP,
                                                        &event_handler,
                                                        NULL,
                                                        &instance_got_ip));

    wifi_config_t wifi_config = {
        .sta = {
            .ssid = EXAMPLE_ESP_WIFI_SSID,
            .password = EXAMPLE_ESP_WIFI_PASS,
        },
    };
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());


    EventBits_t bits = xEventGroupWaitBits(s_wifi_event_group,
            WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
            pdFALSE,
            pdFALSE,
            portMAX_DELAY);

    if (bits & WIFI_CONNECTED_BIT) {
        ESP_LOGI(TAG, "connected to ap SSID:%s password:%s",
                 EXAMPLE_ESP_WIFI_SSID, EXAMPLE_ESP_WIFI_PASS);
    } else if (bits & WIFI_FAIL_BIT) {
        ESP_LOGI(TAG, "Failed to connect to SSID:%s, password:%s",
                 EXAMPLE_ESP_WIFI_SSID, EXAMPLE_ESP_WIFI_PASS);
    } else {
        ESP_LOGE(TAG, "UNEXPECTED EVENT");
    }
}

 void event_handler(void* arg, esp_event_base_t event_base,
                                int32_t event_id, void* event_data)
{
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        esp_wifi_connect();
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        if (s_retry_num < EXAMPLE_ESP_MAXIMUM_RETRY) {
            esp_wifi_connect();
            s_retry_num++;
            ESP_LOGI(TAG, "retry to connect to the AP");
        } else {
            xEventGroupSetBits(s_wifi_event_group, WIFI_FAIL_BIT);
        }
        ESP_LOGI(TAG,"connect to the AP fail");
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
        ESP_LOGI(TAG, "got ip:" IPSTR, IP2STR(&event->ip_info.ip));
        s_retry_num = 0;
        xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);

        // Initialize SNTP after Wi-Fi is connected
        initialize_sntp();
        wait_for_time();
    }
}

 void initialize_sntp(void)
{
    ESP_LOGI(TAG, "Initializing SNTP");
    sntp_setoperatingmode(SNTP_OPMODE_POLL);
    sntp_setservername(0, "pool.ntp.org");
    sntp_init();
}

 void wait_for_time(void)
{
    time_t now = 0;
    struct tm timeinfo = { 0 };
    int retry = 0;
    const int retry_count = 10;

    // Wait for RTC time to be set
    while (timeinfo.tm_year < (2016 - 1900) && ++retry < retry_count) {
        ESP_LOGI(TAG, "Waiting for RTC time to be set... (%d/%d)", retry, retry_count);
        vTaskDelay(pdMS_TO_TICKS(2000));
        time(&now);
        localtime_r(&now, &timeinfo);
    }

    // Print current time
    if (timeinfo.tm_year >= (2016 - 1900)) {
        ESP_LOGI(TAG, "RTC time is set.");
        char strftime_buf[64];
        strftime(strftime_buf, sizeof(strftime_buf), "%A %d %B %Y %Hh%M", &timeinfo);
        ESP_LOGI(TAG, "Current time: %s", strftime_buf);
    } else {
        ESP_LOGE(TAG, "Failed to obtain RTC time.");
    }
}

//////////////////
// Callback pour l'événement IP_EVENT_STA_GOT_IP
 void got_ip_event_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data) {
    // Initialize SNTP après que la connexion Wi-Fi soit établie
    initialize_sntp();
}

 void initialize_rtc(void)
{
    time_t now;
    struct tm timeinfo;
    time(&now);
    localtime_r(&now, &timeinfo);
    struct timeval tv = {
        .tv_sec = mktime(&timeinfo),
        .tv_usec = 0
    };
    settimeofday(&tv, NULL);
}



// Task to update time every minute
 void update_time_task(void *pvParameters)
{
    while (1)
    {
        // Get current time
        time(&now);
        localtime_r(&now, &timeinfo);

        // Adjust for France timezone
        timeinfo.tm_hour += 2; // Add 1 hour for France timezone
        mktime(&timeinfo); // Re-normalize time after adjustment

        // Delay for 1 minute
        vTaskDelay(pdMS_TO_TICKS(60000));
    }
}



////////////////////////////////////////////////
// Task to display time every minute
 void display_time_task(void *pvParameters)
{
    // Wait until valid time is obtained from NTP
    wait_for_time();

    for (;;) {

        time(&now);
        localtime_r(&now, &timeinfo);

        // Adjust for France timezone
        timeinfo.tm_hour += 2; // Add 1 hour for France timezone
        mktime(&timeinfo); // Re-normalize time after adjustment

        now = mktime(&timeinfo); // Update now with adjusted time

        // Extracting individual values
        heure = timeinfo.tm_hour;
        minute = timeinfo.tm_min;
        mois = timeinfo.tm_mon + 1; // tm_mon is 0-indexed
        jour = timeinfo.tm_mday;
        annee = timeinfo.tm_year + 1900; // tm_year represents years since 1900

        // Print current time
        char strftime_buf[64];
        strftime(strftime_buf, sizeof(strftime_buf), "%A %d %B %Y %H:%M:%S", &timeinfo);
        printf("%s\n", strftime_buf); // Print the date directly to the terminal

        // Print individual values
        printf("Heure: %d\n", heure);
        printf("Minute: %d\n", minute);
        printf("Mois: %d\n", mois);
        printf("Jour: %d\n", jour);
        printf("Annee: %d\n", annee);

        vTaskDelay(pdMS_TO_TICKS(60000)); // Delay for 1 minute
    }
}


