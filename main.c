// To run the project:
// - make clean
// - make
// and at the end use STM32CubeProgrammer to upload .elf file

#include "stdint.h"
#include "stm32f4xx.h"
#include "osKernel.h"


void GPIO_Init(void);
void Delay(uint32_t count);
void set_PG13_High();
void set_PG13_Low();

volatile uint32_t msTicks = 0;
// extern uint32_t SystemCoreClock;

volatile uint32_t counter1 = 0;
volatile uint32_t counter2 = 0;
volatile uint32_t counter3 = 0;

uint32_t count0, count1, count2;
double value1 = 0.; 
double value2 = 0.;
double value3 = 0.;

volatile uint32_t control;
volatile uint32_t fpccr;

volatile uint8_t fpca;
volatile uint8_t lspact;
volatile uint8_t aspen;
volatile uint8_t lspen;
void debugFPUState();


void Task0(void)
{
  while (1)
  {
    uint32_t tab[78] = {};
    __ASM volatile("cpsid i" : : : "memory");
    GPIOG->ODR ^= GPIO_ODR_OD13; // pin toggle
    __ASM volatile("cpsie i" : : : "memory");

    task_delay(100);
  }
}

void Task1(void)
{
  while (1)
  {
    __ASM volatile("cpsid i" : : : "memory");
    GPIOG->ODR ^= GPIO_ODR_OD14; // pin toggle
    __ASM volatile("cpsie i" : : : "memory");

    task_delay(5350);
  }
}

void Task2(void)
{
  while (1)
  {
    __ASM volatile("cpsid i" : : : "memory");
    GPIOG->ODR ^= GPIO_ODR_OD15; // pin toggle
    __ASM volatile("cpsie i" : : : "memory");

    task_delay(50);
  }
}

void Task3(void)
{
  while (1)
  {
    __ASM volatile("cpsid i" : : : "memory");
    counter1++;
    __ASM volatile("cpsie i" : : : "memory");

    task_delay(500);
  }
}

void Task4(void)
{
  while (1)
  {
    counter2++;

    task_delay(20);
  }
}

void Task5(void)
{
  while (1)
  {
    counter3++;
  }
}

void Task6(void)
{
  while (1)
  {
    __ASM volatile("cpsid i" : : : "memory");
    // GPIOG->ODR ^= GPIO_ODR_OD15; // pin toggle
    __ASM volatile("cpsie i" : : : "memory");

    task_delay(500);
  }
}

void Task7(void)
{
  while (1)
  {
    __ASM volatile("cpsid i" : : : "memory");
    // GPIOG->ODR ^= GPIO_ODR_OD15; // pin toggle
    __ASM volatile("cpsie i" : : : "memory");

    // task_delay(500);
  }
}

void Task8(void)
{
  while (1)
  {
    __ASM volatile("cpsid i" : : : "memory");
    // GPIOG->ODR ^= GPIO_ODR_OD13; // pin toggle
    __ASM volatile("cpsie i" : : : "memory");

    // task_delay(500);
  }
}

void Task9(void)
{
  while (1)
  {
    __ASM volatile("cpsid i" : : : "memory");
    // GPIOG->ODR ^= GPIO_ODR_OD14; // pin toggle
    __ASM volatile("cpsie i" : : : "memory");

    // task_delay(500);
  }
}

void Task10(void)
{
  while (1)
  {
    __ASM volatile("cpsid i" : : : "memory");
    // GPIOG->ODR ^= GPIO_ODR_OD15; // pin toggle
    __ASM volatile("cpsie i" : : : "memory");

    // task_delay(500);
  }
}

void Task11(void)
{
  while (1)
  {
    __ASM volatile("cpsid i" : : : "memory");
    // GPIOG->ODR ^= GPIO_ODR_OD15; // pin toggle
    __ASM volatile("cpsie i" : : : "memory");

    // task_delay(500);
  }
}

void Task12(void)
{
  while (1)
  {
    __ASM volatile("cpsid i" : : : "memory");
    // GPIOG->ODR ^= GPIO_ODR_OD13; // pin toggle
    __ASM volatile("cpsie i" : : : "memory");

    // task_delay(500);
  }
}

