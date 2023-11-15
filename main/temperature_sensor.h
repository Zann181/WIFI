#ifndef TEMPERATURE_SENSOR_H
#define TEMPERATURE_SENSOR_H

#include <driver/adc.h>
#include <esp_adc_cal.h>

#define ADC_CHANNEL ADC1_CHANNEL_6  // GPIO34 en ESP32
#define DEFAULT_VREF 1100           // Use adc2_vref_to_gpio() para medir el voltaje de referencia del sistema
#define NO_OF_SAMPLES 64            // Multimuestreo

#ifdef __cplusplus
extern "C" {
#endif

void adc_init();
float read_temperature();
#ifdef __cplusplus
}
#endif

#endif // TEMPERATURE_SENSOR_H
