#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "esp_wifi.h"
#include <esp_wifi_types.h>
#include "nvs_flash.h"

#define ESP_WIFI_SSID   "123"
#define ESP_WIFI_PASS   "123456789"


void task_test(void *pvParameters){

    while(1){

        printf("XJP-8964");
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }

    vTaskDelete(task_test);
}

void task_test_1(void *pvParameters){

    while(1){

        printf("XJPWCNM");
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }

    vTaskDelete(task_test_1);
}

void app_main(void)
{

    nvs_flash_init(); //nvs初始化
    esp_netif_init(); //netif初始化
    esp_event_loop_create_default(); //创建默认事件循环

    xTaskCreate(task_test, "Test", 4096, NULL, 3, NULL);
        xTaskCreate(task_test_1, "Test1", 4096, NULL, 3, NULL);

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT(); //初始化WiFi，使用默认配置
     esp_wifi_init(&cfg);
     esp_wifi_set_mode(WIFI_MODE_AP); // 设置为sta模式
     
    wifi_config_t wifi_config = {
        .ap = {
            .ssid = ESP_WIFI_SSID,
            .password = ESP_WIFI_PASS,

        },
    }; //WiFi初始化结构体
    esp_wifi_set_config(ESP_IF_WIFI_AP,&wifi_config); //将 WIFI_EVENT_STA_START 发布到事件任务
    esp_wifi_start();
    esp_wifi_connect();
    
}

