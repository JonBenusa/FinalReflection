#include "RPG.h"
#include "stm32f4xx.h"
#include "LCD.h"


void RPG_init() {
	RCC->AHB1ENR |= 0x00000008;
	
	GPIOD->MODER &=~(3U<<2*clk);
	GPIOD->MODER &=~(3U<<2*data);	
	
}

int update_bits() {
	int bits = 0;
	if(GPIOD->IDR & (1u << clk)) {
		bits=2;
	}else {
		bits=0;
	}
	if(GPIOD->IDR & (1u << data)){
		bits = bits + 1;
	}
	return bits;
}
char RPG_direction(){
//	int oldBits;
	int newBits;
	static int a_new=0;
	static int b_new=0;
	int a_old;
	int b_old;
	
	a_old = a_new;
	b_old = b_new;
	delay(200);
	newBits = update_bits();
	a_new = bitsToA(newBits);
	b_new = bitsToB(newBits);
	
	
	if(a_old!=a_new && b_old==b_new){
		if(a_new==b_new){
			switch_line(2);
			split_bits('L');
			return 'L';
		}
		if(a_new!=b_new){
			switch_line(2);
			split_bits('R');
			return 'R';
		}
	}
	if(a_old==a_new && b_old!=b_new){
		if(a_new==b_new){
			switch_line(2);
			split_bits('R');
			return 'R';
		}
		if(a_new!=b_new){
			switch_line(2);
			split_bits('L');
			return 'L';
		}
	}
	return ' ';
}

int bitsToA(int bits){
	if(bits==3 || bits==2) {
		return 1;
	}else {
		return 0;
	}
}
int bitsToB(int bits){
	if(bits-2==1 || bits==1) {
		return 1;
	}else {
		return 0;
	}
	
}




