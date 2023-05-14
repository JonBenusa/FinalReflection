#include "stm32f429xx.h"                  // Device header
#include "Library.h"

void Lab1_1(void);
void Lab1_2(void);
void Lab1_3(void);
void upCount(void);
void downCount(void);


static int countDirection = 2;

int main(void){
	//Lab1_1();
	//Lab1_2();
	Lab1_3();
	while(1){
		if(GPIOC->IDR&GPIO_IDR_ID13_Msk) {
			for(int i=0; i<200000; i++);
			if(countDirection==1) {
				countDirection=0;
				change_time_TIM4(32000);
			}else {
				countDirection=1;
				change_time_TIM4(16000);
			}
		}
	}
}
//Lab1_1 specific code
void Lab1_1(){
	LED_init(LED_GREEN);
	LED_on(LED_GREEN);
}
//Lab1_2 specific code
void Lab1_2(){
	//initialize LEDs
	LED_init(LED_GREEN);
	LED_init(LED_BLUE);
	LED_init(LED_RED);
	
	//turn on LED's
	LED_on(LED_GREEN);
	LED_on(LED_BLUE);
	LED_on(LED_RED);
	
	init_TIM3(16000, 0);
}
//Lab1_3 specific code
void Lab1_3(){
	//initialize LEDs
	LED_init(LED_GREEN);
	LED_init(LED_BLUE);
	LED_init(LED_RED);
	
	init_TIM4(16000, 0);
	init_UserButton();
}
void upCount() {
	LED_toggle(LED_GREEN);
	if(~GPIOB->IDR&(1<<LED_GREEN)) {
		LED_toggle(LED_BLUE);
		if(~GPIOB->IDR&(1<<LED_BLUE)) {
			LED_toggle(LED_RED);
		}
	}
}
void downCount() {
	LED_toggle(LED_GREEN);
	if(GPIOB->IDR&(1<<LED_GREEN)) {
		LED_toggle(LED_BLUE);
		if(GPIOB->IDR&(1<<LED_BLUE)) {
			LED_toggle(LED_RED);
		}
	}
}


//Handlers
void TIM4_IRQHandler(void){
	if(TIM4->SR & TIM_SR_UIF){ //we got here because of the timer 3
		if(countDirection==1){
			upCount();
		}else if(countDirection==0){
			downCount();
		}
	}
	TIM4->SR &= ~TIM_SR_UIF; //clear flag
}
void TIM3_IRQHandler(void){
	if(TIM3->SR & TIM_SR_UIF){ //we got here because of the timer 3
		LED_toggle(LED_GREEN);
		LED_toggle(LED_BLUE);
		LED_toggle(LED_RED);
	}
	TIM3->SR &= ~TIM_SR_UIF; //clear flag
}
void EXTI0_IRQHandler(void){		
	LED_toggle(LED_GREEN);
	if(~GPIOB->IDR&(1<<LED_GREEN)) {
		LED_toggle(LED_BLUE);
		if(~GPIOB->IDR&(1<<LED_BLUE)) {
			LED_toggle(LED_RED);
		}
	}
	EXTI->PR|=(1<<SWITCH);
	NVIC_ClearPendingIRQ(EXTI0_IRQn);
}
