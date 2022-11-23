
#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/ledc.h"
#include "esp_log.h"
#include "sdkconfig.h"
#include "nvs_flash.h"
#include "lwip/err.h"
#include "lwip/sys.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "lwip/err.h"
#include "lwip/sys.h"
#include "esp_event.h"
#include "esp_smartconfig.h"




static const char *TAG = "wifi softAP";

void output_pwm(uint8_t gpio_num, uint8_t duty){

    printf("GPIO is %d, Duty is %d \n", gpio_num, duty);
    ledc_timer_config_t ledc_timer = {
        .duty_resolution = LEDC_TIMER_8_BIT,
        .freq_hz = 1000,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .timer_num = LEDC_TIMER_0,
        .clk_cfg = LEDC_AUTO_CLK,
    };
    ledc_timer_config(&ledc_timer);             //配置timer

    ledc_channel_config_t ledc_channel ={
            .channel    = LEDC_CHANNEL_0,
            .duty       = 0,
            .gpio_num   = gpio_num,
            .speed_mode = LEDC_LOW_SPEED_MODE,
            .hpoint     = 0,
            .timer_sel  = LEDC_TIMER_0
        };
    ledc_channel_config(&ledc_channel);         //配置通道
    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, duty);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
}
static void wifi_event_handler(void* arg, esp_event_base_t event_base,
                                    int32_t event_id, void* event_data)
{
    if (event_id == WIFI_EVENT_AP_STACONNECTED) {
        wifi_event_ap_staconnected_t* event = (wifi_event_ap_staconnected_t*) event_data;
        ESP_LOGI(TAG, "station "MACSTR" join, AID=%d",
                 MAC2STR(event->mac), event->aid);
    } else if (event_id == WIFI_EVENT_AP_STADISCONNECTED) {
        wifi_event_ap_stadisconnected_t* event = (wifi_event_ap_stadisconnected_t*) event_data;
        ESP_LOGI(TAG, "station "MACSTR" leave, AID=%d",
                 MAC2STR(event->mac), event->aid);
    }
}
void configure_apsta(void){
    nvs_flash_init(); //nvs初始化
    ESP_ERROR_CHECK(esp_netif_init());                   // 网络子系统底层初始化
    ESP_ERROR_CHECK(esp_event_loop_create_default());    // 创建默认循环发送队列
    esp_netif_create_default_wifi_ap();		         //创建网络配置-默认是STA 
    esp_netif_create_default_wifi_sta();
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT(); // WIFI设备配置
    ESP_ERROR_CHECK(esp_wifi_init(&cfg)); 			     // WIFI设备初始化
    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
                                                        ESP_EVENT_ANY_ID,
                                                        &wifi_event_handler,
                                                        NULL,
                                                        NULL));
    wifi_config_t ap_config = {
        .ap = {
            .ssid = "MY_AP",
            .ssid_len = strlen("MY_AP"),
            .channel = 1,
            .password = "",
            .max_connection = 4,
            .authmode = WIFI_AUTH_WPA_WPA2_PSK
        },
    };
    wifi_config_t sta_config = {
        .sta = {
            .ssid = "123",
            .password = "123456789",
	     //.threshold.authmode = ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD,
        },
    };
    esp_wifi_set_mode(WIFI_MODE_APSTA);
    //esp_wifi_set_config(WIFI_IF_AP , &ap_config);
    esp_wifi_set_config(WIFI_IF_STA, &sta_config);
    esp_wifi_start();    
    esp_wifi_connect();

    }

void configure_smartconfig(void){

    smartconfig_start_config_t smartconfig_config = {
        .enable_log = true,
        .esp_touch_v2_enable_crypt = true,
        .esp_touch_v2_key = NULL,
    };
    esp_smartconfig_start(&smartconfig_config);

}
void app_main(void)
{
    configure_apsta();

}