void Task13(void)
{
  while (1)
  {
    __ASM volatile("cpsid i" : : : "memory");
    // GPIOG->ODR ^= GPIO_ODR_OD14; // pin toggle
    __ASM volatile("cpsie i" : : : "memory");

    // task_delay(500);
  }
}

void Task14(void)
{
  while (1)
  {
    __ASM volatile("cpsid i" : : : "memory");
    // GPIOG->ODR ^= GPIO_ODR_OD15; // pin toggle
    __ASM volatile("cpsie i" : : : "memory");

    // task_delay(500);
  }
}

void Task15(void)
{
  while (1)
  {
    __ASM volatile("cpsid i" : : : "memory");
    // GPIOG->ODR ^= GPIO_ODR_OD15; // pin toggle
    __ASM volatile("cpsie i" : : : "memory");

    // task_delay(500);
  }
}

//////////////////////////////////////////////////////////////////////////////////////

void Task16(void)
{
  while (1)
  {
    __ASM volatile("cpsid i" : : : "memory");
    // GPIOG->ODR ^= GPIO_ODR_OD13; // pin toggle
    __ASM volatile("cpsie i" : : : "memory");

    // task_delay(500);
  }
}

void Task17(void)
{
  while (1)
  {
    __ASM volatile("cpsid i" : : : "memory");
    // GPIOG->ODR ^= GPIO_ODR_OD14; // pin toggle
    __ASM volatile("cpsie i" : : : "memory");

    // task_delay(500);
  }
}

void Task18(void)
{
  while (1)
  {
    __ASM volatile("cpsid i" : : : "memory");
    // GPIOG->ODR ^= GPIO_ODR_OD15; // pin toggle
    __ASM volatile("cpsie i" : : : "memory");

    // task_delay(500);
  }
}

void Task19(void)
{
  while (1)
  {
    __ASM volatile("cpsid i" : : : "memory");
    // GPIOG->ODR ^= GPIO_ODR_OD15; // pin toggle
    __ASM volatile("cpsie i" : : : "memory");

    // task_delay(500);
  }
}

void Task20(void)
{
  while (1)
  {
    __ASM volatile("cpsid i" : : : "memory");
    // GPIOG->ODR ^= GPIO_ODR_OD13; // pin toggle
    __ASM volatile("cpsie i" : : : "memory");

    // task_delay(500);
  }
}

void Task21(void)
{
  while (1)
  {
    __ASM volatile("cpsid i" : : : "memory");
    // GPIOG->ODR ^= GPIO_ODR_OD14; // pin toggle
    __ASM volatile("cpsie i" : : : "memory");

    // task_delay(500);
  }
}

void Task22(void)
{
  while (1)
  {
    __ASM volatile("cpsid i" : : : "memory");
    // GPIOG->ODR ^= GPIO_ODR_OD15; // pin toggle
    __ASM volatile("cpsie i" : : : "memory");

    // task_delay(500);
  }
}

void Task23(void)
{
  while (1)
  {
    __ASM volatile("cpsid i" : : : "memory");
    // GPIOG->ODR ^= GPIO_ODR_OD15; // pin toggle
    __ASM volatile("cpsie i" : : : "memory");

    // task_delay(500);
  }
}

void Task24(void)
{
  while (1)
  {
    __ASM volatile("cpsid i" : : : "memory");
    // GPIOG->ODR ^= GPIO_ODR_OD13; // pin toggle
    __ASM volatile("cpsie i" : : : "memory");

    // task_delay(500);
  }
}

void Task25(void)
{
  while (1)
  {
    __ASM volatile("cpsid i" : : : "memory");
    // GPIOG->ODR ^= GPIO_ODR_OD14; // pin toggle
    __ASM volatile("cpsie i" : : : "memory");

    // task_delay(500);
  }
}

void Task26(void)
{
  while (1)
  {
    __ASM volatile("cpsid i" : : : "memory");
    // GPIOG->ODR ^= GPIO_ODR_OD15; // pin toggle
    __ASM volatile("cpsie i" : : : "memory");

    // task_delay(500);
  }
}

