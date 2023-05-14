#include "stm32f4xx.h"

void touch_button_init(void);
void reset_state(void);
void alarm_off(void);


void touch_button_init(){
	
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	
	GPIOA->MODER &=~ (3U<<15*2);
	
	SYSCFG->EXTICR[0] &= SYSCFG_EXTICR1_EXTI0_PA;
	
	EXTI->IMR |= EXTI_IMR_MR0;
	
	EXTI->RTSR |= EXTI_RTSR_TR0;
	
	
__enable_irq(); 
NVIC_SetPriority(EXTI0_IRQn,0); 
NVIC_ClearPendingIRQ(EXTI0_IRQn); 
NVIC_EnableIRQ(EXTI0_IRQn); 	
	
}

void reset_state(){
	
	
}

void alarm_off(){
	
	
}

