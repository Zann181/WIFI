#ifndef LED_CONTROL_H
#define LED_CONTROL_H

#include "esp_system.h"

// Inicializa el GPIO para el LED
esp_err_t led_init(void);

// Cambia el estado del LED (on/off)
void led_toggle(void);

// Obtiene el estado actual del LED
bool led_get_state(void);

#endif // LED_CONTROL_H
