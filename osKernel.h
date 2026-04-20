#ifndef _OS_KERNEL_H
#define _OS_KERNEL_H

#include <stdint.h>


typedef enum 
{
    TASK_READY = 0,
    TASK_RUNNING,
    TASK_SLEEPING,
    TASK_BLOCKED
} TaskState;

uint8_t osKernelAddThreads(void(*task0)(void), void(*task1)(void), void(*task2)(void));
void nnOsKernelInit(void);
void osKernelLaunch(uint32_t quanta);
void osThreadYield(void);
void task_delay(uint32_t ticks);
void osScheduler(void);
void osTick(void);


#endif