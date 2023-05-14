#include "stm32f4xx.h"                  // Device header
#include "LCD.h"
#include "RPG.h"

int main(){
	
	LCD_init();
	RPG_init();


//top line 
	split_bits('D');
	split_bits('I');
	split_bits('R');
	split_bits('=');
	switch_line(2);
	
//check to see direction and display
	
	while(1){
		RPG_direction();
	}		
}
