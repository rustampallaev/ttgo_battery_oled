#include "delay.h"


void delay_rtos(int ms)
{
    vTaskDelay(delay_ms_to_ticks(ms));
}

void delay_hw_ms(int ms)
{
    ets_delay_us(1000 * ms);
}

void delay_hw_us(int us)
{
    ets_delay_us(us);
}

uint32_t delay_ticks_to_ms(uint32_t ticks)
{
    return (portTICK_PERIOD_MS / ticks);
}

uint32_t delay_ms_to_ticks(uint32_t ms)
{
    return (ms / portTICK_PERIOD_MS);
}