#include "stm32f4xx.h" 
#include <string.h>
#include "LCD.h" 
#include <stdio.h>

void LCD_port_init(){
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN; 
	GPIOD->MODER &= ~(GPIO_MODER_MODER7_Msk | GPIO_MODER_MODER6_Msk | GPIO_MODER_MODER5_Msk | GPIO_MODER_MODER3_Msk | GPIO_MODER_MODER2_Msk | GPIO_MODER_MODER1_Msk | GPIO_MODER_MODER0_Msk);
	GPIOD->MODER |= (GPIO_MODER_MODER7_0 | GPIO_MODER_MODER6_0 | GPIO_MODER_MODER5_0 | GPIO_MODER_MODER3_0 | GPIO_MODER_MODER2_0 | GPIO_MODER_MODER1_0 | GPIO_MODER_MODER0_0);

	GPIOD->OTYPER &=~(GPIO_OTYPER_OT7_Msk | GPIO_OTYPER_OT6_Msk | GPIO_OTYPER_OT5_Msk | GPIO_OTYPER_OT3_Msk | GPIO_OTYPER_OT2_Msk | GPIO_OTYPER_OT1_Msk | GPIO_OTYPER_OT0_Msk);
}

void delay(){
	int x=0;
	for(x=0; x<150000; x++);
}

void delay_short(){
	int x=0;
	for(x=0; x<100000; x++);
}

void send_four(uint8_t shift){
	clear_PIN(RS);
	clear_PIN(RW);
	set_PIN(EN);
	GPIOD->ODR &= ~(0xFU<<DB4);
	GPIOD->ODR |= ((shift&0xFU)<<DB4);
	clear_PIN(EN);
	delay(); 
}

void LCD_init(){
	clear_PIN(RS);
	send_four(0x03);
	send_four(0x03);
	send_four(0x03);
	send_four(0x02);
	send_four(0x02);
	send_four(0x08);
	send_four(0x00);
	send_four(0x08);
	send_four(0x00);
	send_four(0x01);
	send_four(0x00);
	send_four(0x06);
	display_cursor_blink_on();
	place_lcd_cursor_1();
}

void display_cursor_blink_on(){
	send_four(0);
	send_four(0xFU);
}

void place_lcd_cursor_1(){
	send_four(0x8U);
	send_four(0x0);
}

void place_lcd_cursor_2(){
	send_four(0xCU);
	send_four(0x0);
}


void LCD_str(char s[]){
	int count=0;
	for(count=0;s[count] != '\0';count++){
		LCD_sendData(s[count]);
	}
}

void LCD_clear() {
	place_lcd_cursor_1();
	LCD_str("                                   ");
	place_lcd_cursor_2();
	LCD_str("                                   ");
	place_lcd_cursor_1();
}

void LCD_int (int x){
	char num[20];
	sprintf(num,"%d",x);
	LCD_str(num);
}

void LCD_double (double y){
	char num[20];
	sprintf(num,"%f",y);
	LCD_str(num);
}


void LCD_sendData(unsigned char data){
	set_PIN(RS);
	clear_PIN(RW);
	set_PIN(EN);
	GPIOD->ODR &= ~(0xFU<<DB4);
	GPIOD->ODR |= ((data>>4)&0xF);
	clear_PIN(EN);
	check_BF();

	set_PIN(RS);
	clear_PIN(RW);
	set_PIN(EN);
	GPIOD->ODR &= ~(0xFU<<DB4);
	GPIOD->ODR |= (data&0xF);
	clear_PIN(EN);
	check_BF();
}

void LCD_sendInstr(unsigned char instr){
	clear_PIN(RS);
	clear_PIN(RW);
	set_PIN(EN);
	GPIOD->ODR &= ~(0xFU<<DB4);
	GPIOD->ODR |= ((instr>>4)&0xF);
	clear_PIN(EN);
	check_BF();

	clear_PIN(RS);
	clear_PIN(RW);
	set_PIN(EN);
	GPIOD->ODR &= ~(0xFU<<DB4);
	GPIOD->ODR |= (instr&0xF);
	clear_PIN(EN);
	check_BF();
}

void clear_PIN(int PINNO){
	GPIOD->ODR &= ~(1U<<PINNO);	
}

void set_PIN(int PINNO){
	GPIOD->ODR |= (1U<<PINNO);
}


void check_BF(){
	clear_PIN(RS);
	GPIOD->MODER &= ~(GPIO_MODER_MODER3); 
	set_PIN(RW);
	set_PIN(EN);
	while((GPIOD->IDR &(1U<<DB7)) != 0);
	clear_PIN(EN);
	clear_PIN(RW);
	GPIOD->MODER |= (GPIO_MODER_MODER3_0); 
}

void SysTick_Init(uint32_t load_reg_value){
	SysTick->CTRL =0;
	SysTick->LOAD = load_reg_value - 1;
	NVIC_SetPriority(SysTick_IRQn, 6);
	SysTick->VAL =0;
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
}

void RPG_Switch_Init(){
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	GPIOC->MODER &= ~(GPIO_MODER_MODER1);
	GPIOC->PUPDR &= ~(GPIO_PUPDR_PUPD1_Msk);
	GPIOC->PUPDR |= (GPIO_PUPDR_PUPD1_0); 
		
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI1_PC;
	EXTI->IMR |= EXTI_IMR_MR1;
	EXTI->RTSR |= EXTI_RTSR_TR1;
		
	__enable_irq();
	NVIC_SetPriority(EXTI1_IRQn,0);
	NVIC_ClearPendingIRQ(EXTI1_IRQn);
	NVIC_EnableIRQ(EXTI1_IRQn);	
}


