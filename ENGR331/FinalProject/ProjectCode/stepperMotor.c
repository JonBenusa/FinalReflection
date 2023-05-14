#include <stdio.h>
#include <string.h>
#include "stm32f4xx.h"
#include "LCD.h"
#include "stepperMotor.h"


void motor_delay(){
	int x=0;
	for(x=0; x<2000; x++);
}

void init_steppermotor(){
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	GPIOB->MODER &= ~(GPIO_MODER_MODER11 | GPIO_MODER_MODER12 | GPIO_MODER_MODER13 | GPIO_MODER_MODER14);
	GPIOB->MODER |= (GPIO_MODER_MODER11_0 | GPIO_MODER_MODER12_0 | GPIO_MODER_MODER13_0 | GPIO_MODER_MODER14_0);
	GPIOB->OTYPER &= ~(GPIO_OTYPER_OT11_Msk | GPIO_OTYPER_OT12_Msk | GPIO_OTYPER_OT13_Msk | GPIO_OTYPER_OT14_Msk);

	// To have it lock by default the motor is off
	GPIOB->ODR &= ~(GPIO_ODR_OD11 | GPIO_ODR_OD12 | GPIO_ODR_OD13 | GPIO_ODR_OD14);
}

// this is a full 360 degree rotation with 45 degree steps
// we can modify this depending on how much we need to turn the lock to unlock it
// the delay probably isn't necessary, I added it just to be safe
void unlock_safe(){
	int turn1 =0;
	for(turn1=0; turn1<150; turn1++){
	GPIOB->ODR |= (GPIO_ODR_OD11);
	motor_delay();
	GPIOB->ODR |= (GPIO_ODR_OD12);
	motor_delay();
	GPIOB->ODR &= ~(GPIO_ODR_OD11);
	motor_delay();
	GPIOB->ODR |= (GPIO_ODR_OD13);
	motor_delay();
	GPIOB->ODR &= ~(GPIO_ODR_OD12);
	motor_delay();
	GPIOB->ODR |= (GPIO_ODR_OD14);
	motor_delay();
	GPIOB->ODR &= ~(GPIO_ODR_OD13);
	motor_delay();
	GPIOB->ODR |= (GPIO_ODR_OD11);
	motor_delay();
	GPIOB->ODR &= ~(GPIO_ODR_OD14);
	GPIOB->ODR &= ~(GPIO_ODR_OD11 | GPIO_ODR_OD12 | GPIO_ODR_OD13 | GPIO_ODR_OD14);
	}
}	

// this is a full 360 in the other direction to lock the safe once 
// it has been opened, again we can change how much it rotates depending 
// on how much we need the motor to turn to re-lock the safe
void lock_safe(){
	int turn2 =0;
	for(turn2=0; turn2<150; turn2++){
	GPIOB->ODR |= (GPIO_ODR_OD11);
	motor_delay();
	GPIOB->ODR |= (GPIO_ODR_OD14);
	motor_delay();
	GPIOB->ODR &= ~(GPIO_ODR_OD11);
	motor_delay();
	GPIOB->ODR |= (GPIO_ODR_OD13);	
	motor_delay();	
	GPIOB->ODR &= ~(GPIO_ODR_OD14);	
	motor_delay();
	GPIOB->ODR |= (GPIO_ODR_OD12);
	motor_delay();
	GPIOB->ODR &= ~(GPIO_ODR_OD13);
	motor_delay();
	GPIOB->ODR |= (GPIO_ODR_OD11);
	motor_delay();
	GPIOB->ODR &= ~(GPIO_ODR_OD12);
	motor_delay();
	GPIOB->ODR &= ~(GPIO_ODR_OD11 | GPIO_ODR_OD12 | GPIO_ODR_OD13 | GPIO_ODR_OD14);
	}
}
	