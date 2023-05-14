#include "LCD.h"
#include "stm32f4xx.h"

define VSS 11
define VDD 10
define V0 15
define RS 14
define RW 12
define EN 10

define DB4 14 
define DB5 15
define DB6 13
define DB7 14
define K 11
define A 9

void LCD_init() {
	// Enable Port D clock in RCC (bit 3 or AHB1ENR register)
	RCC->AHB1ENR = 0x00000008; //STEP 1: Enable GPIOD in RCC AHB1ENR register
	
	GPIOG->MODER &= ~(3u << DB4*2); 
	GPIOF->MODER &= ~(3u << DB5*2); 
	GPIOE->MODER &= ~(3u << DB6*2); 
	GPIOF->MODER &= ~(3u << DB7*2); 
	GPIOE->MODER &= ~(3u << EN*2); 
	GPIOE->MODER &= ~(3u << RS*2);
	GPIOE->MODER &= ~(3u << RW*2);
	GPIOB->MODER &= ~(3u << VSS*2);
	GPIOB->MODER &= ~(3u << VDD*2);
	GPIOE->MODER &= ~(3u << V0*2);
	GPIOE->MODER &= ~(3u << K*2);
	GPIOE->MODER &= ~(3u << A*2);
	
	GPIOG->MODER |= (1u << DB4*2); 
	GPIOF->MODER |= (1u << DB5*2); 
	GPIOE->MODER |= (1u << DB6*2); 
	GPIOF->MODER |= (1u << DB7*2); 
	GPIOE->MODER |= (1u << EN*2); 
	GPIOE->MODER |= (1u << RS*2);
	GPIOE->MODER |= (1u << RW*2);
	GPIOB->MODER |= (1u << VSS*2);
	GPIOB->MODER |= (1u << VDD*2);
	GPIOE->MODER |= (1u << V0*2);
	GPIOE->MODER |= (1u << A*2);
	GPIOE->MODER |= (1u << K*2);

	GPIOG->PUPDR &= ~(1u << DB4); 
	GPIOF->PUPDR &= ~(1u << DB5); 
	GPIOE->PUPDR &= ~(1u << DB6); 
	GPIOF->PUPDR &= ~(1u << DB7); 
	GPIOE->PUPDR &= ~(1u << EN); 
	GPIOE->PUPDR &= ~(1u << RS); 
	GPIOE->PUPDR &= ~(1u << RW);
	GPIOB->PUPDR &= ~(1u << VSS);
	GPIOB->PUPDR &= ~(1u << VDD);
	GPIOE->PUPDR &= ~(1u << V0);
	GPIOE->PUPDR &= ~(1u << A);
	GPIOE->PUPDR &= ~(1u << K);
	
	
	//turn on the LCD
	set_pin(A);
	set_pin(K);
	GPIOD->ODR |= (1u << VSS);
	
	
	//initialize
	clear_pin(RW);
	clear_pin(RS);
	check_BF();
	
	LCD_sendInstr(3,3);
	LCD_sendInstr(3,2);
	
	
	LCD_sendInstr(0x2,0x8);
	LCD_sendInstr(0x0,0x8);
	LCD_sendInstr(0x0,0x1);
	LCD_sendInstr(0x0,0x6);
	LCD_sendInstr(0x0,0xf);

	
}


