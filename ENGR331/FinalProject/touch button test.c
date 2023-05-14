#include <stdio.h>
#include <string.h>
#include "stm32f4xx.h"


#include "stm32f4xx.h"

void touch_button_init(void);
void reset_state(void);
void alarm_off(void);


int main(){
	
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
	
	GPIOD->MODER |= (1<<2*15);
	
		GPIOD->ODR &=~ (3U<<15);
	
	touch_button_init();
	
	while(1);
	
}

void touch_button_init(){
	
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	
	GPIOA->MODER &=~ (3U<<15*2);

	SYSCFG->EXTICR[3] &= SYSCFG_EXTICR4_EXTI15_PA; 
	
EXTI->IMR |= EXTI_IMR_IM15; //Sets up Interrupt Mask Register
EXTI->FTSR |= EXTI_RTSR_TR15; //Sets up Falling Edge Selection Register

__enable_irq(); 
NVIC_SetPriority(EXTI15_10_IRQn,0); 
NVIC_ClearPendingIRQ(EXTI15_10_IRQn); 
NVIC_EnableIRQ(EXTI15_10_IRQn); 
	
	
}

void reset_state(){
	
	
}

void alarm_off(){
	
	
}

void EXTI15_10_IRQHandler(void){
	
	if ((EXTI->PR & EXTI_PR_PR15) !=0){ 	
		GPIOD->ODR |= (1<<15);
	}
	
		EXTI->PR|=EXTI_PR_PR15;
		NVIC_ClearPendingIRQ(EXTI15_10_IRQn);
	
}



