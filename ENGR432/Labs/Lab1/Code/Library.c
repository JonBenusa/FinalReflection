#include "Library.h"
#include "stm32f429xx.h"

 
#define SWITCH 0 //PortA Pin0 -- default pull-down resistor

//LED Controls
void LED_init(int color){
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN; // (clock for GPIOB)
    GPIOB->MODER |= (1U<<color*2); //set to output
    GPIOB->OTYPER  &=~(1U<<color); //push pull
    GPIOB->OSPEEDR &=~(3U<<color*2); // Ospeed to low
}

void LED_on(int color){
    GPIOB->ODR |= (1<<color); // set LED to 1.
}

void LED_off(int color){
    GPIOB->ODR &= ~(1<<color); // set LED to 0.
}

void LED_toggle(int color){
	GPIOB->ODR ^= (1<<color);
}

//Timers
void init_TIM3(uint32_t count, int importance) {
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	RCC->APB1ENR |= (RCC_APB1ENR_TIM3EN);
	
	TIM3->PSC = 999;
	TIM3->ARR = count-1;
	TIM3->CNT = 0;
	TIM3->SR &= ~TIM_SR_UIF;
	TIM3->DIER |= TIM_DIER_UIE;	
	TIM3->CR1 |= TIM_CR1_CEN;		
	
	__enable_irq();
	NVIC_SetPriority(TIM3_IRQn, importance);
	NVIC_ClearPendingIRQ(TIM3_IRQn);
	NVIC_EnableIRQ(TIM3_IRQn);
}

void change_time_TIM3(uint32_t count){
	TIM3->CNT = 0;
	TIM3->ARR = count-1;
}

void init_TIM4(uint32_t count, int importance) {
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	RCC->APB1ENR |= (RCC_APB1ENR_TIM4EN);
	
	TIM4->PSC = 999;
	TIM4->ARR = count-1;
	TIM4->CNT = 0;
	TIM4->SR &= ~TIM_SR_UIF;
	TIM4->DIER |= TIM_DIER_UIE;	
	TIM4->CR1 |= TIM_CR1_CEN;		
	
	__enable_irq();
	NVIC_SetPriority(TIM4_IRQn, importance);
	NVIC_ClearPendingIRQ(TIM4_IRQn);
	NVIC_EnableIRQ(TIM4_IRQn);
}
void change_time_TIM4(uint32_t count){
	TIM4->CNT = 0;
	TIM4->ARR = count-1;
}
//SysTick interupt setup
void init_SysTick(uint32_t count, int importance) {
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	RCC->APB1ENR |= (RCC_APB1ENR_TIM3EN);
	
	SysTick->LOAD &= ~(0x00FFFFFFU<<SysTick_LOAD_RELOAD_Pos);
	SysTick->LOAD |= (count<<SysTick_LOAD_RELOAD_Pos);
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;		//ENABLE the timer
	
	__enable_irq();
	NVIC_SetPriority(TIM3_IRQn, importance);
	NVIC_ClearPendingIRQ(TIM3_IRQn);
	NVIC_EnableIRQ(TIM3_IRQn);
}
//Interrupts
void init_UserButton(){
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOCEN;
	
	GPIOC->MODER &= ~GPIO_MODER_MODE13_Msk;
	
	SYSCFG->EXTICR[1] &= SYSCFG_EXTICR1_EXTI0_PC;			//EXTICR1_EXTI0_PA; //and because we want to clear all other
	EXTI->IMR |= EXTI_IMR_IM13;//Interrupt Mask
	EXTI->RTSR|= EXTI_RTSR_TR13;//Rising trigger selection
	
	

	__enable_irq();
	NVIC_SetPriority(EXTI0_IRQn,0);
	NVIC_ClearPendingIRQ(EXTI0_IRQn);
	NVIC_EnableIRQ(EXTI0_IRQn);
}


