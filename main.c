#include "pico/stdlib.h"
#include <stdio.h>
#include <stdlib.h>
#include "hardware/pio.h"
#include "build/generated/pico_base/pico/ws2812.pio.h"
#include "numeros.h"

#define LED_COUNT 25
#define WS2812 7
#define IS_RGB false
#define BUTTON_PIN_INC 5
#define BUTTON_PIN_DEC 6
#define LED_RED 13
#define DEBOUNCE_TIME 200 // Tempo de debounce em ms

volatile int current_number = 0;
volatile uint32_t last_interrupt_time_inc = 0;
volatile uint32_t last_interrupt_time_dec = 0;



void display_number(int number, uint32_t *leds) {
    for (int i = 0; i < LED_COUNT; i++) {
        leds[i] = number_patterns[number][i];
    }
}
void blink_red_led() {
    for (int i = 0; i < 5; i++) {
        gpio_put(LED_RED, 1);
        sleep_ms(100); // 100 ms on
        gpio_put(LED_RED, 0);
        sleep_ms(100); // 100 ms off
    }
}

void gpio_callback(uint gpio, uint32_t events) {
    uint32_t current_time = to_ms_since_boot(get_absolute_time());
    if (gpio == BUTTON_PIN_INC) {
        if (current_time - last_interrupt_time_inc > DEBOUNCE_TIME) {
            current_number = (current_number + 1) % 10;
            last_interrupt_time_inc = current_time;
        }
    } else if (gpio == BUTTON_PIN_DEC) {
        if (current_time - last_interrupt_time_dec > DEBOUNCE_TIME) {
            current_number = (current_number - 1 + 10) % 10;
            last_interrupt_time_dec = current_time;
        }
    }
}

int main() {
    stdio_init_all();
    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);
    ws2812_program_init(pio, sm, offset, WS2812, 800000, IS_RGB);
    uint32_t leds[LED_COUNT];
    for (int i = 0; i < LED_COUNT; i++) {
        leds[i] = 0x00000000; // Apaga todos os LEDs
    }

    gpio_init(BUTTON_PIN_INC);
    gpio_set_dir(BUTTON_PIN_INC, GPIO_IN);
    gpio_pull_up(BUTTON_PIN_INC);
    gpio_set_irq_enabled_with_callback(BUTTON_PIN_INC, GPIO_IRQ_EDGE_FALL, true, &gpio_callback);

    gpio_init(BUTTON_PIN_DEC);
    gpio_set_dir(BUTTON_PIN_DEC, GPIO_IN);
    gpio_pull_up(BUTTON_PIN_DEC);
    gpio_set_irq_enabled_with_callback(BUTTON_PIN_DEC, GPIO_IRQ_EDGE_FALL, true, &gpio_callback);

    gpio_init(LED_RED);
    gpio_set_dir(LED_RED, GPIO_OUT);

    while (true) {
        display_number(current_number, leds);
        for (int j = 0; j < LED_COUNT; j++) {
            pio_sm_put_blocking(pio, sm, leds[j]);
        }
        blink_red_led(); // Pisca o LED vermelho 5 vezes por segundo
        sleep_ms(100); // Pequena pausa para evitar sobrecarga da CPU
    }
}
