#include "stdint.h"
#include "osKernel.h"


void nnOsSchedulerLaunch(void);

#define SYSPRI3             (*((volatile uint32_t *)0xE000ED20)) //System Handler Priority Register 3
#define INTCTRL             (*((volatile uint32_t *)0xE000ED04)) // Interrupt Control and State Register

// SysTick struct from cmsis (arm datasheet page 51)
typedef struct
{
    volatile uint32_t CTRL;         // Offset: 0x000 (R/W) SysTick Control and Status Register
    volatile uint32_t LOAD;         // Offset: 0x004 (R/W) SysTick Reload Value Register
    volatile uint32_t VAL;          // Offset: 0x008 (R/W) SysTick Current Value Register
    volatile const uint32_t CALIB;  // Offset: 0x00C (R/ ) SysTick Callibration Register
} SysTick_Type;

#define SCS_BASE            (0xE000E000UL)                      // System Control Space Base Address
#define SysTick_BASE        (SCS_BASE + 0x0010UL)               // SysTick Base Address, PM page 246
#define SysTick             ((SysTick_Type  *)  SysTick_BASE)   // SysTick configuration struct


#ifndef __ASMz
#define __ASM               __asm
#endif


#define BUS_FREQ            16000000
uint32_t MILLIS_PRESCALLER;


#define NUM_OF_THREADS      3
#define STACK_SIZE          100

struct tcb // Task Control Block
{
    int32_t *stackPt;
    struct tcb *nexPt;
    uint32_t delayTicks;
    TaskState state;          // 0: READY, 1: SLEEPING
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

volatile tcbType *currentPt;

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

    currentPt = &tcbs[0]; // Set currentPt as first thread

    __ASM volatile("cpsie i" : : : "memory"); // Enable interrupt

    return 1;
}

void nnOsKernelInit(void)
{
    __ASM volatile ("cpsid i" : : : "memory"); // Disable interrupt
    MILLIS_PRESCALLER = (BUS_FREQ / 1000); // How many ticks for 1ms
}

// Interrupt vector (page 40 PM - programming manual)
void osKernelLaunch(uint32_t quanta) // quanta - how long one threat will work
{
    SysTick->CTRL = 0; // Disable SysTick counter
    SysTick->VAL = 0;
    SysTick->LOAD = (quanta * MILLIS_PRESCALLER) - 1;

    SYSPRI3 = (SYSPRI3&0x00FFFFFF) | 0xE0000000; // System Handler Priority Register (Page 51 - ARM Documentation | PM page 234)

    SysTick->CTRL = 0x00000007;
    nnOsSchedulerLaunch();
}

void osThreadYield(void)
{
    SysTick->VAL = 0;
    INTCTRL = 0x04000000;
}

void task_delay(uint32_t ticks)
{
    __ASM volatile("cpsid i" : : : "memory"); // Disable interrupt

    currentPt->delayTicks = ticks;
    currentPt->state = TASK_SLEEPING;

    __ASM volatile("cpsie i" : : : "memory"); // Enable interrupt

    volatile uint32_t test_ = currentPt->delayTicks;

    
    // SysTick interrupt
    osThreadYield();
}

void osScheduler(void)
{
    do 
    {
        currentPt = currentPt->nexPt;
    } while (currentPt->state != TASK_READY);
}

// This function will: 
// go ahead through every tasks 
// decrements delayTicks
// wakes up tasks
void osTick(void)
{
    tcbType *pt = currentPt;

    do 
    {
        if (pt->state == TASK_SLEEPING)
        {
            if (pt->delayTicks > 0)
            {
                pt->delayTicks--;

                if (pt->delayTicks == 0)
                {
                    pt->state = TASK_READY;
                }
            }
        }

        pt = pt->nexPt;
    } while (pt != currentPt);
}

