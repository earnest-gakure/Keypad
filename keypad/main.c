#include "TM4C123.h"                    // Device header
#include "lcd_driver.h"
#include "lcd_library.h"

#define K_ROW GPIOE
#define K_COL GPIOC
void KEYPAD_init(void);
unsigned char getkey (void);
int main (){
	unsigned char key ;
	int key_count = 0 ;
	KEYPAD_init ();
	LCD_Init();
	lcd_command(0x80); //set cursor to line one beggining
	delay_milli(500);
 
	
	while (1){
		
		key =getkey();
		if(key!=0){
		delay_milli(500);
			key_count++;
			if (key_count>=16){
				lcd_data(key); //this is to make sure it prints on pin 16
				delay_milli(500);
				lcd_command(0xC0); //line 2 begginning
				
				key_count = 0; //to reset key_count
			}
			if (key== '*'){
				lcd_command(0x01); // clear screen
				lcd_command(0x80); //beggininhg line 1
				
				key_count = 1;
			}
		lcd_data(key); //continue printing if >16
			delay_milli(100);
		}
	}
	  	
}
void KEYPAD_init(void){ 
	SYSCTL->RCGCGPIO |= 0x04 ; //PORTC clock
	SYSCTL->RCGCGPIO |= 0x10;  //PORTE clock
	
	//setting GPIOE as OUTPUT
	K_ROW->DIR |= 0x0F ;
	K_ROW->DEN |= 0x0F ;
	K_ROW->ODR |= 0x0F ; //setting output high
	
	
	//column
	K_COL->DIR &=~0xF0 ; //set PC4-7 INPUT
	K_COL->DEN |= 0xF0 ;
	K_COL->PUR |= 0xF0;

}
// Function that gets which KEY is pressed.we start by creating a key map
//The function returns key pressed
unsigned char getkey (void)
{
	const unsigned char keymap [4][4]={
		{ '1' ,'2' , '3' ,'A' },
		{ '4' ,'5' , '6' ,'B' },
		{ '7' ,'8' , '9' ,'C' },
		{ '*' ,'0' , '#' ,'D' } 
	};
	
	  //creating a logic that detects which key is pressed
	  //we start by creating two local variables for our rows and columns
	
	uint8_t  k_row , k_col ;
	//we accesse Row DATA register and assign 0 to it in order to enable the ROWS
	K_ROW->DATA = 0x00 ;
	//Lets now read the columns
	 k_col = K_COL->DATA & 0xF0;
	
	//using an if statement to check which key is pressed    
	if (k_col == 0 )
		return 0 ;
	
	//we now want to see which key is pressed,we will enable each ROW one by one 
	for(;;){
	k_row =0 ;
		K_ROW->DATA = 0x0E; //Enable row o  OB :1110
	delay_milli(100);
	k_col = K_COL->DATA & 0xF0 ;  //WHE NOT PRESSED K_COL =0x00
	if(k_col != 0xF0)
		break ;
	
	k_row = 1 ;
	K_ROW->DATA = 0x0D ; //enable row 1  OB :1101
	delay_milli(100);
	k_col = K_COL->DATA & 0xF0 ;  //WHE NOT PRESSED K_COL =0x00
	if(k_col != 0xF0)
		break ;
	
	k_row = 2 ;
	K_ROW->DATA = 0x0B ; //enable row 2  OB :1011
	delay_milli(100);
	k_col = K_COL->DATA & 0xF0 ;  //WHE NOT PRESSED K_COL =0x00
	if(k_col != 0xF0)
		break ;
	
	k_row = 3 ;
	K_ROW->DATA = 0x07 ; //enable row 3  OB :0111
	delay_milli(100);
	k_col = K_COL->DATA & 0xF0 ;  //WHE NOT PRESSED K_COL =0x00
	if(k_col != 0xF0)
		break ; //executed when true i.e when key is pressed
	
	return 0;
} 
	if(k_col == 0xE0) 
		return keymap[k_row][0];  //means a key in column 0 is pressed
  if(k_col == 0xD0) 
		return keymap[k_row][1];  //means a key in column 1 is pressed
  if(k_col == 0xB0) 
		return keymap[k_row][2];  //means a key in column 2 is pressed
  if(k_col == 0x70) 
		return keymap[k_row][3];  //means a key in column 3 is pressed

	return 0;
}


