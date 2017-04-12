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
	ADMUX = 0b01100011;
	// no Free running mode, no startbit, prescaler 64
	ADCSRA = 0b11100110;
}

int main( void )
{
	DDRF = 0x0;

	DDRA = 0xFF;
	DDRB = 0xFF;

	InitAdc();
	
	char* text;

	while (1)
	{
		PORTB = ADCL;
		PORTA = ADCH;
		sprintf(text, "%i", ADCH);
		LCDWrite(text);
		wait(500);
	}
}
