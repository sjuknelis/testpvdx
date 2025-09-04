#include "../FreeRTOSConfig.h"
#include "../ASF/thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/include/FreeRTOS.h"
#include "../ASF/thirdparty/RTOS/freertos/FreeRTOSV10.0.0/Source/include/task.h"
#include "../ASF/atmel_start.h"
#include "../ASF/atmel_start_pins.h"

// int main(void);

// __attribute__((section(".vectors"))) const long vectors[] = {0x2002FFFF, (long)main};

volatile int test = 8;

int main(void)
{
    while (test != 8);

    atmel_start_init();

    FREERTOS_V1000_0_example();
}

void vApplicationStackOverflowHook(TaskHandle_t xTask, signed char *pcTaskName)
{
    // This function is called when a stack overflow is detected
}

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer,
                                   configSTACK_DEPTH_TYPE *puxIdleTaskStackSize_StackDepthType)
{
    // Must be static so it doesn't go out of scope when the function ends
    static StaticTask_t xIdleTaskTCB;
    static StackType_t uxIdleTaskStack[configMINIMAL_STACK_SIZE];

    /* Pass out a pointer to the StaticTask_t structure in which the Idle task's
    state will be stored. */
    *ppxIdleTaskTCBBuffer = &xIdleTaskTCB;

    /* Pass out the array that will be used as the Idle task's stack. */
    *ppxIdleTaskStackBuffer = uxIdleTaskStack;

    /* Pass out the size of the array pointed to by *ppxIdleTaskStackBuffer.
    Note that, as the array is necessarily of type StackType_t,
    configMINIMAL_STACK_SIZE is specified in words, not bytes. */
    StackType_t *puxIdleTaskStackSize = (StackType_t *)puxIdleTaskStackSize_StackDepthType;
    *puxIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}

void vApplicationGetTimerTaskMemory(StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer,
                                    configSTACK_DEPTH_TYPE *puxTimerTaskStackSize_StackDepthType)
{
    // Must be static so it doesn't go out of scope when the function ends
    static StaticTask_t xTimerTaskTCB;
    static StackType_t uxTimerTaskStack[configTIMER_TASK_STACK_DEPTH];

    /* Pass out a pointer to the StaticTask_t structure in which the Timer
    task's state will be stored. */
    *ppxTimerTaskTCBBuffer = &xTimerTaskTCB;

    /* Pass out the array that will be used as the Timer task's stack. */
    *ppxTimerTaskStackBuffer = uxTimerTaskStack;

    /* Pass out the size of the array pointed to by *ppxTimerTaskStackBuffer.
    Note that, as the array is necessarily of type StackType_t,
    configTIMER_TASK_STACK_DEPTH is specified in words, not bytes. */
    StackType_t *puxTimerTaskStackSize = (StackType_t *)puxTimerTaskStackSize_StackDepthType;
    *puxTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}