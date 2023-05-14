#include <stdio.h>
#include <string.h>
#include "stm32f4xx.h"

void SPI_init(void); 
int read_position_x(void); 
int read_position_y(void); 
int read_position_z(void); 
unsigned char spi_send (unsigned char sent); 
