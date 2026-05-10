// To run the project:
// - make clean
// - make
// and at the end use STM32CubeProgrammer to upload .elf file

#include "stdint.h"
#include "stm32f4xx.h"
#include "osKernel.h"

void GPIO_Init(void);
void Delay(uint32_t count);

volatile uint32_t msTicks = 0;
// extern uint32_t SystemCoreClock;

uint32_t count0, count1, count2;


void Task0(void)
{
  while (1)
  {
    count0++;
    GPIOG->ODR ^= GPIO_ODR_OD13; // pin toggle

    task_delay(1000);
  }
}

void Task1(void)
{
  while (1)
  {
    count1++;
    GPIOG->ODR ^= GPIO_ODR_OD14; // pin toggle

    task_delay(333);
  }
}

void Task2(void)
{
  while (1)
  {
    count2++;
    GPIOG->ODR ^= GPIO_ODR_OD15; // pin toggle

    // task_delay(2);
  }
}



int main(void)
{
  GPIO_Init();

  nnOsKernelInit();
  osKernelAddThreads(Task0, Task1, Task2);
  osKernelLaunch(1u);

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
