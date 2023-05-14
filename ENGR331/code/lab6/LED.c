#include "LED.h"
#include "stm32f4xx.h"

#define LED_ORANGE 13  
#define LED_GREEN 12
#define LED_RED 14
#define LED_BLUE 15
#define SWITCH 0 


void LED_init(int color){
    RCC->AHB1ENR |= (1<<3); // set bit 3 to 1 (clock for GPIOD)
    GPIOD->MODER |= (1U<<color*2); //set to output
    GPIOD->OTYPER  &=~(1U<<color); //push pull
    GPIOD->OSPEEDR &=~(3U<<color*2); // Ospeed to low
}

void LED_on(int color){
    GPIOD->ODR |= (1<<color); // set LED to 1.
}

void LED_off(int color){
    GPIOD->ODR &= ~(1<<color); // set LED to 0.
}

void LED_toggle(int color){
	GPIOD->ODR ^= (1<<color);
}

