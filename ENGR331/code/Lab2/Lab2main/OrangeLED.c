#include "stm32f4xx.h"                  // Device header


int main(){

// Task Light up Orange LED
// Orange LED = Port D Pin 13
// Enable Port D clock in RCC (bit 3 or AHB1ENR register)
	
RCC->AHB1ENR |= (1<<3); // set bit 3 to 1

// GPIOD set MODER to output (01) on pin 13 (so MODER27, MODER26 t0 01)
	
GPIOD->MODER &=~(3U<<26); // clear bits 27 and 26
GPIOD->MODER |= (1U<<26); //set bit 26 so we have 01 when done

	// Set OTYPER – push/pull : clear bit 13 to 0
	
GPIOD->OTYPER  &=~(1U<<13);
	
// Set OSPEEDR to LOW
	
GPIOD->OSPEEDR &=~(3U<<26); // clear bits 27 and 26
// Write output data to ODR
	
GPIOD->ODR |= (1<<13); // set LED connected to Pin 13 to 1.
	
while(1); // Embedded C never exits main
return 1;
}