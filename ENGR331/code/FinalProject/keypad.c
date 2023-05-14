#include "stm32f4xx.h"
#include "keypad.h"

static int R1_pin = 5;
static int R2_pin = 6;
static int R3_pin = 8;
static int R4_pin = 9;
static int C1_pin = 4;
static int C2_pin = 2;
static int C3_pin = 13;

void init_keypad() {
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	//enable interupt
	//RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	
	GPIOC->PUPDR |= (2U << R1_pin);
	GPIOC->PUPDR |= (2U << R2_pin);
	GPIOC->PUPDR |= (2U << R3_pin);
	GPIOC->PUPDR |= (2U << R4_pin);
	GPIOC->PUPDR |= (2U << C1_pin);
	GPIOC->PUPDR |= (2U << C2_pin);
	GPIOC->PUPDR |= (2U << C3_pin);
	
	r_output();
	
	//pin C1 for C1	
//	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI1_PC;
//	EXTI->IMR |= EXTI_IMR_MR1;
//	EXTI->RTSR |= EXTI_RTSR_TR1;
//		
//	__enable_irq();
//	NVIC_SetPriority(EXTI1_IRQn,0);
//	NVIC_ClearPendingIRQ(EXTI1_IRQn);
//	NVIC_EnableIRQ(EXTI1_IRQn);	
	
//	//pin C2 for C2	
//	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI2_PC;
//	EXTI->IMR |= EXTI_IMR_MR2;
//	EXTI->RTSR |= EXTI_RTSR_TR2;
//		
//	__enable_irq();
//	NVIC_SetPriority(EXTI2_IRQn,0);
//	NVIC_ClearPendingIRQ(EXTI2_IRQn);
//	NVIC_EnableIRQ(EXTI2_IRQn);	
	
	//pin C3 for C3	
//	SYSCFG->EXTICR[1] |= SYSCFG_EXTICR2_EXTI4_PC;
//	EXTI->IMR |= EXTI_IMR_MR4;
//	EXTI->RTSR |= EXTI_RTSR_TR3;
//		
//	__enable_irq();
//	NVIC_SetPriority(EXTI4_IRQn,0);
//	NVIC_ClearPendingIRQ(EXTI4_IRQn);
//	NVIC_EnableIRQ(EXTI4_IRQn);	
	
}

void c_output(){
		//r pins 0 for odr
	GPIOC->ODR &= ~(1<<R1_pin);
	GPIOC->ODR &= ~(1<<R2_pin);
	GPIOC->ODR &= ~(1<<R3_pin);
	GPIOC->ODR &= ~(1<<R4_pin);
	
	//r pins input
	GPIOC->MODER &= ~(3U<<R1_pin*2); //set to input
	GPIOC->MODER &= ~(3U<<R2_pin*2); //set to input
	GPIOC->MODER &= ~(3U<<R3_pin*2); //set to input
	GPIOC->MODER &= ~(3U<<R4_pin*2); //set to input
	
	//c pins output
	GPIOC->MODER |= (1U<<C1_pin*2); //set to output
	GPIOC->MODER |= (1U<<C2_pin*2); //set to output
	GPIOC->MODER |= (1U<<C3_pin*2); //set to output
	
	//c pins set to high
	GPIOC->ODR |= (1<<C1_pin);
	GPIOC->ODR |= (1<<C2_pin);
	GPIOC->ODR |= (1<<C3_pin);

}

void r_output(){
	//c pins 0 for odr
	GPIOC->ODR &= ~(1<<C1_pin);
	GPIOC->ODR &= ~(1<<C2_pin);
	GPIOC->ODR &= ~(1<<C3_pin);
	
		//c pins input 
	GPIOC->MODER &= ~(3U<<C1_pin*2); //set to input
	GPIOC->MODER &= ~(3U<<C2_pin*2); //set to input
	GPIOC->MODER &= ~(3U<<C3_pin*2); //set to input
	
	//r pins output
	GPIOC->MODER |= (1U<<R1_pin*2); //set to output
	GPIOC->MODER |= (1U<<R2_pin*2); //set to output
	GPIOC->MODER |= (1U<<R3_pin*2); //set to output
	GPIOC->MODER |= (1U<<R4_pin*2); //set to output
		
	//set r pins set to high
	GPIOC->ODR |= (1<<R1_pin);
	GPIOC->ODR |= (1<<R2_pin);
	GPIOC->ODR |= (1<<R3_pin);
	GPIOC->ODR |= (1<<R4_pin);
	
	GPIOC->PUPDR |= (2U >> R1_pin);
	GPIOC->PUPDR |= (2U >> R2_pin);
	GPIOC->PUPDR |= (2U >> R3_pin);
	GPIOC->PUPDR |= (2U >> R4_pin);
	GPIOC->PUPDR |= (2U >> C1_pin);
	GPIOC->PUPDR |= (2U >> C2_pin);
	GPIOC->PUPDR |= (2U >> C3_pin);
}

char read_entry_C1(){
	c_output();
	while(1){
		if(GPIOC->IDR & (1u << R1_pin)) {
			return '1';
		}else if(GPIOC->IDR & (1u << R2_pin)) {
			return '4';
		}else if(GPIOC->IDR & (1u << R3_pin)) {
			return '7';
		}else if(GPIOC->IDR & (1u << R4_pin)) {
			return '*';
			}
		}
}
char read_entry_C2(){
	c_output();
	while(1){
		if(GPIOC->IDR & (1u << R1_pin)) {
			return '2';
		}else if(GPIOC->IDR & (1u << R2_pin)) {
			return '5';
		}else if(GPIOC->IDR & (1u << R3_pin)) {
			return '8';
		}else if(GPIOC->IDR & (1u << R4_pin)) {
			return '0';
			}
		}
}
char read_entry_C3(){
	c_output();
	while(1){
		if(GPIOC->IDR & (1u << R1_pin)) {
			return '3';
		}else if(GPIOC->IDR & (1u << R2_pin)) {
			return '6';
		}else if(GPIOC->IDR & (1u << R3_pin)) {
			return '9';
		}else if(GPIOC->IDR & (1u << R4_pin)) {
			return '#';
			}
		}
}

char wait() {
	r_output();
	while(1) {
		if(GPIOC->IDR & (1u << C1_pin)) {
			return read_entry_C1();
		}else if(GPIOC->IDR & (1u << C2_pin)) {
			return read_entry_C2();
		}else if(GPIOC->IDR & (1u << C3_pin)) {
			return read_entry_C3();
		}
	}
		
}
