#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <asf.h>
#include <stdio.h>
#include "LCD.h"

//set desired baud rate
#define BAUDRATE 1200
#define HIGH 1
#define LOW 0

/*
* Vars
*/
unsigned char rxdat[10];  // (global var) holds received RF bytes

long lowTime = 0;
long highTime = 0;
int edges = 0;



unsigned char receivedData = 0;

int startBitFound = 0;
int firstTimeFound = 0;

/*
* Function prototypes
*/
void delayms(int t);
void delayus(int t);
void send_rf_byte(unsigned char txdat);
void send_timon_bytes(unsigned char data);
void receive_rf_packet(void);
void InitInterupts(void);

int main(void)
{
	/* Set all PORTB to output*/
	DDRA = 0xFF;
	DDRB = 0xFF;
	DDRD = 0x0;
	DDRE = 0xFF;
	
	PORTA = 0x0;
	PORTE = 0x0;

	InitInterupts();

	int i;
	for(i = 0; i < 10; i++)
	{
		//send_timon_bytes(0b11001101);
		//delayms(5);
	}
	
	/*Start of infinite loop*/
	while(1)
	{
		send_timon_bytes(0b11001101);

		delayms(1);
	}
}

ISR( INT0_vect )
{
	//Change interrupt for rising edge/falling edge
	if(EICRA == 0x02)
	{
		//On falling edge
		if(startBitFound && edges < 9)
		{
			highTime = TCNT2;
			if(highTime > 1 && highTime < 5)
			{
				if(receivedData == 0)
				{
					//Data should be 0
				}
				else
				{
					receivedData = receivedData << 1;
				}
				edges++;
			}
			else if(highTime > 5 && highTime < 9)
			{
				if(receivedData == 0)
				{
					receivedData = 1;
				}
				else
				{
					receivedData = receivedData << 1;
					receivedData |= 1;
				}
				edges++;
			}
			else
			{
				//Corrupt bit found
				receivedData = 0;
				startBitFound = 0;
				edges = 0;
			}
			
			if(startBitFound == 1 && edges == 8)
			{
				if(!firstTimeFound)
				{
					PORTE = receivedData;
					PORTA = 0xFF;
					firstTimeFound = 1;
				}
				
				startBitFound = 0;
				edges = 0;
			}
		}

		//Change interrupt mode to rising edge
		EICRA = 0x03;
	}
	else
	{
		//On rising edge
		if(!startBitFound)
		{
			lowTime = TCNT2;
			if(lowTime > 6 && lowTime < 14)
			{
				startBitFound = 1;				
			}
		}

		//Reset high timer
		highTime = 0;

		//Change interrupt mode to falling edge
		EICRA = 0x02;
	}

	
	lowTime = 0;

	//Reset timer to 0
	TCNT2 = 0;
}

void InitInterupts(void)
{
	TCCR2 |= (1 << CS22);
	TCNT2 = 0;

	EICRA |= 0x03; // EX0, EX1: rising edge
	EIMSK |= 0x01; // enable intrpt EX0, EX1
	sei();
}

void delayms(int t)//delay in ms
{
	int i;
	for(i=0;i<t;i++)
	{
		_delay_ms(1);
	}
}


void delayus(int t)//delay in us
{
	int i;
	for(i=0;i<t;i++)
	{
		_delay_us(1);
	}
}

//send_timon_bytes(0b11001111);
void send_timon_bytes(unsigned char data)
{
	unsigned char tbit;
	int delayTime = 0;

	// make 250uS start bit first
	PORTB = 0x0;
	delayus(100);
	      
	//PORTB = 0x00;
	//delayus(500);     

	// now loop and send 8 bits
	for(tbit=0; tbit<8; tbit++)
	{
		delayTime = 0;
		PORTB = 0xFF;
		if((data & 0b10000000))
		{
			delayTime += 100;
		}
		delayTime += 100;
		delayus(delayTime);

		PORTB = 0x0;
		delayus(50);


		data = data << 1; 
	}
	PORTB = 0xFF;
}

//=============================================================================
//   SEND_RF_BYTE
//=============================================================================
void send_rf_byte(unsigned char txdat)
{
	//-------------------------------------------------------
	// This is a pulse period encoded system to send a byte to RF module.
	// Bits are sent MSB first. Each byte sends 9 pulses (makes 8 periods).
	// Timing;
	//   HI pulse width; always 80uS
	//   0 bit, LO width; 20uS (total 0 bit pulse period 100uS)
	//   1 bit, LO width; 70uS (total 1 bit pulse period 150uS)
	//   space between bytes, LO width; 170uS (total space period 250uS)
	// (timings tested with 20MHz xtal PIC 18F, no pll)
	//-------------------------------------------------------
	unsigned char tbit;

	// make 250uS start bit first
	delayus(170);      // 170uS LO
	PORTB = 0xFF;
	delayus(80-1);     // 80uS HI
	PORTB = 0x0;

	// now loop and send 8 bits
	for(tbit=0; tbit<8; tbit++)
	{
		delayus(20-1);             // default 0 bit LO period is 20uS
		if(txdat && 0b10000000)
		{
			delayus(50);  // increase the LO period if is a 1 bit!
		}
		
		PORTB = 0xFF;
		delayus(80-1);             // 80uS HI pulse
		PORTB = 0x0;
		txdat <<= 1;                // roll data byte left to get next bit
	}
}
//-----------------------------------------------------------------------------

