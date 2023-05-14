#include <stdio.h>
#include <string.h>
#include "stm32f4xx.h"
#include "LCD.h"


void motor_delay(void);
void init_steppermotor(void);
void unlock_safe(void);
void lock_safe(void);
