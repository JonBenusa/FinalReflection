#include "stm32f4xx.h"                  // Device header
#include "LCD.h"
#include "Pin.h"

int main(){
	int sum;
	
	LCD_init();
	//place_LCD_cursor(1);
	
	
	//write H
	//split_bits('H');
		
	//write Hello ENGR331 Class 
	split_bits('H');
	split_bits('E');
	split_bits('L');
	split_bits('L');
	split_bits('0');
	switch_line(2);
	
	
	split_bits('E');
	split_bits('N');
	split_bits('G');
	split_bits('R');
	split_bits('3');
	split_bits('3');
	split_bits('1');
	split_bits(' ');
	split_bits('C');
	split_bits('L');
	split_bits('A');
	split_bits('S');
	split_bits('S');


//sum to LCD
//	 sum = 10;
//	 for(int i=1; i<10; i++) {
//		 sum = sum + 5;
//	 }
//	 
//	split_bits('S');
//	split_bits('U');
//	split_bits('M');
//	split_bits('=');
//	place_LCD_cursor(36);
//	intToChar(sum);

//Sum of Float To LCD
//	split_bits('S');
//	split_bits('U');
//	split_bits('M');
//	split_bits('=');
//	place_LCD_cursor(36);
//	
//	floatToLCD(1.324+12.9);
	
	while(1);
	
}
