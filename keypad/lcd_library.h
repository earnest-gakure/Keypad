#ifndef __LCD_LIBRARY__H
#define __LCD_LIBRARY__H
#include <stdint.h>

void delay_milli(uint32_t n);
void delay_micro(uint32_t n);
void lcd_data (unsigned char  data);
void lcd_command (unsigned char command );
#endif 