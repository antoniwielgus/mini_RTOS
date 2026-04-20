// To run the project:
// - make clean
// - make
// and at the end use STM32CubeProgrammer to upload .elf file

#include "stdint.h"
#include "stm32f4xx.h"
#include "osKernel.h"

void LED_Init(void);
void Delay(uint32_t count);

volatile uint32_t msTicks = 0;
extern uint32_t SystemCoreClock;

uint32_t count0, count1, count2;


void Task0(void)
{
  while (1)
  {
    count0++;
    GPIOG->ODR ^= GPIO_ODR_OD13;

    task_delay(10);
    // osThreadYield();
		// osThreadYield();
		// osThreadYield();
		// osThreadYield();
		// osThreadYield();
		// osThreadYield();
		// osThreadYield();
		// osThreadYield();
  }
}

void Task1(void)
{
  while (1)
  {
    count1++;
    GPIOG->ODR ^= GPIO_ODR_OD14;

    task_delay(5);
    // osThreadYield();
		// osThreadYield();
		// osThreadYield();
		// osThreadYield();
  }
}

void Task2(void)
{
  while (1)
  {
    count2++;
    // osThreadYield();
  }
}



int main(void)
{
  LED_Init();

  nnOsKernelInit();
  osKernelAddThreads(Task0, Task1, Task2);
  osKernelLaunch(100u);

  while (1)
  {

  }

  return 0;
}


void LED_Init(void)
{
  // 1. Włącz zegar dla portu GPIOG
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;

  // 2. Ustaw piny PG13 i PG14 jako wyjścia (Mode 01)
  GPIOG->MODER &= ~(GPIO_MODER_MODER13 | GPIO_MODER_MODER14);    // Wyczyść bity
  GPIOG->MODER |= (GPIO_MODER_MODER13_0 | GPIO_MODER_MODER14_0); // Ustaw na 'Output'

  // 3. Opcjonalnie: ustaw prędkość i brak rezystorów pull-up/down
  GPIOG->OSPEEDR |= (GPIO_OSPEEDER_OSPEEDR13 | GPIO_OSPEEDER_OSPEEDR14);
}

void Delay(uint32_t ms)
{
  uint32_t start = msTicks;
  while ((msTicks - start) < ms);
}

