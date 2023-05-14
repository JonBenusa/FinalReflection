#include <stdio.h>
#include <string.h>
#include "stm32f4xx.h"
#include "spi.h"


#include "stm32f4xx.h"

void touch_button_init(void);
void reset_state(void);
void alarm_off(void);

void SPI_init(void){
	
	
	//Configuring
	RCC->AHB1ENR |= (RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOEEN);
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
	
	// Port A Pins 5-7 used for SPI, 5 for SCK, 6 for MISO, 7 for MOSI// Port A Pins 5-7 used for SPI, 5 for SCK, 6 for MISO, 7 for MOSI
	GPIOA->AFR[0] |= (GPIO_AFRL_AFSEL5_2 | GPIO_AFRL_AFSEL5_0 | GPIO_AFRL_AFSEL6_2 | GPIO_AFRL_AFSEL6_0 | GPIO_AFRL_AFSEL7_2 | GPIO_AFRL_AFSEL7_0);
	
	GPIOA->MODER &= ~(GPIO_MODER_MODER5 | GPIO_MODER_MODER6 | GPIO_MODER_MODER7);
	GPIOE->MODER &= ~GPIO_MODER_MODER3;
	GPIOA->MODER |= (GPIO_MODER_MODER5_1| GPIO_MODER_MODER6_1 | GPIO_MODER_MODER7_1);
	GPIOE->MODER |= GPIO_MODER_MODER3_0;
	GPIOE->ODR |= GPIO_ODR_OD3; 

	// Port A Pins 5-7 used for SPI, 5 for SCK, 6 for MISO, 7 for MOSI
	
	SPI1->CR1 |= SPI_CR1_CPOL | SPI_CR1_CPHA;

	SPI1->CR1 |= SPI_CR1_MSTR; 
	
	SPI1->CR1 |= SPI_CR1_SSM; 
	
	SPI1->CR1 |= SPI_CR1_SSI;
	
	SPI1->CR1 |= (SPI_CR1_BR_2);
	
	SPI1->CR1 |= SPI_CR1_SPE; 
	
}

unsigned char spi_send (unsigned char sent){
		SPI1->DR = sent;
		while(!(SPI1->SR & SPI_SR_RXNE));
		return(SPI1->DR);
}



int read_position_x (void){
	SPI_init();
	static unsigned char x;
	GPIOE->ODR &= ~(GPIO_ODR_OD3);
	x= spi_send(0x20);
	x= spi_send(0x27);  
	GPIOE->ODR |= GPIO_ODR_OD3;
	static unsigned char position_x[10];
	unsigned char x_pos; 
	
		GPIOE->ODR &= ~(GPIO_ODR_OD3);
		position_x[1] = spi_send(0xA9);
		position_x[2] = spi_send(0);
		GPIOE->ODR |= GPIO_ODR_OD3;
		
		x_pos = position_x[2] & 0XF0;
		return(x_pos); 
		
}

int read_position_y (void){
	SPI_init();
	
	static unsigned char y;
	GPIOE->ODR &= ~(GPIO_ODR_OD3);
	y= spi_send(0x20);
	y= spi_send(0x27);  
	GPIOE->ODR |= GPIO_ODR_OD3;
	static unsigned char position_y[10];
	unsigned char y_pos;  
	
		GPIOE->ODR &= ~(GPIO_ODR_OD3);
		position_y[1] = spi_send(0xAB);
		position_y[2] = spi_send(0);
		GPIOE->ODR |= GPIO_ODR_OD3;
	 
		
		y_pos = position_y[2] & 0xF0;
		return(y_pos); 
		
}

int read_position_z (void){
		SPI_init();

	static unsigned char z;
	GPIOE->ODR &= ~(GPIO_ODR_OD3);
	z= spi_send(0x20);
	z= spi_send(0x27);  
	GPIOE->ODR |= GPIO_ODR_OD3;
	static unsigned char position_z[10]; 
	unsigned char z_pos; 
		
		GPIOE->ODR &= ~(GPIO_ODR_OD3);
		position_z[1] = spi_send(0xAD);
		position_z[2] = spi_send(0); 
	  GPIOE->ODR |= GPIO_ODR_OD3; 
		
		z_pos = position_z[2] & 0xF0;
		return(z_pos); 
		
}



