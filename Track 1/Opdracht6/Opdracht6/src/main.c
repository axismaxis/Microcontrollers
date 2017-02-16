/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#define F_CPU 8000000
#include <asf.h>
#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>

void wait( int );
int getBitNumber( int );

void wait( int ms )
{
		for (int i=0; i<ms; i++)
		{
			_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
		}
}

//If bytes has become bigger than 0b10000000 than shift it right 8 times
int getBitNumber(int bytes)
{
	if(bytes > 128)
	{
		return bytes >> 8;
	}
	else
	{
		return bytes;
	}
}

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
	board_init();

	/* Insert application code here, after the board has been initialized. */
	//Init the first 4 registers for writing data to
	DDRA = 0b11111111;
	DDRB = 0b11111111;
	DDRC = 0b11111111;
	DDRD = 0b11111111;
	DDRF = 0b00000000;

	//Bitnumber used for counting
	int waitLength = 1000;
	int lampjeAan = 0;

	while (1)
	{
		if(lampjeAan == 0)
		{
			PORTA = 0b11111111;
			PORTB = 0b11111111;
			PORTC = 0b11111111;
			PORTD = 0b11111111;
			lampjeAan = 1;
		}
		else
		{
			PORTA = 0b00000000;
			PORTA = 0b00000000;
			PORTA = 0b00000000;
			PORTA = 0b00000000;
			lampjeAan = 0;
		}

		if (PINF & 1)
		{
			if(waitLength == 100)
			{
				waitLength = 1000;
			}
			else
			{
				waitLength = 100;
			}
		}
		
		wait(waitLength);
	}

	return 1;
}
