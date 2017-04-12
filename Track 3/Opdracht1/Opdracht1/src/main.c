#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <LCD.h>
#include <string.h>

void wait( int ms )
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );
	}
}

ISR( INT0_vect )
{

}

ISR( INT1_vect )
{

}

int main( void )
{
	DDRC = 0xFF;
	PORTC = 0x0;

	DDRC = 0xFF;
	DDRD = 0xF0;

	EICRA |= 0x0B;			// INT1 falling edge, INT0 rising edge
	EIMSK |= 0x03;			// Enable INT1 & INT0

	sei();		

	lcd_init();
	
	//lcd_writeChar('A');
	unsigned char makker[] = "Timon is heerlijk - Timon is heerlijk";
	lcd_writeLine(makker);
	//lcd_clear();
	//lcd_writeLine(makker);

	while (1)
	{
		wait(500);
		lcd_set_cursor();
	}		    
}