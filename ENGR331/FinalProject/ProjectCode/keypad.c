#include "stm32f4xx.h"
#include "keypad.h"

static int R1_pin = 5;
static int R2_pin = 6;
static int R3_pin = 8;
static int R4_pin = 9;
static int C1_pin = 4;
static int C2_pin = 2;
static int C4_pin = 13;
static int delay = 1000;

void init_keypad() {
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	
	GPIOC->PUPDR &= ~(3U << R1_pin);
	GPIOC->PUPDR &= ~(3U << R2_pin);
	GPIOC->PUPDR &= ~(3U << R3_pin);
	GPIOC->PUPDR &= ~(3U << R4_pin);
	GPIOC->PUPDR &= ~(3U << C1_pin);
	GPIOC->PUPDR &= ~(3U << C2_pin);
	GPIOC->PUPDR &= ~(3U << C4_pin);
	
	GPIOC->PUPDR |= (2U << R1_pin*2);
	GPIOC->PUPDR |= (2U << R2_pin*2);
	GPIOC->PUPDR |= (2U << R3_pin*2);
	GPIOC->PUPDR |= (2U << R4_pin*2);
	GPIOC->PUPDR |= (2U << C1_pin*2);
	GPIOC->PUPDR |= (2U << C2_pin*2);
	GPIOC->PUPDR |= (2U << C4_pin*2);
	
	r_output();
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
	GPIOC->MODER &= ~(3U<<C1_pin*2);
	GPIOC->MODER &= ~(3U<<C2_pin*2);
	GPIOC->MODER &= ~(3U<<C4_pin*2);
	GPIOC->MODER |= (1U<<C1_pin*2); //set to output
	GPIOC->MODER |= (1U<<C2_pin*2); //set to output
	GPIOC->MODER |= (1U<<C4_pin*2); //set to output
	
	//c pins set to high
	GPIOC->ODR |= (1<<C1_pin);
	GPIOC->ODR |= (1<<C2_pin);
	GPIOC->ODR |= (1<<C4_pin);

}

void r_output(){
	//c pins 0 for odr
	GPIOC->ODR &= ~(1<<C1_pin);
	GPIOC->ODR &= ~(1<<C2_pin);
	GPIOC->ODR &= ~(1<<C4_pin);
	
		//c pins input 
	GPIOC->MODER &= ~(3U<<C1_pin*2); //set to input
	GPIOC->MODER &= ~(3U<<C2_pin*2); //set to input
	GPIOC->MODER &= ~(3U<<C4_pin*2); //set to input
	
	//r pins output
	GPIOC->MODER &= ~(3U<<R1_pin*2); 
	GPIOC->MODER &= ~(3U<<R2_pin*2);
	GPIOC->MODER &= ~(3U<<R3_pin*2); 
	GPIOC->MODER &= ~(3U<<R4_pin*2);
	GPIOC->MODER |= (1U<<R1_pin*2); //set to output
	GPIOC->MODER |= (1U<<R2_pin*2); //set to output
	GPIOC->MODER |= (1U<<R3_pin*2); //set to output
	GPIOC->MODER |= (1U<<R4_pin*2); //set to output
		
	//set r pins set to high
	GPIOC->ODR |= (1<<R1_pin);
	GPIOC->ODR |= (1<<R2_pin);
	GPIOC->ODR |= (1<<R3_pin);
	GPIOC->ODR |= (1<<R4_pin);
}

char read_entry_C1(){
	c_output();
	for(int i=0; i<delay; i++);
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
	for(int i=0; i<delay; i++);
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
	for(int i=0; i<delay; i++);
	while(1){
		if(GPIOC->IDR & (1u << R1_pin)) {
			return '3';
		}else if(GPIOC->IDR & (1u << R2_pin)) {
			return '6';
		}else if(GPIOC->IDR & (1u << R3_pin) ) {
			return '9';
		}else if(GPIOC->IDR & (1u << R4_pin)) {
			return '#';
			}
		}
}

char wait() {
	r_output();
	for(int i=0; i<delay; i++);
	while(1) {
		if(GPIOC->IDR & (1u << C1_pin)) {
			return read_entry_C1();
		}else if(GPIOC->IDR & (1u << C2_pin)) {
			return read_entry_C2();
		}else if(GPIOC->IDR & (1u << C4_pin)) {
			return read_entry_C3();
		}
	}
		
}
