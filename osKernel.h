#ifndef _OS_KERNEL_H
#define _OS_KERNEL_H

#include <stdint.h>


uint8_t osKernelAddThreads(void(*task0)(void), void(*task1)(void), void(*task2)(void));
void nnOsKernelInit(void);
void osKernelLaunch(uint32_t quanta);
void osThreadYield(void);


#endif