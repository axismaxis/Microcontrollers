#define F_CPU 8000000
#include <asf.h>
#include <avr/io.h>
#include <util/delay.h>

int CompareValue = 10;
int TenthValue = 0;

void wait( int ms )
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

void InitAdc()
{
	// AREF = VCC, Result left adjusted
	// input op pin PF1
	ADMUX = 0b11100001;
	// no Free running mode, no startbit, prescaler 64
	ADCSRA = 0b10000110;
}

void EnableAdcConverter()
{
	//Set 6th bit to start conversion
	ADCSRA |= 0b01000000;
}

int DataConverted()
{
	while((ADCSRA & 0b01000000) == 1) {}
	if((ADCSRA & 0b01000000) == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int main( void )
{
	DDRF = 0x0;

	DDRA = 0xFF;
	DDRB = 0xFF;

	InitAdc();

	while (1)
	{
		//EnableAdcConverter();
		ADCSRA |= 0b01000000;
		while(ADCSRA & 0b01000000);
		PORTA = ADCH;
		PORTB = ADCL;
		wait(500);
	}
}
