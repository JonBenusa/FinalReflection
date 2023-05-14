#include "stm32f4xx.h" 
#include <string.h>

#define RW 6
#define RS 7
#define EN 5 
#define DB7 3
#define DB6 2
#define DB5 1
#define DB4 0

void LCD_port_init(void);
void delay(void);
void delay_short(void);
void send_four(uint8_t shift);
void LCD_init(void);
void display_cursor_blink_on(void);
void place_lcd_cursor_1(void);
void place_lcd_cursor_2(void);
void LCD_str(char s[]);
void LCD_int (int x);
void LCD_double (double y);
void LCD_sendData(unsigned char data);
void LCD_sendInstr(unsigned char instr);
void clear_PIN(int PINNO);
void set_PIN(int PINNO);
void check_BF(void);
void SysTick_Init(uint32_t load_reg_value);
void RPG_Switch_Init(void);
void LCD_clear(void);


