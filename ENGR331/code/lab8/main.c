#include "stm32f4xx.h"
#include "Interupt.h"

volatile int flag, ii =0;
volatile int myDATAArr[1000];

int main(void){
		init_ADC();
		
	
	while(1);
	
}

// INERRUPT HANDLER FOR ADC
void ADC_IQRHandler(void) {
	NVIC_ClearPendingIRQ(ADC_IRQn);
	
	if((ADC1->SR & ADC_SR_EOC)){
		myDATAArr[ii++] = (ADC1->DR);
		if(ii>=500) {
			ADC1->CR2 &= ~ADC_CR2_ADON;
		}
	}
}
