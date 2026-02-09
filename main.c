/*
 * main.c
 *
 * Created: 8/30/2023 10:46:55 AM
 *  Author: Andrea Marcosano Ruth Dagnachew 
 */ 

#define F_CPU 16000000UL

#include <atmel_start.h>
#include <stdint-gcc.h>
#include <stdio.h>
#include <avr/pgmspace.h>
#include <avr/iom328pb.h>
#include <util/delay.h>
#include <math.h>
#include <lcd.h>

//initial position of frog
int x=9;
int y=3;

char key='$';

void printFirst()
{
	 for(int i=0;i<10;i=i+1)
	 {
		lcd_write_string(PSTR("# "));
	 }
}

void drawCars(uint8_t row, uint8_t col)
{
	lcd_goto_position(row, col);
	lcd_write_string(PSTR("  ##8"));
}

void drawTrucks(uint8_t row, uint8_t col)
{
	lcd_goto_position(row, col);
	lcd_write_string(PSTR(" ###>"));

}
void delete(uint8_t row, uint8_t col)
{
	lcd_goto_position(row, col);
	lcd_write_string(PSTR("     "));
}




int  increase(uint8_t row,uint8_t position)
{
	if(position+5==20)
	{
		delete(row,position);
		position=0;
	}
	else
	{
		position=position+1;
	}
	return position;
}

void deleteFrog()
{
	
	if (((x>=0) & (x<20)) & ((y>=0) & (y<4)))
	{
		lcd_goto_position(y,x);
		lcd_write_string(PSTR(" "));
	}
}

void drawFrog()
{
	if (((x>=0) & (x<20)) & ((y>=0) & (y<4)))
	{
		lcd_goto_position(y,x);
		lcd_write_string(PSTR("&"));
	}
}

uint8_t keypressed() {
	 // Checks to see if any key has been pressed
	 // Sets all columns to low, and checks if any row goes low
	 // Returns a 1 (true) if a key has been pressed, 0 if not
	 
	 // Set column output pins low, so input low if contact made
	 
	 uint8_t rowval;
	 uint8_t kp;
	 
	 PORTD &= ~(1<<PD0) & ~(1<<PD2) & ~(1<<PD4); // Set PD0, PD2 and PD4 low
	 _delay_us(10);  // Short delay to allow signals to settle
	 
	 rowval = PIND & 0x42;   // Read value from Port D pins and clear bits not associated with keypad row inputs
	 
	 kp = (rowval != 0x42);    // if 0x6A, all high so no key has been pressed
	 
	 return kp;
}
	 

void keypad_init() {
	// Subroutine to set ports to required input and output states and enable pull up resistors for inputs
	
	// Set the columns as ouput
	DDRD |= (1<<PD0) | (1<<PD2) | (1<<PD4) ;   // Set Port D pins 0, 2 and 4 as outputs (columns)
	
	// Set row pins to input mode
	DDRD &= ~(1<<PD1) & ~(1<<PD3) & ~(1<<PD5) & ~(1<<PD6); // Set PD1, PD3, PD5 and PD6 as inputs
	
	// Turn on the internal resistors for the input pins
	PORTD |= (1<<PD1) | (1<<PD3) | (1<<PD5) | (1<<PD6); // Turn on internal pull up resistors for PD3, PD4, PD5 and PD6
	
	// Initialise the column output pins low, so input low if contact made
	PORTD &= ~(1<<PD0) & ~(1<<PD2) & ~(1<<PD4); // set PD0, PD2 and PD4 low
}

