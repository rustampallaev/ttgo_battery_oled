
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void delay_rtos(int ms);
void delay_hw_ms(int ms);
void delay_hw_us(int us);
uint32_t delay_ticks_to_ms(uint32_t ticks);
uint32_t delay_ms_to_ticks(uint32_t ms);