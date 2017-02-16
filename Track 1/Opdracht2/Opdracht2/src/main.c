#define F_CPU 8000000
#include <asf.h>
#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>

void wait( int );



int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
	board_init();
	
	//Tel program Port D is used for output
	DDRD = 0xFF;

	while(1)
	{
		//Turn on led 6 & 7 on Port D
		PORTD = 0xC0;
		wait(500);
		//Turn off all leds on Port D
		PORTD = 0x00;
		wait(500);
	}

	
	/* Insert application code here, after the board has been initialized. */
}

void wait( int ms )
{
		for (int i=0; i<ms; i++)
		{
			_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
		}
}
