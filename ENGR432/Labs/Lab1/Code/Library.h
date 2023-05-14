#include "stm32f429xx.h"

#define LED_GREEN 0
#define LED_RED 14
#define LED_BLUE 7
#define SWITCH 0 //PortA Pin0 -- default pull-down resistor

//LED controls
void LED_init(int color);
void LED_on(int color);
void LED_off(int color);
void LED_toggle(int color);
//Timers
void init_TIM3(uint32_t time, int importance);
void change_time_TIM3(uint32_t count);
void init_TIM4(uint32_t time, int importance);
void change_time_TIM4(uint32_t count);
void init_SysTick(uint32_t time, int importance);
//Interupts
void init_UserButton(void);
