// ENGR 331 Class Exercise: Timers
// Name: Jonathan Benusa
// Date: 10/7/2022
// Goal: Use Timer interrupts
// Requirements:
// 1. a)Calculate PRESCALAR and Auto-reload register values for Timer 6
//		Timer 6 should interrupt Every 1 second.
//	  b) Initialize GPIOs and Timer 6.
//    c) Complete Appropriate Interrupt Service Routine.

// Complete Timer 6 interrupt requirement before starting Timer 7
		
// 2. Calculate PRESCALAR and Auto-reload register values for Timer 7
//		Timer 7 should interrupt Every 5 seconds.

#include "stm32f4xx.h"                  // Device header
#include "LED.h"
#include "time.h"
//=============================================================================
// LEDs and Switches in the Board
//=============================================================================
//USER LEDs are in PortD
#define LED_ORANGE 13  
#define LED_GREEN 12
#define LED_RED 14
#define LED_BLUE 15
#define SWITCH 0 //PortA Pin0 -- default pull-down resistor

//=============================================================================
// main function
//=============================================================================

// add your code below..
int main(void)
{
//Initialize LEDs
//==========================================
	LED_init(LED_ORANGE);
	LED_init(LED_GREEN);
	LED_init(LED_RED);
	LED_init(LED_BLUE);

// Open Chapter 20 - Basic Timers (TIM6&TIM7)
// Set up all TIMER 6 registers to meet the 1 second goal
//=======================================================
	RCC->APB1ENR |= (RCC_APB1ENR_TIM6EN | RCC_APB1ENR_TIM7EN);
	
	TIM6->PSC = 999;
	TIM6->ARR = 16000000-1;
	TIM6->CNT = 0;
	TIM6->SR &= ~TIM_SR_UIF;
	TIM6->DIER |= TIM_DIER_UIE;	
	TIM6->CR1 |= TIM_CR1_CEN;	
	
	TIM7->PSC = 999;
	TIM7->ARR = 80000000-1;
	TIM7->CNT = 0;
	TIM7->SR &= ~TIM_SR_UIF;
	TIM7->DIER |= TIM_DIER_UIE;	
	TIM7->CR1 |= TIM_CR1_CEN;	
	
	
// Let CMSIS take care of NVIC interrupt regs
//=======================================================
	__enable_irq();
	NVIC_SetPriority(TIM6_DAC_IRQn, 0);
	NVIC_ClearPendingIRQ(TIM6_DAC_IRQn);
	NVIC_EnableIRQ(TIM6_DAC_IRQn);
	
	__enable_irq();
	NVIC_SetPriority(TIM7_IRQn, 0);
	NVIC_ClearPendingIRQ(TIM7_IRQn);
	NVIC_EnableIRQ(TIM7_IRQn);


// Done with NVIC
// do nothing... wait to be interrupted
while (1) {}
}

//=============================================================================
// TIM6 Interrupt Handler
//=============================================================================
// Add code for your Timer 6 handler here
// Set BLUE LED to toggle every time Timer 6 interrupt handler is entered
void TIM6_DAC_IRQHandler(){
	if(TIM6->SR & TIM_SR_UIF){ //we got here because of the timer 6
		LED_toggle(LED_BLUE);
		TIM6->SR &= ~TIM_SR_UIF; //clear flag
	}
}


//=============================================================================
// TIM7 Interrupt Handler
//=============================================================================
// Add code for your Timer 7 handler here
// Set GREEN LED to toggle every time Timer 7 interrupt handler is entered

void TIM7_IRQHandler(){
	if(TIM7->SR & TIM_SR_UIF){ //we got here because of the timer 7
		LED_toggle(LED_GREEN);
		TIM7->SR &= ~TIM_SR_UIF; //clear flag
	}
}


//=============================================================================
// End of file
//=============================================================================
