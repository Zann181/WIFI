#include "led_control.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "esp_log.h" // Asegúrate de incluir esto si estás usando ESP_LOGI
#include "driver/ledc.h"


#define GPIO_LED GPIO_NUM_2

#define LEDC_HS_TIMER          LEDC_TIMER_0
#define LEDC_HS_MODE           LEDC_HIGH_SPEED_MODE
#define LEDC_HS_CH0_GPIO       GPIO_LED
#define LEDC_HS_CH0_CHANNEL    LEDC_CHANNEL_0
#define LEDC_TEST_DUTY         (4000) // Valor inicial de la intensidad
#define LEDC_TEST_FADE_TIME    (3000) // Tiempo de fade (no lo usaremos aquí, pero es bueno tenerlo)

// En led_control.c
uint32_t current_intensity = 0;  // Asumiendo que esto es tu valor inicial.

static const char *TAG = "LED_CONTROL";

static bool led_state = false; // Estado inicial del LED: apagado

esp_err_t led_init(void) {
    // Configuración del timer
    ledc_timer_config_t ledc_timer = {
        .duty_resolution = LEDC_TIMER_13_BIT, // Resolución de 13 bits
        .freq_hz = 5000,                      // Frecuencia de 5kHz
        .speed_mode = LEDC_HS_MODE,           // Modo de alta velocidad
        .timer_num = LEDC_HS_TIMER            // Timer 0
    };
    ledc_timer_config(&ledc_timer);

    // Configuración del canal
    ledc_channel_config_t ledc_channel = {
        .channel    = LEDC_HS_CH0_CHANNEL,
        .duty       = 0,                      // Inicialmente apagado
        .gpio_num   = LEDC_HS_CH0_GPIO,
        .speed_mode = LEDC_HS_MODE,
        .hpoint     = 0,
        .timer_sel  = LEDC_HS_TIMER
    };
    ledc_channel_config(&ledc_channel);

    ESP_LOGI(TAG, "init led with PWM completed");
    return ESP_OK;
}



void led_set_intensity(uint32_t intensity) {
    if(intensity > 8191) { // 2^13 - 1
        intensity = 8191;
    }
    ledc_set_duty(LEDC_HS_MODE, LEDC_HS_CH0_CHANNEL, intensity);
    ledc_update_duty(LEDC_HS_MODE, LEDC_HS_CH0_CHANNEL);
}


uint32_t led_get_intensity() {
    return current_intensity;
}


void led_toggle(void) {
    led_state = !led_state; // Cambiar el estado del LED
    gpio_set_level(GPIO_LED, led_state);
}

bool led_get_state(void) {
    return led_state;
}
