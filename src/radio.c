

#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "delay.h"
#include "nrf24l01.h"

#define     MODE_SENDER

#define     NRF_CE      (1)
#define     NRF_CS      (1)
#define     NRF_SCK     (1)
#define     NRF_MOSI    (1)
#define     NRF_MISO    (1)


static void radio_thread(void * pvParameters);


void radio_start(void)
{
    xTaskCreate(radio_thread, "radio_thread", 2 * 4096, NULL, 10, NULL);
}

static void radio_thread(void * pvParameters)
{
	uint8_t buff[32] = {0};
	uint8_t addr[5] = {222, 111, 001, 100, 040};
    int8_t result;

    printf("radio_thread\n");

#ifdef MODE_SENDER
    nrf_init(NRF_CE, NRF_CS, NRF_SCK, NRF_MOSI, NRF_MISO, nrf_tx_mode);
#else
    nrf_init(NRF_CE, NRF_CS, NRF_SCK, NRF_MOSI, NRF_MISO, nrf_rx_mode);
#endif
    
    nrf_set_pipe_addr(0, addr, 5);
    
#ifdef MODE_SENDER
    printf("Tx mode\n");
    nrf_set_tx_addr(addr, 5);

    for(int i = 0; i < 32; i++)
        buff[i] = i;

    for(;;) {
        result = nrf_send(buff, 32);
        buff[1]++;
        
        printf("Result: %d\n", result);
        delay_rtos(1500);
    }
#elif
    printf("Rx mode\n");
    for(;;) {
        delay_rtos(10);

        if (!nrf_is_rx_data_available())
            continue;
        
        nrf_read(buff, 32);
        printf("Received: ");
        for(int i = 0; i < 32; i++)
            printf("%d ", buff[i]);
        printf("\n");
    }
#endif
}
