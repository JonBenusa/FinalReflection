//ENGR 331 - External Input demo (PA0 - USER SWITCH)

#include "stm32f4xx.h"                  // Device header

#define LED_ORANGE 13  //PortDPin13
#define LED_GREEN 12
#define LED_RED 14
#define LED_BLUE 15

#define SWITCH 0 //PortA Pin0

void Init_LED(void);
void Init_Switch(void);
void EXTI0_IRQHandler(void);
void LED_on(int color);