void LCD_sendData(unsigned int bits){
	unsigned int high;
	unsigned int low;
	
	high = bits&0xf0U;
	high = high/16;
	low = bits&0xfU;
	
	set_pin(RS);
	clear_pin(RW);
	// high bits
	GPIOG->ODR&=~(0x1U<<DB4); //clear
	GPIOF->ODR&=~(0x1U<<DB5); //clear
	GPIOE->ODR&=~(0x1U<<DB6); //clear
	GPIOF->ODR&=~(0x1U<<DB7); //clear
	
	GPIOG->ODR|=(high&0x1U<<DB4); //set
	GPIOF->ODR|=(high&0x2U<<DB5-1); //set
	GPIOE->ODR|=(high&0x4U<<DB6-2); //set
	GPIOF->ODR|=(high&0x8U<<DB7-3); //set
	
	set_pin(EN); clear_pin(EN); //read
	check_BF();

	set_pin(RS);
	clear_pin(RW);
	// high bits
	GPIOG->ODR&=~(0x1U<<DB4); //clear
	GPIOF->ODR&=~(0x1U<<DB5); //clear
	GPIOE->ODR&=~(0x1U<<DB6); //clear
	GPIOF->ODR&=~(0x1U<<DB7); //clear
	
	GPIOG->ODR|=(low&0x1U<<DB4); //set
	GPIOF->ODR|=(low&0x2U<<DB5-1); //set
	GPIOE->ODR|=(low&0x4U<<DB6-2); //set
	GPIOF->ODR|=(low&0x8U<<DB7-3); //set
	
	set_pin(EN); clear_pin(EN); //read
	check_BF();
}

void LCD_sendInstr(unsigned int high, unsigned int low){
	clear_pin(RS);
	clear_pin(RW);
	// high bits
	GPIOG->ODR&=~(0x1U<<DB4); //clear
	GPIOF->ODR&=~(0x1U<<DB5); //clear
	GPIOE->ODR&=~(0x1U<<DB6); //clear
	GPIOF->ODR&=~(0x1U<<DB7); //clear
	
	GPIOG->ODR|=(high&0x1U<<DB4); //set
	GPIOF->ODR|=(high&0x2U<<DB5-1); //set
	GPIOE->ODR|=(high&0x4U<<DB6-2); //set
	GPIOF->ODR|=(high&0x8U<<DB7-3); //set
	
	set_pin(EN); clear_pin(EN); //read
	check_BF();

	clear_pin(RS);
	clear_pin(RW);
	// high bits
	GPIOG->ODR&=~(0x1U<<DB4); //clear
	GPIOF->ODR&=~(0x1U<<DB5); //clear
	GPIOE->ODR&=~(0x1U<<DB6); //clear
	GPIOF->ODR&=~(0x1U<<DB7); //clear
	
	GPIOG->ODR|=(low&0x1U<<DB4); //set
	GPIOF->ODR|=(low&0x2U<<DB5-1); //set
	GPIOE->ODR|=(low&0x4U<<DB6-2); //set
	GPIOF->ODR|=(low&0x8U<<DB7-3); //set
	
	set_pin(EN); clear_pin(EN); //read
	check_BF();
}
void place_LCD_cursor(int num){
	clear_pin(RS);
	while(num>0) {
		LCD_sendInstr(0x1U, 0x6U);
		num--;
	}
}

void switch_line(int line) {
		if(line == 2){
			LCD_sendInstr(0xc, 0);
		}else if(line == 1){
			LCD_sendInstr(0xc, 0);
			place_LCD_cursor(40);
		}			
}

//delay 6000 for about 1 sec
void delay(int time){
	while(time>=0) {
		time = time - 1;
	}
}

void intToChar(int num){
	char character;
	character = num%10 +'0';
	num = num /10;
	if(num!=0) {
		intToChar(num);
	}
	split_bits(character); 
	
	
}

void doubleToLCD(double num, int sigfig) {
	int integer = num;
	intToChar(integer);
	
	split_bits('.');
	
	num = num - integer;
	for(int i=0; i<sigfig && num>0; i++) {
		num = num * 10;
		integer = num;
		split_bits(integer+'0');
		num = num - integer;
	}
}

void clear_pin(int pin){
	GPIOE->ODR&=~(0x1U<<pin); //clear
}

void set_pin(int pin){
	GPIOE->ODR|=(0x1U<<pin); //clear
}

void check_BF(void){
	set_pin(RW);
	clear_pin(RS);
	GPIOD->MODER &=~(3U<<DB7*2);
	set_pin(EN);
	while(GPIOD->IDR & (1<<DB7)) {
		
	}
	clear_pin(EN);
	GPIOD->MODER &=~(3U<<DB7*2);
	GPIOD->MODER |=(1U<<DB7*2);
	clear_pin(RW);
}


