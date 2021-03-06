#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define sbi(x,y) x |= _BV(y) //set bit
#define cbi(x,y) x &= ~(_BV(y)) //clear bit
#define tbi(x,y) x ^= _BV(y) //toggle bit
#define is_high(x,y) ((x & _BV(y)) == _BV(y))

typedef struct { 
	unsigned char data;
	unsigned int delay ;
} PATTERN_STRUCT; 


// 7 seg
// PORTD dp G F E D C B A
//        y y y y x x x x

PATTERN_STRUCT pattern[] = { 
	{0xFF, 150}, {0xFF, 150}, 
	{0xFF, 150}, {0xFF, 150},
	{0x01, 150}, {0x02, 150}, {0x40, 150}, {0x20, 150},
	{0x01, 150}, {0x02, 150}, {0x40, 150}, {0x20, 150},
	{0x00, 150},
	{0x01, 150}, {0x03, 150}, {0x43, 150}, {0x63, 150},	
	{0x01, 150}, {0x03, 150}, {0x43, 150}, {0x63, 150},
	{0x00, 150},
	{0xFF, 0}
};

// A b c d e f g dp
const unsigned char
digits[17] =
{
	// dPgfedcba
	0b00111111, // 0
	0b00000110, // 1
	0b01011011, // 2
	0b01001111, // 3
	0b01100110, // 4
	0b01101101, // 5
	0b01111101, // 6
	0b00000111, // 7
	0b01111111, // 8
	0b01101111, // 9
	0b01110111, // A
	0b01111100, // B
	0b00111001, // C
	0b01011110, // D
	0b01111001, // E
	0b01110001, // F
	0b11111001  // Error
};

/******************************************************************/
void wait( int ms )
/* 
short:			Busy wait number of millisecs
inputs:			int ms (Number of millisecs to busy wait)
outputs:	
notes:			Busy wait, not very accurate. Make sure (external)
				clock value is set. This is used by _delay_ms inside
				util/delay.h
Version :    	DMK, Initial code
*******************************************************************/
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

void display(int digit)
{
	if(digit > 16)
	{
		PORTD = digits[16];
	}
	else
	{
		PORTC = digits[digit];
	}
}

int count = 0;
ISR( INT0_vect )
{
	count++;
	if(PIND & 0b00000010)
	{
		count = 0;
	}
	display(count);
	wait(10);
}

ISR( INT1_vect )
{
	count--;
	if(PIND & 0b00000001)
	{
		count = 0;
	}
	display(count);
	wait(10);
}


/******************************************************************/
int main( void )
/* 
short:			main() loop, entry point of executable
inputs:			
outputs:	
notes:			
Version :    	DMK, Initial code
*******************************************************************/
{
	DDRC = 0xFF;
	DDRD = 0xF0;

	EICRA |= 0x0B;			// INT1 falling edge, INT0 rising edge
	EIMSK |= 0x03;			// Enable INT1 & INT0

	sei();		

	while (1)
	{
		display(count);
		count++;
		wait(1000);
		if(count > 18)
		{
			count = 0;
		}
	}		    
}