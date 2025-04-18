#include "../ASF/thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/include/FreeRTOS.h"
#include "../ASF/thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/include/task.h"

// int main(void);

// __attribute__((section(".vectors"))) const long vectors[] = {0x2002FFFF, (long)main};

volatile int test = 8;

int main(void) {
    while (test != 8);

    volatile int a = 1;
    a++;
    for (;;);
}

void vApplicationStackOverflowHook(TaskHandle_t xTask, signed char *pcTaskName) {
    // This function is called when a stack overflow is detected

}