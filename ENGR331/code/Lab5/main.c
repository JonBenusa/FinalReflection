void print_value(int count);

#include "stm32f4xx.h"
#include "LCD.h"
#include "LED.h"
#include "Pin.h"
#include "Time.h"

int main(){
	init_TIM6(800, 1);
	LCD_init();
	LED_init(LED_BLUE);
	init_user_button(0);
	
	
	switch_line(1);
	split_bits('B');
	split_bits('L');
	split_bits('U');
	split_bits('E');
	split_bits(' ');
	split_bits('L');
	split_bits('E');
	split_bits('D');
	split_bits(' ');
	split_bits('B');
	split_bits('L');
	split_bits('I');
	split_bits('N');
	split_bits('K');
	split_bits('S');
	
	switch_line(2);
	split_bits('E');
	split_bits('V');
	split_bits('E');
	split_bits('R');
	split_bits('Y');
	split_bits(' ');
	split_bits('0');
	split_bits('.');
	split_bits('5');
	split_bits(' ');
	split_bits(' ');
	split_bits('s');
	split_bits('e');
	split_bits('c');

	
	while(1){

	}
}

void TIM6_DAC_IRQHandler(void){
	if(TIM6->SR & TIM_SR_UIF){ //we got here because of the timer 6
		LED_toggle(LED_BLUE); //toggle blue led
	}
			TIM6->SR &= ~TIM_SR_UIF; //clear flag
}

void EXTI0_IRQHandler(void){
	int count = (int) TIM6->ARR;
	if ((EXTI->PR & EXTI_PR_PR0) !=0){ 
		//find new count value	
		if (count<=19200) {
			count = count + 800;
		} else {
			count = 800;	
		}
		//update lcd and timer count

		change_time_TIM6((uint16_t)count);
		print_value(count);
			//Clear the EXTI pending bits before leaving
		EXTI->PR|=EXTI_PR_PR0; 
		NVIC_ClearPendingIRQ(EXTI0_IRQn);
	}
}
void print_value(int count) {
	int half_seconds = count/800;
	int seconds = half_seconds/2;
	
	switch_line(2);
	place_LCD_cursor(6);
	intToChar(seconds);
	split_bits('.');
	if(half_seconds%2>0) {
		split_bits('5');
	}else {
		split_bits('0');
	}
}	

