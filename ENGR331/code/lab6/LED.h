#define LED_ORANGE 13  
#define LED_GREEN 12
#define LED_RED 14
#define LED_BLUE 15
#define SWITCH 0 //PortA Pin0 -- default pull-down resistor

void LED_init(int color);
void LED_on(int color);
void LED_off(int color);
void LED_toggle(int color);
