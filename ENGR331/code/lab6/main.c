#include "stm32f4xx.h"
#include "LCD.h"
#include "LED.h"
#include "RPG.h"
#include "Interupt.h"

void update_LCD_display(void);
void update_power(char rpg_direction);
void stop_motor(void);
void update_motor_power(void);


volatile int power = 0;
static char motor_direction = 'S';

int main(){
	LCD_init();
	LED_init(LED_GREEN);
	LED_init(LED_RED);
	init_user_button(0);
	init_TIM4(100);
	
	update_LCD_display();
	while(1){
		update_power(RPG_direction());
		if(motor_direction=='R') {
			LED_off(LED_RED);
			LED_on(LED_GREEN);
		}else if(motor_direction=='L') {
			LED_off(LED_GREEN);
			LED_on(LED_RED);
		}
	}
}

void stop_motor() {
	power = 0;
	motor_direction = 'S';
	update_LCD_display();
	update_motor_power();
}

void update_motor_power() {
	unsigned int temp;
	temp = power*(TIM4->ARR+1)/100;
	TIM4->CCR4 = temp;
	//TIM4->CCR4 = (unsigned) power*TIM4->ARR/100;
}
 
void update_power(char rpg_direction) {
	if(rpg_direction == 'R') { //if rpg was moved right
		if(motor_direction=='S'){ //if motor was stopped then power equals 10 and direction equals R
			power = 5;
			motor_direction = 'R';
		}else if(motor_direction=='R') { //if motor was moving right add 10 to power if power is less than 100
			if(power<100) {
				power = power + 5;
			}
		}else if(motor_direction=='L') { // if motor was moving left subtract 10 if new power is 0 then direction equals S
			power = power - 5;
			if(power == 0) {
				motor_direction = 'S';
			}
		}
	}else if(rpg_direction == 'L') { //if rpg was moved left
		if(motor_direction=='S'){ //if motor was stopped then power  equals 10 and direction equals L
			power = 5;
			motor_direction = 'L';
		}else if(motor_direction=='R') { // if motor was moving right subtract 10 if new power is 0 then direction equals S
			power = power - 5;
			if(power == 0) {
				motor_direction = 'S';
			}				
		}else if(motor_direction=='L') { //if motor was moving left add 10 to power if power is less than 100
			if(power<100) {
				power = power + 5;
			}
		}
	}
	update_LCD_display();
	update_motor_power();
}


void update_LCD_display() {
	//update line one data
	switch_line(1);
	split_bits('M');
	split_bits('o');
	split_bits('t');
	split_bits('o');
	split_bits('r');
	split_bits(' ');
	split_bits('i');
	split_bits('s');
	split_bits(' ');
	//depends on direction
	if(motor_direction=='S'){
		split_bits('s');
		split_bits('t');
		split_bits('o');
		split_bits('p');
		split_bits('p');
		split_bits('e');
		split_bits('d');
		split_bits(' ');
	}else if(motor_direction=='R'){
		split_bits('f');
		split_bits('o');
		split_bits('r');
		split_bits('w');
		split_bits('a');
		split_bits('r');
		split_bits('d');
		split_bits(' ');
	}else if(motor_direction=='L'){
		split_bits('b');
		split_bits('a');
		split_bits('c');
		split_bits('k');
		split_bits('w');
		split_bits('a');
		split_bits('r');
		split_bits('d');
	}
	
	//enter new data on line 2
	switch_line(2);
	split_bits('P');
	split_bits('o');
	split_bits('w');
	split_bits('e');
	split_bits('r');
	split_bits(' ');
	split_bits('=');
	split_bits(' ');
	intToChar(power);
	split_bits('%');
	split_bits(' ');
	split_bits(' ');
}

void EXTI0_IRQHandler(void){
	if ((EXTI->PR & EXTI_PR_PR0) !=0){ 
		stop_motor();
		EXTI->PR|=EXTI_PR_PR0; 
		NVIC_ClearPendingIRQ(EXTI0_IRQn);
	}
}

