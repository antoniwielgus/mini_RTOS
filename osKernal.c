#include "stdint.h"

#ifndef __ASM
#define __ASM __asm
#endif

#define NUM_OF_THREADS 3
#define STACK_SIZE 100

struct tcb // Thread Control Block
{
    int32_t *stackPt;
    struct tcb *nexPt;
};

typedef struct tcb tcbType;
tcbType tcbs[NUM_OF_THREADS]; // Task Control Blocks

// Stack for every particular tasks. Register's size in Cortex M4 is 4 byte
int32_t TCB_STACK[NUM_OF_THREADS][STACK_SIZE];

void osKernelStackInit(int i)
{
    tcbs[i].stackPt = &TCB_STACK[i][STACK_SIZE - 16];
    TCB_STACK[i][STACK_SIZE - 1] = 0x01000000; // The T (24)bit in EPSR must be
                                               // "set" always instruction pop may
                                               // overwrite it. This is reset value - 0x01000000

    // Describe in my theses T byte in ePSR register. It is responsible for Thumb and ARM mode.
}

tcbType *currentPt;

// Datasheet page 43, order of registers in stack
uint8_t osKernelAddThreads(void (*task0)(void), void (*task1)(void), void (*task2)(void))
{
    __ASM volatile("cpsid i" : : : "memory"); // Disable interrupt

    tcbs[0].nexPt = &tcbs[1];
    tcbs[1].nexPt = &tcbs[2];
    tcbs[2].nexPt = &tcbs[0];

    osKernelStackInit(0);
    TCB_STACK[0][STACK_SIZE - 2] = (int32_t)(task0); // -2 because of register PC (Program Counter) is the secound value from the end of stack

    osKernelStackInit(1);
    TCB_STACK[1][STACK_SIZE - 2] = (int32_t)(task1);

    osKernelStackInit(2);
    TCB_STACK[2][STACK_SIZE - 2] = (int32_t)(task2);

    currentPt = &tcbs[0];

    __ASM volatile("cpsie i" : : : "memory"); // Enable interrupt

    return 1;
}