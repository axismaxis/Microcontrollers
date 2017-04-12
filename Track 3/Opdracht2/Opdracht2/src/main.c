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

ISR( TIMER2_OVF_vect )
{
	TenthValue++; // Increment counter
}

// Initialize timer2
//

void timer2Init( void )
{
	OCR2 = CompareValue; // Compare value of counter 2
	TIMSK |= 0b01000000; // T2 compare match interrupt enable
	SREG |= 0b0100000; // turn_on intr all
	TCCR2 = 0b00011111; // Initialize T2: ext.counting, rising edge
	// compare output mode, CTC, RUN
}

int main( void )
{
	DDRD &= 0b01000000; // set PORTD.7 for input
	DDRA = 0xFF; // set PORTB for output (shows countregister)
	DDRB = 0xFF; // set PORTC for output (shows tenth value)
	timer2Init();
	while (1)
	{
		PORTA = TCNT2; // show value counter 2
		PORTB = TenthValue; // show value tenth counter
		wait(10); // every 10 ms
	}
}
