#include "stm32f4xx.h" 

void SysTick_Initialize(){
	SysTick->CTRL=0;
	SysTick->LOAD = 16000000-1;
	NVIC_SetPriority(SysTick_IRQn, 6);
	SysTick->VAL = 0;	
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk; 	
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
}
