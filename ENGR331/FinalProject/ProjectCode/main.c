#include <stdio.h>
#include <string.h>
#include "stm32f4xx.h"
#include "LCD.h"
#include "stepperMotor.h"
#include "keypad.h"
#include "spi.h"
#include "TouchButton.h"

void wait_for_input(void);
void enter_new_code(void);
void alarm(void);
int check_code(void);

volatile char code[4] = "1111";
volatile char entered_code[4]; //code initially equals 1111 until user picks a code for the first time
volatile int index = 0;
volatile int status = 0;
volatile char last_entered;
static int failed_attempts = 0;
static unsigned char x_old;
static unsigned char z_old;
static unsigned char y_old;

int main(void){
	init_steppermotor();
	LCD_port_init();
	LCD_init(); 
	touch_button_init();
	init_keypad();
	SPI_init();
	
	RCC->APB1ENR |= (RCC_APB1ENR_TIM6EN | RCC_APB1ENR_TIM7EN);
	TIM6->PSC = 9999;
	TIM6->ARR = 6400;
	TIM6->CNT = 0;
	TIM6->SR &= ~TIM_SR_UIF;
	TIM6->DIER |= TIM_DIER_UIE;	
	TIM6->CR1 |= TIM_CR1_CEN;		
	__enable_irq();
	NVIC_SetPriority(TIM6_DAC_IRQn, 1);
	NVIC_ClearPendingIRQ(TIM6_DAC_IRQn);
	NVIC_EnableIRQ(TIM6_DAC_IRQn);
	
	x_old = read_position_x();
	y_old = read_position_y();
	z_old = read_position_z();
	
	LCD_str("Enter Code: ");
	
	while(1){
		//status = 0 when locked
		while(status==0){
			if(check_code()==0){ // if the code is entered corretly, unlock the safe
				unlock_safe();
				LCD_clear();
				LCD_str("Safe Unlocked ");
				failed_attempts=0; //reset failed attempts
				index = 0;
				status = 1;
			}else { //show failed atteps and alarm if needed
				//display failed attmpts
				LCD_clear();
				LCD_str("Incorrect Code");
				for(int i=0; i<20000; i++); //delay before showing failed attemps
				LCD_clear();
				place_lcd_cursor_1();
				LCD_str("failed attempts = ");
				place_lcd_cursor_2();
				LCD_int(failed_attempts);
				if(failed_attempts>3) {
					alarm();
				}
			}
		}
		//status = 1 when unlocked
		while(status==1){
			for(int i=0; i<5000000; i++){
				if(GPIOA->IDR & (1U<<15)){
					failed_attempts=0; //reset failed attempts
					status = 2;
					break;
				}
			}
			if(status==2){
				break;
			}
			if(index>3){
				index=0;
			}
			place_lcd_cursor_2();
			LCD_str("Press * to lock");
			wait_for_input();
			if(last_entered=='*'){ //star is the button to lock the safe when unlocked
				status = 0;
				lock_safe();
				//will be switched with push button
			}else if(GPIOA->IDR & (1U<<15)){
				failed_attempts=0; //reset failed attempts
				status = 2;
			}
		}
		//status = 2 when reseting code
		while(status==2){
			enter_new_code();
		}
	}
}

//checks if the code entered was correct will return 0 if correct. will return failed attemps if wrong.
int check_code() {
	index = 0;
	LCD_clear();
	LCD_str("Enter Code: ");
	place_lcd_cursor_2();
	while(index<4){
		wait_for_input();
	}
	if(index!=4){
		return NULL;
	}
	for(int i=0; i<4; i++) {
		if(code[i]!=entered_code[i]) { //if there isn't a match stop comparing
			failed_attempts++;
			return failed_attempts;
		}else if(i==3) { //if you get all of the way through and everything matched ulock the safe
			failed_attempts = 0;
			return failed_attempts;
		}
	}
	return failed_attempts;
}

//changes the code to a new one entered by the user
void enter_new_code(){
	LCD_clear();
	LCD_str("Enter New Code:");
	place_lcd_cursor_2();
	index = 0;
	while(index<4){
		wait_for_input();
	}
	if(index>=4) {
		LCD_clear();
		place_lcd_cursor_1();
		LCD_str("Save Code? (Y=#)");
		wait_for_input();
		if(last_entered=='#'){
			for(int i=0; i<4; i++){
				code[i] = entered_code[i];
			}
			LCD_clear();
			place_lcd_cursor_1();
			LCD_str("New Code Saved");
			last_entered = ' ';
			index = 0;
			LCD_clear();
			LCD_str("Safe Unlocked ");
			status = 1;
		}else {
			index = 0;
			LCD_clear();
			LCD_str("Enter New Code:");
			place_lcd_cursor_2();
			status = 1;
		}
	}
}

//function that the safe will go into when the alarm is triggerd. Needs the correct code to be entered to exit.	
void alarm(){
	int alarm=1;
	while(alarm){
		//print alarm message
		LCD_clear();
		place_lcd_cursor_1();
		LCD_str("ALARM");
		for(int i=0; i<2000; i++);
		
		index = 0;
		while(index<4){
			wait_for_input();
			//print alarm message
			place_lcd_cursor_1();
			LCD_str("ALARM");
			for(int i=0; i<2000; i++);
		}
		for(int i=0; i<4; i++) {
			if(code[i]!=entered_code[i]) { //if there isn't a match stop comparing
				failed_attempts++;
			}else if(i==3) { //if you get all of the way through and everything matched ulock the safe and turn off alarm
				unlock_safe();
				LCD_clear();
				LCD_str("Safe Unlocked ");
				failed_attempts=0; //reset failed attempts
				index = 0;
				status = 1;
				alarm=0;
			}
		}
	}
}	

//helper method that is called whenever the safe is waiting on the user to enter a value with the keypad
void wait_for_input() {
	
	last_entered = wait();
	if(index<4){//only save first 4 entries
		entered_code[index] = last_entered;
	}
	if(status!=1) { //print out last entered value
		place_lcd_cursor_2();
		if(index<4){
			for(int i=0; i<=index; i++){
				LCD_sendData(entered_code[i]);
			}
		}
	}
	r_output();
	index++;
	
}

//spi gets checked on a timer interrupt
void TIM6_DAC_IRQHandler(void){

	if(TIM6->SR & TIM_SR_UIF){ //we got here because of the timer 6
		if(x_old!=read_position_x() || y_old!=read_position_y() || z_old!=read_position_z()){
			if(status==0){
				alarm();
			}
			x_old = read_position_x();
			y_old = read_position_y();
			z_old = read_position_z();
		}
	}
			TIM6->SR &= ~TIM_SR_UIF; //clear flag
}

