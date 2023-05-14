#include "Pin.h"
#include "stm32f4xx.h" 
#include "LCD.h"

#define RW 6
#define RS 7
#define EN 5 
#define DB7 3
#define DB6 2
#define DB5 1
#define DB4 0

void clear_pin(int pin){
	GPIOD->ODR &=~(1U<<pin); // clear bits 0-7
}

void set_pin(int pin){
	GPIOD->ODR |= (1U<<pin);
}

void check_BF(void){
	set_pin(RW);
	clear_pin(RS);
	GPIOD->MODER &=~(3U<<DB7*2);
	set_pin(EN);
	while(GPIOD->IDR & (1<<DB7)) {
		
	}
	clear_pin(EN);
	GPIOD->MODER &=~(3U<<DB7*2);
	GPIOD->MODER |=(1U<<DB7*2);
	clear_pin(RW);
}
