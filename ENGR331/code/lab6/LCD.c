#include "LCD.h"
#include "stm32f4xx.h"

#define RW 6
#define RS 7
#define EN 5 
#define DB7 3
#define DB6 2
#define DB5 1
#define DB4 0

void LCD_init() {
	// Enable Port D clock in RCC (bit 3 or AHB1ENR register)
	RCC->AHB1ENR = 0x00000008; //STEP 1: Enable GPIOD in RCC AHB1ENR register
	
	GPIOD->MODER &= ~(3u << DB4*2); 
	GPIOD->MODER &= ~(3u << DB5*2); 
	GPIOD->MODER &= ~(3u << DB6*2); 
	GPIOD->MODER &= ~(3u << DB7*2); 
	GPIOD->MODER &= ~(3u << EN*2); 
	GPIOD->MODER &= ~(3u << RS*2);
	GPIOD->MODER &= ~(3u << RW*2);
	
	GPIOD->MODER |= (1u << DB4*2); 
	GPIOD->MODER |= (1u << DB5*2); 
	GPIOD->MODER |= (1u << DB6*2); 
	GPIOD->MODER |= (1u << DB7*2); 
	GPIOD->MODER |= (1u << EN*2); 
	GPIOD->MODER |= (1u << RS*2);
	GPIOD->MODER |= (1u << RW*2);

	GPIOD->PUPDR &= ~(1u << DB4); 
	GPIOD->PUPDR &= ~(1u << DB5); 
	GPIOD->PUPDR &= ~(1u << DB6); 
	GPIOD->PUPDR &= ~(1u << DB7); 
	GPIOD->PUPDR &= ~(1u << EN); 
	GPIOD->PUPDR &= ~(1u << RS); 
	GPIOD->PUPDR &= ~(1u << RW);
	
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


void split_bits(unsigned int bits){
	unsigned int high;
	unsigned int low;
	
	high = bits&0xf0U;
	high = high/16;
	low = bits&0xfU;
	
	LCD_sendData(high, low);
}
void LCD_sendData(unsigned int high, unsigned int low){
	set_pin(RS);
	clear_pin(RW);
	// high bits
	GPIOD->ODR&=~(0xfU<<DB4); //clear
	GPIOD->ODR|=(high&0xfU<<DB4); //set
	set_pin(EN); clear_pin(EN); //read
	check_BF();

	set_pin(RS);
	clear_pin(RW);	
	//low bits
	GPIOD->ODR&=~(0xfU<<DB4);  //clear
	GPIOD->ODR|=(low&0xfU<<DB4); //set
	set_pin(EN); clear_pin(EN); //read
	check_BF();
}

void LCD_sendInstr(unsigned int high, unsigned int low){
	clear_pin(RS);
	clear_pin(RW);
	// high bits
	GPIOD->ODR&=~(0xfU<<DB4); //clear
	GPIOD->ODR|=(high&0xfU<<DB4); //set
	set_pin(EN); clear_pin(EN); //read
	check_BF();
	
	clear_pin(RS);
	clear_pin(RW);
	//low bits
	GPIOD->ODR&=~(0xfU<<DB4); //clear
	GPIOD->ODR|=(low&0xfU<<DB4); //set
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
	GPIOD->ODR &=~(1U<<pin); // clear bits 0-7
}

void set_pin(int pin){
	GPIOD->ODR |= (1U<<pin);
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


