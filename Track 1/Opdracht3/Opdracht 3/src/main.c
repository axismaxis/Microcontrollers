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
	
	//Tell program Port D is used for output
	DDRD = 0xFF;

	//Tell program Port C is used for input
	DDRC = 0x0;

	while(1)
	{
		//turn all leds off on Port D
		PORTD = 0x0;
		//If Button 0 is pressed, turn on led 7
		if(PINC & 1)
		{
			//Turn led 7 on on Port D
			PORTD = 0x80;
			wait(1);
		}
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
