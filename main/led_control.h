#ifndef LED_CONTROL_H
#define LED_CONTROL_H

#include "esp_system.h"

// Inicializa el GPIO para el LED
esp_err_t led_init(void);

// Cambia el estado del LED (on/off)
void led_toggle(void);

// Función para configurar la intensidad del LED
void led_set_intensity(uint32_t intensity);

uint32_t led_get_intensity(void);


// Obtiene el estado actual del LED
bool led_get_state(void);

#endif // LED_CONTROL_H
