#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
static int LightBit;

void wait( int ms )
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}


ISR( INT0_vect )
{
	if(LightBit > 128)
	{
		LightBit >>= 8;
	}
	LightBit <<=1;
	PORTC = LightBit;
	PORTD = 0b00000000;
	wait(1000);

}

ISR( INT1_vect )
{
	if(LightBit > 128)
	{
		LightBit >>= 8;
	}
	LightBit <<= 1;
	PORTC = LightBit;
	PORTD = 0b00000011;
	wait(1000);
}


int main (void)
{
	LightBit = 0b00000001;
	
	DDRC = 0b11111111;
	DDRD = 0b11111111;
	EICRA |= 0x0B;
	EIMSK |= 0x03;
	sei();
	/* Insert system clock initialization code here (sysclk_init()). */
	PORTD = 0b00000011;
	
	while (1)
	{
	}
	return 1;
}