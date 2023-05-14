#include "stm32f4xx.h"                  

static void initializeLED(char color){
	// Task Light up Orange Green, Red, and Blue alternating. 
	// Stop when the button is pushed. Start when pushed again
	// LEDs = Port D Pin 13, Pin 12, Pin 14, and Pin 15 	
	// Enable Port D clock in RCC (bit 3 or AHB1ENR register)
		
	RCC->AHB1ENR |= (1<<3); // set bit 3 to 1
	
	//initialize orange led
	if(color == 'O') {
		GPIOD->MODER &=~(3U<<26); // clear bits 26 to 27
		// GPIOD set MODER to output (01) on pins 
		GPIOD->MODER |= (1U<<26); //set bit 26 so we have 01 when done
		GPIOD->OTYPER  &=~(1U<<13);
		GPIOD->OSPEEDR &=~(3U<<26); // clear bits 27 and 26
	}
	
	//initialize green led
	if(color == 'G') {
		GPIOD->MODER &=~(3U<<24); // clear bits 24 to 25
		// GPIOD set MODER to output (01) on pins 
		GPIOD->MODER |= (1U<<24); //set bit 24 so we have 01 when done
		GPIOD->OTYPER  &=~(1U<<12);
		GPIOD->OSPEEDR &=~(3U<<24); // clear bits 25 and 24
	}
	
	//initialize red led
	if(color == 'R') {
		GPIOD->MODER &=~(3U<<28); // clear bits 28 to 29
		// GPIOD set MODER to output (01) on pins 
		GPIOD->MODER |= (1U<<28); //set bit 28 so we have 01 when done
		GPIOD->OTYPER  &=~(1U<<14);
		GPIOD->OSPEEDR &=~(3U<<28); // clear bits 28 and 29
	}
	
	//initialize blue led
	if(color == 'B') {
		GPIOD->MODER &=~(3U<<30); // clear bits 30 to 31
		// GPIOD set MODER to output (01) on pins 
		GPIOD->MODER |= (1U<<30); //set bit 30 so we have 01 when done
		GPIOD->OTYPER  &=~(1U<<15);
		GPIOD->OSPEEDR &=~(3U<<30); // clear bits 30 and 31
	}
}