#include "temperature_sensor.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


// Inicialización del ADC
void adc_init() {
    // Configuración de ADC 
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(ADC_CHANNEL, ADC_ATTEN_DB_0);

    // Calibración del ADC (opcional si se requiere calibración)
    esp_adc_cal_characteristics_t *adc_chars = calloc(1, sizeof(esp_adc_cal_characteristics_t));
    esp_adc_cal_characterize(ADC_UNIT_2, ADC_ATTEN_DB_0, ADC_WIDTH_BIT_12, DEFAULT_VREF, adc_chars);
}

float read_temperature() {
    static float last_valid_temp = 0; // Variable estática para almacenar la última temperatura válida
    
    int raw;
    uint32_t adc_reading = 0;
    const int num_samples = 10;
    const int num_c = 100;


    for (int i = 0; i < num_samples; i++) {
        raw = adc1_get_raw(ADC_CHANNEL);
        adc_reading += raw;
        vTaskDelay(pdMS_TO_TICKS(500)); // Pequeña pausa entre muestras
    }

    float average = (float)adc_reading / num_samples;
    float temp = average/num_c;


        // Comprobar si temp está fuera del rango deseado (5 a 100)
    if (temp < 5 || temp > 100) {
        return last_valid_temp; // Devolver la última temperatura válida
    } else {
        last_valid_temp = temp; // Actualizar la última temperatura válida
        return temp; // Devolver la temperatura actual
    }
    
}