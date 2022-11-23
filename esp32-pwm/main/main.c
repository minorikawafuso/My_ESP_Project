
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/ledc.h"
#include "esp_log.h"
#include "sdkconfig.h"


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

void app_main(void)
{
    while(1){
        for(uint8_t i = 0; i < 255; i++){
            output_pwm(16, i);
            vTaskDelay(1);
        }
            for(uint8_t i = 255; i > 0; i--){
            output_pwm(16, i);
            vTaskDelay(1);
        }
    }
}
