#include "stm32f4xx.h"
#include "Interupt.h"


void init_ADC() {
	// initialize clock for Port A and ADC
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; 
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	
	// intiialize Port A pin 1 as ADC pin
	GPIOA->MODER |= GPIO_MODER_MODER1; //analog function mode
	GPIOA->AFR[1] |=GPIO_MODER_MODE1_1;
	
	//single channel continous conversion mode
	ADC1->CR1 |= ADC_CR1_SCAN;
	ADC1->CR2 |= ADC_CR2_CONT;
	ADC1->CR2 |= ADC_CR2_EOCS;
	
		// Set Sampling time to 84 (100) cycles in SMPR2 register (default is 000)
	ADC1->SMPR2	&= ADC_SMPR2_SMP1_2; //sets the delay before reading.
	
	//12 bit resolution
	ADC1->CR1 &= ~ADC_CR1_RES_Msk;
	
	//Enable EOC Interupt
	ADC1->CR1 |= ADC_CR1_EOCIE; 
	
	// Specify channel number 1 of the 1st conversion
	ADC1->SQR1 &=~ADC_SQR1_L; // set L bit to 0000 (default) – i.e. only 1 conversion
	ADC1->SQR3 |= ADC_SQR3_SQ1_0; // set channel to 1
	
	//turn on ADC
	ADC1->CR2 |= ADC_CR2_ADON;
	// Start Conversion
	ADC1->CR2 |= ADC_CR2_SWSTART; //GOOD
	
		// LET NVIC handle ADC Interrupts
	__enable_irq();
	NVIC_ClearPendingIRQ(ADC_IRQn);
	NVIC_SetPriority(ADC_IRQn,0);
	NVIC_EnableIRQ(ADC_IRQn);
	
}

void init_TIM4(uint32_t count) {
	RCC->APB1ENR |= (RCC_APB1ENR_TIM4EN); //enable clk for TIM4
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN; //enable clk for GPIOD
	
	GPIOD->MODER &= ~(3U>>15*2); 
	GPIOD->MODER |= GPIO_MODER_MODE15_1;
	GPIOD->AFR[1] |= GPIO_MODER_MODE15_1;
	
	TIM4->CCMR2 &=~TIM_CCMR2_CC4S; //set as output with 00
	
	TIM4->CCER &=~TIM_CCER_CC4P; //sets active high
	
	TIM4->CCMR2 |= TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1; //110 PWM mode 1
	
	TIM4->PSC = 15999;
	TIM4->ARR = count-1; //period
	TIM4->CNT = 0; //reset current count count
	TIM4->CCR4 = (count-1)/2; //time on
	
	TIM4->CCMR2 |= TIM_CCMR2_OC4PE; //preload enable
	TIM4->CR1 |= TIM_CR1_ARPE; //auto reload enable
	
	TIM4->CR1 |= TIM_CR1_CEN; //enable the timer
	
}
void init_TIM6(uint32_t count, int importance) {
	RCC->APB1ENR |= (RCC_APB1ENR_TIM6EN | RCC_APB1ENR_TIM7EN);
	
	TIM6->PSC = 9999;
	TIM6->ARR = count-1;
	TIM6->CNT = 0;
	TIM6->SR &= ~TIM_SR_UIF;
	TIM6->DIER |= TIM_DIER_UIE;	
	TIM6->CR1 |= TIM_CR1_CEN;		
	
	__enable_irq();
	NVIC_SetPriority(TIM6_DAC_IRQn, importance);
	NVIC_ClearPendingIRQ(TIM6_DAC_IRQn);
	NVIC_EnableIRQ(TIM6_DAC_IRQn);
}

void init_TIM7(uint32_t count, int importance) {
	RCC->APB1ENR |= (RCC_APB1ENR_TIM6EN | RCC_APB1ENR_TIM7EN);
	
	TIM7->PSC = 9999;
	TIM7->ARR = count-1;
	TIM7->CNT = 0;
	TIM7->SR &= ~TIM_SR_UIF;
	TIM7->DIER |= TIM_DIER_UIE;	
	TIM7->CR1 |= TIM_CR1_CEN;	
	
	__enable_irq();
	NVIC_SetPriority(TIM7_IRQn, importance);
	NVIC_ClearPendingIRQ(TIM7_IRQn);
	NVIC_EnableIRQ(TIM7_IRQn);
}

void init_user_button(int importance){
//user switch is on PA0
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN;
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

	GPIOA->MODER &= ~ (GPIO_MODER_MODER0);  // GPIO_MODER_MODER0 is the same as saying 0x3<<0;

//Connect the portA pin0 to external interrupt line0
	SYSCFG->EXTICR[0] &= SYSCFG_EXTICR1_EXTI0_PA; //and because we want to clear all other ~(0x000F)
	EXTI->IMR |= EXTI_IMR_MR0; // same as saying (1<<SWITCH);//Interrupt Mask
	EXTI->RTSR|= EXTI_RTSR_TR0; // same as (1<<SWITCH);//Rising trigger selection

	__enable_irq();
	NVIC_SetPriority(EXTI0_IRQn, importance);
	NVIC_ClearPendingIRQ(EXTI0_IRQn);
	NVIC_EnableIRQ(EXTI0_IRQn);
}

void change_time_TIM6(uint32_t count){
	TIM6->CNT = 0;
	TIM6->ARR = count-1;
}

void change_time_TIM7(uint32_t count){
	TIM7->CNT = 0;	
	TIM7->ARR = count-1;	
}

void change_time_TIM4(uint32_t count){
	TIM7->CNT = 0;	
	TIM7->ARR = count-1;	
}
