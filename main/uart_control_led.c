#include "uart_control_led.h"
#include "rgb_led.h" // Asegúrate de incluir la biblioteca del LED RGB aquí
#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"

#define BUF_SIZE 1024
#define UART_NUM UART_NUM_0

void uart_control_led_init() {
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };

    // Configure UART parameters
    ESP_ERROR_CHECK(uart_param_config(UART_NUM, &uart_config));
    // Install UART driver using an event queue here
    ESP_ERROR_CHECK(uart_driver_install(UART_NUM, BUF_SIZE * 2, 0, 0, NULL, 0));
    // Set UART pins here
    ESP_ERROR_CHECK(uart_set_pin(UART_NUM, TXD_PIN, RXD_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));
}

void uart_control_led_task(void *pvParameters) {
    uint8_t* data = (uint8_t*) malloc(BUF_SIZE);
    while (1) {
        int len = uart_read_bytes(UART_NUM, data, BUF_SIZE, 20 / portTICK_RATE_MS);
        if (len > 0) {
            data[len] = '\0'; // Null-terminate whatever we received and treat it as a string
            uint8_t red, green, blue;
            // Parse received command and change LED intensity
            if (sscanf((const char *)data, "SET %hhu %hhu %hhu", &red, &green, &blue) == 3) {
                rgb_led_set_color(red, green, blue); // Llama a la función de la biblioteca del LED RGB
                // Optionally, echo back the received command or send an acknowledgment
            }
            // Clear the buffer after processing
            memset(data, 0, BUF_SIZE);
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
    free(data);
}

/* llamado en la principal 
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "uart_control_led.h"

void app_main() {
    uart_control_led_init(); // Inicializa la comunicación UART
    xTaskCreate(uart_control_led_task, "uart_control_led_task", 4096, NULL, 5, NULL); // Crea la tarea para control de LED
}

*/