// keypad read
void keypad_read() {
	uint8_t move;
	
	key='$';

	PORTD &= ~(1<<PD2 );            // Set PD2  low - to check column 1
	PORTD |= (1<<PD0) | (1<<PD4);  // Set  other two column pins high
	_delay_us(10);                // Short delay to allow signals to settle
	
	move =PIND & 0x42;  // Read value from Port D pins and clear bits not associated with keypad row inputs
	

	move = PIND & 0x6A;   // Read value from Port D pins and clear bits not associated with keypad row inputs
	
	switch(move) {
		case 0x68: key = '1';
		break;
		case 0x2A: key = '4';
		break;
		case 0x4A: key = '7';
		break;
		case 0x62: key = '*';
		break;
		default: key = '$';
		break;
	}
	  PORTD &= ~(1<<PD0 )&~(1<<PD4);
	
	if(key=='$')//checking if keych has already been initialized (button already identified)
	{
		PORTD &= ~(1<<PD0 );            // Set PD0  low - to check column 1
		PORTD |= (1<<PD2) | (1<<PD4);  // Set  other two column pins high
		_delay_us(10);
		
		move = PIND & 0x6A;
		
		switch(move) {
			case 0x68: key = '2';
			break;
			case 0x2A: key = '5';
			break;
			case 0x4A: key = '8';
			break;
			case 0x62: key = '0';
			break;
			default: key = '$';
			break;
		}
		PORTD &= ~(1<<PD2)&~(1<<PD4);
	}
	if(key=='$')//checking if keych has already been initialised(button already identified)
	{
		PORTD &= ~(1<<PD4 );           	// Set PD4 low - to check column 3
		PORTD |= (1<<PD0) | (1<<PD2); 	// set  other 2 high
		// Short delay to allow signals to settle
		_delay_us(10);// Set  other two column pins high
		
		move = PIND & 0x6A;
		
		switch(move) {
			case 0x68: key = '3';
			break;
			case 0x2A: key = '6';
			break;
			case 0x4A: key = '9';
			break;
			case 0x62: key = '#';
			break;
			default: key = '$';
			break;
		}
		 PORTD &= ~(1<<PD0 )&~(1<<PD2);
	}
	
}

void init_interrupts() {
	//PD2 PCINT18
	//PD0 PCINT16
	//PD4 PCINT20
	//PD1 PCINT17
	//PD6 PCINT22
	
	//PCMSK2
	
	PCMSK2 = (1<<PCINT22) | (1<<PCINT17)| (1<<PCINT19)| (1<<PCINT21);//  Enable PCINT22 and 17, interrupts caused by first and second rows
	
	PCICR &= ~(1<<PCIE0)&~(1<<PCIE1); // Disable PC Int 1 and PC Int 1
	PCICR |=(1<< PCIE2);  // Enable PC Int 2
	
	sei();  // Enable global interrupts
	
}  

void move()
{
	
	switch(key) {
		case '2':
			y=y-1;
			deleteFrog();
			drawFrog();
		break;
		case '4':
			deleteFrog();
			x=x-1;
			drawFrog();
		break;
		case '5':
			deleteFrog();
			y=y+1;
			drawFrog();
		break;
		case '6':
			deleteFrog();
			x=x+1;
			drawFrog();
		break;
		case '0': 
			x=9;
			y=3;
			drawFrog();
		break;
	}
}

ISR(PCINT2_vect) {
	
	
	_delay_us(100);                       // Short delay to 'debounce' switch
	
	keypad_read();

	
	PCIFR|=(1<<PCIF2);
	

	move();
	
	
}   //End ISR PCINT0

int main(void)
{
	// initialise MCU, drivers and middleware
	atmel_start_init();
	
	// start up the LCD
	lcd_init();
	lcd_home();
	
	//portD is used for the joystick
	
	// Initialise keypad
	keypad_init();
	
	// Wait a moment, then enable interrupts
	_delay_ms(1);
	init_interrupts();

	
	
	int position1=15;
	int position2=10;
	int position3=4;
	
	int position4=12;
	int position5=5;
	
	
	printFirst();    
	
	drawFrog(x,y);
	
    while(1)
    {
     
	 lcd_home();   //go to position 00
	 
	 //second line
	 
	 drawCars(1, position1);
	 drawTrucks(1, position2);
	 drawCars(1, position3);
	 
	 
	 //third line
	 drawTrucks(2, position4);
	 drawCars(2, position5);
	 
	

	 _delay_ms(500); // delay to slow down cars
	
	 position1=increase(1,position1);
	 position2=increase(1,position2);
	 position3=increase(1,position3);
	 
	 position4=increase(2,position4);
	 position5=increase(2,position5);
	 
	 //_delay_ms(100);
	    
    }
	
	
	return 0;
}
