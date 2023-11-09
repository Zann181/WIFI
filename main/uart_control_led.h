#ifndef UART_CONTROL_LED_H
#define UART_CONTROL_LED_H

#ifdef __cplusplus
extern "C" {
#endif

void uart_control_led_init();
void uart_control_led_task(void *pvParameters);

#ifdef __cplusplus
}
#endif

#endif // UART_CONTROL_LED_H
