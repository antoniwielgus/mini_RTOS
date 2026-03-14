// To run the project:
// - make clean
// - make
// and at the end use STM32CubeProgrammer to upload .elf file

#include "stdint.h"
#include "stm32f4xx.h"

// void SystemInit(void);
void LED_Init(void);
void Delay(uint32_t count);

volatile uint32_t msTicks = 0;
extern uint32_t SystemCoreClock;


int main(void)
{
  SysTick_Config(SystemCoreClock / 1000);

  LED_Init();

  while (1)
  {
    // Change state on Pin 13 Port G
    GPIOG->ODR ^= GPIO_ODR_OD13;
    GPIOG->ODR ^= GPIO_ODR_OD14;
    Delay(500);
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

void SysTick_Handler(void)
{
  msTicks++;
}

void Delay(uint32_t ms)
{
  uint32_t start = msTicks;
  while ((msTicks - start) < ms)
    ;
}
