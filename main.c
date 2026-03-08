#include "stdint.h"
#include "stm32f4xx.h"


void SystemInit(void);
void LED_Init(void);
void SimpleDelay(uint32_t count);



int main(void)
{
	LED_Init();

    while(1)
    {
		// Change state on Pin 13 Port G
        GPIOG->ODR ^= GPIO_ODR_OD13;
		GPIOG->ODR ^= GPIO_ODR_OD14;
    }  

	return 0;
}




void SystemInit(void)
{
  /* FPU settings ------------------------------------------------------------*/
  #if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
    SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));  /* set CP10 and CP11 Full Access */
  #endif

#if defined (DATA_IN_ExtSRAM) || defined (DATA_IN_ExtSDRAM)
  SystemInit_ExtMemCtl(); 
#endif /* DATA_IN_ExtSRAM || DATA_IN_ExtSDRAM */

  /* Configure the Vector Table location -------------------------------------*/
#if defined(USER_VECT_TAB_ADDRESS)
  SCB->VTOR = VECT_TAB_BASE_ADDRESS | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal SRAM */
#endif /* USER_VECT_TAB_ADDRESS */
}

void LED_Init(void) 
{
    // 1. Włącz zegar dla portu GPIOG
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;

    // 2. Ustaw piny PG13 i PG14 jako wyjścia (Mode 01)
    GPIOG->MODER &= ~(GPIO_MODER_MODER13 | GPIO_MODER_MODER14); // Wyczyść bity
    GPIOG->MODER |= (GPIO_MODER_MODER13_0 | GPIO_MODER_MODER14_0); // Ustaw na 'Output'

    // 3. Opcjonalnie: ustaw prędkość i brak rezystorów pull-up/down
    GPIOG->OSPEEDR |= (GPIO_OSPEEDER_OSPEEDR13 | GPIO_OSPEEDER_OSPEEDR14);
}

