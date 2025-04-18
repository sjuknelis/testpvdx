#include "../ASF/thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/include/FreeRTOS.h"
#include "../ASF/thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/include/task.h"
#include "../ASF/atmel_start.h"
#include "../ASF/atmel_start_pins.h"

// int main(void);

// __attribute__((section(".vectors"))) const long vectors[] = {0x2002FFFF, (long)main};

volatile int test = 8;

int main(void) {
    while (test != 8);

    atmel_start_init();

    volatile int a = 1;
    a++;
    while (1) {
        gpio_set_pin_level(LED_Orange1, false);
        // for (int i = 0; i < 10000; i++);
        gpio_set_pin_level(LED_Orange1, true);
        // for (int i = 0; i < 10000; i++);
    }
}

void vApplicationStackOverflowHook(TaskHandle_t xTask, signed char *pcTaskName) {
    // This function is called when a stack overflow is detected

}