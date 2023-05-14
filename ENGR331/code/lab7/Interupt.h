#include "stm32f4xx.h"

void init_input_capture(void);
void init_TIM6(uint32_t time, int importance);
void init_TIM7(uint32_t time, int importance);
void init_TIM4(uint32_t time);
void init_user_button(int importace);	

void change_time_TIM6(uint32_t count);
void change_time_TIM7(uint32_t count);
void change_time_TIM4(uint32_t count);
