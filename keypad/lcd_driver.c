#include "TM4C123.h"                    // Device header
#include "lcd_driver.h"
#include "lcd_library.h"

void LCD_Init (void)
	{
	SYSCTL->RCGCGPIO |= 0x01 ;	// Clock for port A & B
	SYSCTL->RCGCGPIO |= 0x02 ;	
//configuring portA pin 5,6,7 and portB 0-7 as out put	
	GPIOA->DIR |= 0xE0;    //portA 5,6,7
	GPIOB->DIR |= 0xF0;     //portB 4-7
	//enabling portA & B
	GPIOA->DEN |= 0xE0;
	GPIOB->DEN |=0xF0;
	
	lcd_command(0x28);   //setting 4bit mode,2 line of display , 5x7 font
	lcd_command(0x06);   //increment the cursor automatically
	lcd_command(0x0F);   //turn on displaay ..cursor blinking
	lcd_command(0x01);   //clear screen	
}
	void lcd_string (unsigned char *str , unsigned char len ){
	char i;
	for(i=0;i<len;i++){
		
		lcd_data(str[i]);
	}
	
}