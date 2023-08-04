#include "TM4C123.h"                    // Device header
#include "lcd_driver.h"
#include "lcd_library.h"

void lcd_command(unsigned char command){
	GPIOA->DATA =0x00 ;  //RS =0
	GPIOB->DATA = command & 0xF0;
	GPIOA->DATA |= 0x80 ;     //EN =1
	delay_micro(0);
	GPIOA->DATA = 0x00;   //EN =0
	
	GPIOA->DATA =0x00 ;  //RS =0
	GPIOB->DATA = (command<<4) & 0xF0;
	GPIOA->DATA |= 0x80 ;     //EN =1
	delay_micro(0);
	GPIOA->DATA = 0x00;   //EN =0
	
	if (command < 4)
		delay_milli(2);
	else
	delay_micro(37); // delay_micro(40)
}
void lcd_data (unsigned char data){
	GPIOA->DATA = 0x20 ;     //RS =1
	GPIOB->DATA =  data & 0xF0;	
	GPIOA->DATA |= 0x80 ;     //EN=1
	delay_micro(0);
	GPIOA->DATA |= 0x00;  //EN=0
	delay_micro(0);	
	GPIOA->DATA = 0x20 ;     //RS =1
	GPIOB->DATA =  (data<<4) & 0xF0 ;	
	GPIOA->DATA |= 0x80 ;     //EN=1
	delay_micro(0);
	GPIOA->DATA |= 0x00;  //EN=0
	delay_micro(0);	
}
void delay_micro(uint32_t n)
{
	SysTick->LOAD = (16000 * n) - 1;
	SysTick->VAL = 0;
	SysTick->CTRL = 0x5;
	while ((SysTick->CTRL & 0x10000) == 0)
	{
	}
	SysTick->CTRL = 0;
}

void delay_milli(uint32_t n)
{
	SysTick->LOAD = (16000 * 1000 * n) - 1;
	SysTick->VAL = 0;
	SysTick->CTRL = 0x5;
	while ((SysTick->CTRL & 0x10000) == 0)
	{
	}
	SysTick->CTRL = 0;
}

