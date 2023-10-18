#include "led_control.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "esp_log.h" // Asegúrate de incluir esto si estás usando ESP_LOGI

#define GPIO_LED GPIO_NUM_2
static const char *TAG = "LED_CONTROL";

static bool led_state = false; // Estado inicial del LED: apagado

esp_err_t led_init(void) { // Cambiado el tipo de retorno a esp_err_t
    esp_rom_gpio_pad_select_gpio(GPIO_LED);
    gpio_set_direction(GPIO_LED, GPIO_MODE_OUTPUT);
    gpio_set_level(GPIO_LED, 1); // Inicialmente apagado
    ESP_LOGI(TAG, "init led completed");
    return ESP_OK;
}

void led_toggle(void) {
    led_state = !led_state; // Cambiar el estado del LED
    gpio_set_level(GPIO_LED, led_state);
}

bool led_get_state(void) {
    return led_state;
}
