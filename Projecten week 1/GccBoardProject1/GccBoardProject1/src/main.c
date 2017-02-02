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

	//Bitnumber used for counting
	int bitNumber = 0b00000001;

	while (1)
	{
		PORTA = (getBitNumber(bitNumber) | getBitNumber(bitNumber << 3));
		PORTB = (getBitNumber(bitNumber << 1) | getBitNumber(bitNumber << 2));
		PORTC = (getBitNumber(bitNumber << 2) | getBitNumber(bitNumber << 1));
		PORTD = (getBitNumber(bitNumber << 3) | getBitNumber(bitNumber));
		
		wait(300);

		bitNumber = bitNumber << 1;
		//Wraps around after bitshifting 8 times
		if(bitNumber > 128)
		{
			bitNumber = 1;
		}
	}

	return 1;
}
