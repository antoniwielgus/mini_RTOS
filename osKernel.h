#ifndef _OS_KERNEL_H
#define _OS_KERNEL_H

#include <stdint.h>
#include "stm32f4xx.h"

#define NUM_OF_THREADS      32
typedef void (*TaskFunction)(void);

typedef enum 
{
    TASK_READY = 0,
    TASK_RUNNING,
    TASK_SLEEPING,
    TASK_BLOCKED
} TaskState;

uint8_t osKernelAddThreads(TaskFunction* taskArray, uint8_t tasksAmount);
void nnOsKernelInit(void);
void osKernelLaunch(uint32_t quanta);
void osThreadYield(void);
void task_delay(uint32_t ticks);
void osScheduler(void);
void osTick(void);


#endif
