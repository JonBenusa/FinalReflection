#define RW 6
#define RS 7
#define EN 5 
#define DB7 3
#define DB6 2
#define DB5 1
#define DB4 0


void LCD_port_init(int x);
void LCD_init(void);
void split_bits(unsigned int bits);
void LCD_sendData(unsigned int high, unsigned int low);
void LCD_sendInstr(unsigned int high, unsigned int low);
void place_LCD_cursor(int num);
void delay(int num);
void setBits(char);
void intToChar(int num);
void doubleToLCD(double num, int sigfig);
void clear_pin(int pin);
void set_pin(int pin);
void check_BF(void);
void switch_line(int line);


