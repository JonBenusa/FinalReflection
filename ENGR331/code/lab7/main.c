#include "stm32f4xx.h"
#include "LCD.h"
#include "LED.h"
#include "RPG.h"
#include "Interupt.h"

void update_LCD_display(void);
void update_power(void);
void stop_motor(void);


static int distance = 0;
static char motor_direction = 'S';

int main(){
	LCD_init();
	LED_init(LED_GREEN);
	LED_init(LED_RED);
	init_user_button(0);
	init_TIM4(0);
	init_input_capture();
	init_TIM7(1000, 1);
	update_LCD_display();
	while(1){
		
		if(motor_direction=='R') {
			LED_off(LED_RED);
			LED_on(LED_GREEN);
		}
	}
}

void stop_motor() {
	motor_direction = 'S';
	update_LCD_display();
}
 
void update_power() {
	//if far go faster
	if(distance>5){ 
		TIM4->CCR4 = 75*(TIM4->ARR)/100;
	}else {
	//if close go slower
		TIM4->CCR4 = 25*(TIM4->ARR)/100;
	}
	update_LCD_display();
}

void TIM3_IRQHandler(void){
	if(TIM3->SR & TIM_SR_CC1IF) { //channel 1
		distance = (int)(TIM3->CCR1)/148;
		update_power();
	}else if(TIM3->SR & TIM_SR_CC1OF) { //if second interupt on the same channel was recieved before the first interupt had bit cleared
		
	}
}

void update_LCD_display() {
	//update line one data
	switch_line(1);
	split_bits('D');
	split_bits('i');
	split_bits('s');
	split_bits('t');
	split_bits('a');
	split_bits('n');
	split_bits('c');
	split_bits('e');
	split_bits(':');
	split_bits(' ');

	//enter new data on line 2
	switch_line(2);
	intToChar(distance);
}

void EXTI0_IRQHandler(void){
	if ((EXTI->PR & EXTI_PR_PR0) !=0){ 
		stop_motor();
		EXTI->PR|=EXTI_PR_PR0; 
		NVIC_ClearPendingIRQ(EXTI0_IRQn);
	}
}