void Task27(void)
{
  while (1)
  {
    __ASM volatile("cpsid i" : : : "memory");
    // GPIOG->ODR ^= GPIO_ODR_OD15; // pin toggle
    __ASM volatile("cpsie i" : : : "memory");

    // task_delay(500);
  }
}

void Task28(void)
{
  while (1)
  {
    __ASM volatile("cpsid i" : : : "memory");
    // GPIOG->ODR ^= GPIO_ODR_OD13; // pin toggle
    __ASM volatile("cpsie i" : : : "memory");

    // task_delay(500);
  }
}

void Task29(void)
{
  while (1)
  {
    __ASM volatile("cpsid i" : : : "memory");
    // GPIOG->ODR ^= GPIO_ODR_OD14; // pin toggle
    __ASM volatile("cpsie i" : : : "memory");

    // task_delay(500);
  }
}

void Task30(void)
{
  while (1)
  {
    __ASM volatile("cpsid i" : : : "memory");
    // GPIOG->ODR ^= GPIO_ODR_OD15; // pin toggle
    __ASM volatile("cpsie i" : : : "memory");

    // task_delay(500);
  }
}





void idleTask(void)
{
  while(1)
  {
    __ASM volatile("wfi"); // Wait For Interrupt
  }
}

TaskFunction taskArray[NUM_OF_THREADS] = {
  Task0,
  Task1,
  Task2,
  Task3,
  Task4,
  Task5,
  Task6,
  Task7,
  Task8,
  Task9,
  Task10,
  Task11,
  Task12,
  Task13,
  Task14,
  Task15,
  Task16,
  Task17,
  Task18,
  Task19,
  Task20,
  Task21,
  Task22,
  Task23,
  Task24,
  Task25,
  Task26,
  Task27,
  Task28,
  Task29,
  Task30,
  idleTask
};



int main(void)
{
  GPIO_Init();

  nnOsKernelInit();
  osKernelAddThreads(taskArray, NUM_OF_THREADS);
  osKernelLaunch(1u);

  // FPU->FPCCR &= ~(FPU_FPCCR_LSPEN_Msk);
  // FPU->FPCCR &= ~(FPU_FPCCR_LSPACT_Msk);
  

  while (1)
  {

  }

  return 0;
}


void GPIO_Init(void)
{
  // 1. Włącz zegar dla portu GPIOG
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;

  // 2. Ustaw piny PG13 i PG14 jako wyjścia (Mode 01)
  GPIOG->MODER &= ~(GPIO_MODER_MODER13 | GPIO_MODER_MODER14 | GPIO_MODER_MODER15);    // Wyczyść bity
  GPIOG->MODER |= (GPIO_MODER_MODER13_0 | GPIO_MODER_MODER14_0 | GPIO_MODER_MODER15_0); // Ustaw na 'Output'

  // 3. Opcjonalnie: ustaw prędkość i brak rezystorów pull-up/down
  GPIOG->OSPEEDR |= (GPIO_OSPEEDER_OSPEEDR13 | GPIO_OSPEEDER_OSPEEDR14 | GPIO_OSPEEDER_OSPEEDR15);
}

void Delay(uint32_t ms)
{
  uint32_t start = msTicks;
  while ((msTicks - start) < ms);
}

void debugFPUState()
{
  control = __get_CONTROL();
  // __set_CONTROL();
  fpccr   = FPU->FPCCR;

  fpca   = (control >> 2) & 1;
  lspact = (fpccr >> 0) & 1;
  aspen  = (fpccr >> 31) & 1;
  lspen  = (fpccr >> 30) & 1;
}

void set_PG13_High()
{
    // __ASM volatile("cpsid i" : : : "memory");
    GPIOG->ODR |= GPIO_ODR_OD13;
    // __ASM volatile("cpsie i" : : : "memory");
}

void set_PG13_Low()
{
    // __ASM volatile("cpsid i" : : : "memory");
    GPIOG->ODR &= ~GPIO_ODR_OD13;
    // __ASM volatile("cpsie i" : : : "memory");
}
