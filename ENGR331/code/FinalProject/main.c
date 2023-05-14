#include <stdio.h>
#include <string.h>
#include "stm32f4xx.h"
#include "LCD.h"
#include "stepperMotor.h"
#include "keypad.h"

void wait_for_input(void);

volatile char code[4] = "1111";
volatile char entered_code[4]; //code initially equals 1111 until user picks a code for the first time
volatile int index = 0;
volatile int status = 0;
volatile char last_entered;

int main(void){
	//init_steppermotor();
	LCD_port_init();
	LCD_init(); 
	init_keypad();
	static int failed_attempts = 0;
	LCD_str("Enter Code: ");
	
	while(1){
		//status = 0 when locked
		while(status==0){	
			wait_for_input();
			//code fully entered
			if(index>3){
				for(int i=0; i<4; i++) {
					if(code[i]!=entered_code[i]) { //if there isn't a match stop comparing
						
						//display failed attmpts
						LCD_clear();
						LCD_str("Incorrect Code");
						failed_attempts++;
						//DELAY NEEDED
						place_lcd_cursor_2();
						LCD_str("failed attempts = ");
						LCD_int(failed_attempts);
						
						if(failed_attempts==3) {
							//alarm
						}
						
						//when the user hits any key failed attempts message is replaced with initial enter code prompt
						while(index < 4);
						wait_for_input();
						index = 0;
						LCD_clear();
						LCD_str("Enter Code: ");
						place_lcd_cursor_2();
						break;
						
					}else if(i==3) { //if you get all of the way through and everything matched ulock the safe
						unlock_safe();
						LCD_clear();
						LCD_str("Safe Unlocked ");
						failed_attempts=0; //reset failed attempts
						index = 0;
						status = 1;
					}
				}
			}
		}
		//status = 1 when unlocked
		while(status==1){
			wait_for_input();
			if(last_entered=='*'){ //star is the button to lock the safe when unlocked
				status = 0;
				index = 0;
				LCD_clear();
				LCD_str("Enter Code: ");
				wait_for_input();
				place_lcd_cursor_2();
				//will be switched with push button
			}else if(last_entered=='#'){
				
				failed_attempts=0; //reset failed attempts
				status = 2;
				index = 0;
				LCD_clear();
				LCD_str("Enter New Code:");
				wait_for_input();
				place_lcd_cursor_2();
			}
		}
		//status = 2 when reseting code
		while(status==2){
			wait_for_input();
			if(index==3) {
				place_lcd_cursor_1();
				LCD_str("                           ");
				place_lcd_cursor_1();
				LCD_str("Save Code? (Y=#)");
				wait_for_input();
			}
			if(index>3){
				if(last_entered=='#'){
					for(int i=0; i<4; i++){
						code[i] = entered_code[i];
					}
					index = 0;
					status = 1;
				}else {
					index = 0;
					LCD_clear();
					LCD_str("Enter New Code:");
					place_lcd_cursor_2();
				}
			}
		}
	}
	
}

void wait_for_input() {
	last_entered = wait();
	if(index<4){//only save first 4 entries
		entered_code[index] = last_entered;
	}
	if(status!=1) { //print out last entered value
		char entry = last_entered;
		place_lcd_cursor_2();
		LCD_sendData(entry);
	}
	r_output();
	index++;
	
}

////Interupts for if the key pad gets a button pushed
//void EXTI1_IRQHandler(void) {
//	if ((EXTI->PR & EXTI_PR_PR1) !=0){ 	
//		c_output();
//		last_entered = read_entry_C1();
//		if(index<4){//only save first 4 entries
//			entered_code[index] = last_entered;
//		}
//		if(status!=1) { //print out last entered value
//			LCD_str(last_entered);
//		}
//		r_output();
//		index++;
//	}
//			//Clear the EXTI pending bits before leaving
//		EXTI->PR|=EXTI_PR_PR1;
//		NVIC_ClearPendingIRQ(EXTI1_IRQn);
//}
//void EXTI2_IRQHandler(void) {
//	if ((EXTI->PR & EXTI_PR_PR2) !=0){ 	
//		c_output();
//		last_entered = read_entry_C1();
//		if(index<4){//only save first 4 entries
//			entered_code[index] = last_entered;
//		}
//		if(status!=1) { //print out last entered value
//			LCD_str(last_entered);
//		}
//		r_output();
//		index++;
//	}
//			//Clear the EXTI pending bits before leaving
//		EXTI->PR|=EXTI_PR_PR2; 
//		NVIC_ClearPendingIRQ(EXTI2_IRQn);
//}
//void EXTI4_IRQHandler(void) {
//	if ((EXTI->PR & EXTI_PR_PR4) !=0){ 	
//		c_output();
//		last_entered = read_entry_C1();
//		if(index<4){//only save first 4 entries
//			entered_code[index] = last_entered;
//		}
//		if(status!=1) { //print out last entered value
//			LCD_str(last_entered);
//		}
//		r_output();
//		index++;
//	}
//			//Clear the EXTI pending bits before leaving
//		EXTI->PR|=EXTI_PR_PR4;
//		NVIC_ClearPendingIRQ(EXTI4_IRQn);
//}