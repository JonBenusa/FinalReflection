#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_hal.h" 

int main(){
	int x = 0;
	// Task Light up Orange Green, Red, and Blue LEDs Only when blue button is pushed
	// LEDs = Port D Pin 13, Pin 12, Pin 14, and Pin 15 
	// Button = Port A Pin 0	
	// Enable Port D clock in RCC (bit 3 or AHB1ENR register)
	HAL_Init();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin = GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		
	RCC->AHB1ENR |= (1<<3); // set bit 3 to 1
	RCC->AHB1ENR |= (1<<0); // set bit 3 to 1	

	// GPIOD set MODER to output (01) on pins 
	GPIOD->MODER &=~(3U<<31); // clear bits 24 to 31
	GPIOD->MODER |= (1U<<26); //set bit 26 so we have 01 when done
	GPIOD->MODER |= (1U<<24); //set bit 24 so we have 01 when done
	GPIOD->MODER |= (1U<<28); //set bit 28 so we have 01 when done
	GPIOD->MODER |= (1U<<30); //set bit 30 so we have 01 when done
	//GPIOD set MODER to input (00) on pin 0
	GPIOA->MODER &=~(3U<<1); // clear bits 24 to 31

		// Set OTYPER – push/pull : clear bit 13 to 0
		
	GPIOD->OTYPER  &=~(1U<<13);
	GPIOD->OTYPER  &=~(1U<<12);
	GPIOD->OTYPER  &=~(1U<<14);
	GPIOD->OTYPER  &=~(1U<<15);
		
	// Set OSPEEDR to LOW
		
	GPIOD->OSPEEDR &=~(3U<<26); // clear bits 27 and 26
	GPIOD->OSPEEDR &=~(3U<<24); // clear bits 27 and 26
	GPIOD->OSPEEDR &=~(3U<<28); // clear bits 27 and 26
	GPIOD->OSPEEDR &=~(3U<<30); // clear bits 27 and 26
	// Write output data to ODR

	while(1) { // Embedded C never exits main
		if((GPIOA->IDR & (1<<0))) {
			x++;
		}
		while(x%2==0 && (GPIOA->IDR & (1<<0))==0) {
				GPIOD->ODR |= (1<<13); // Turn on LED
				HAL_Delay(10);
				GPIOD->ODR &=~(1U<<13); // Turn off LED
				GPIOD->ODR |= (1<<12); // Turn on LED
				HAL_Delay(10);
				GPIOD->ODR &=~(1U<<12); // Turn off LED
				GPIOD->ODR |= (1<<14); // Turn on LED
				HAL_Delay(10);
				GPIOD->ODR &=~(1U<<14); // Turn off LED
				GPIOD->ODR |= (1<<15); // Turn on LED
				HAL_Delay(10);
				GPIOD->ODR &=~(1U<<15); // Turn off LED
		}
	}
}