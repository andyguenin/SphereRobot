/*
 * _32U4IMU.c
 *
 * Created: 4/16/2012 8:17:38 PM
 *  Author: Andy
 */ 
#define F_CPU 16000000

#include "m_general.h"
//#include "m_usb.h"

char get_register_val(char, char);
char set_register_val(char address, char reg, char val);
char init(void);
void write(int);

int main(void)
{
	init();

}
/*
void write(int a)
{
	m_usb_tx_int(a);
	m_usb_tx_push();
}*/
char init()
{
	m_clockdivide(0);
	
	// ENABLE PULLUPS
	set(PORTD,0);
	set(PORTD,1);
	set(PORTD,2);
	
	// CONFIGURE THE CLOCK
	TWBR = 12;	// CLK freq = CPU clock / (16 + 2*TWBR*(4^TWPS)), 16MHz clock, TWBR=12, TWPS=00 -> 400kHz

	// ENABLE interrupts in INT2 (D2)
	set(EICRA,ISC21); clear(EICRA,ISC20); // trigger on falling edge
	set(EIMSK,INT2); // demask the interrupt
	sei(); // enable global interrupts

	m_red(ON);
	
	for(int i = 0; i < 128; i++)
	{
		TWCR = (1<<TWEN)|(1<<TWSTA)|(1<<TWINT);
		while(!(TWCR & (1<<TWINT))){};
		// ADDRESS
		TWDR = i<<1;
		TWCR = (1<<TWINT) | (1<<TWEN);
		while(!(TWCR & (1<<TWINT))){};
		if((TWSR & 0xF8) != 0x18){ // ACK was not received - may not be connected/listening
			TWCR = (1<<TWINT)|(1<<TWEN)| (1<<TWSTO); // let go of the line (STOP)
			
		}
		else
		{
			break;
		}
	}

	m_green(ON);
	// send the register address
	TWDR = 0;
		
	TWCR = (1<<TWINT) | (1<<TWEN);
	while(!(TWCR & (1<<TWINT))){};
	if((TWSR & 0xF8) != 0x28){ // ACK was not received - may not be connected/listening
		TWCR = (1<<TWINT)|(1<<TWEN)| (1<<TWSTO); // let go of the line (STOP)
		return 0;
	}
	
	TWCR = (1<<TWINT)|(1<<TWEN)| (1<<TWSTO); // let go of the line (STOP)
	m_red(ON);
	return 1;
	
}
char set_register_val(char address, char reg, char val)
{
	TWCR = (1<<TWEN)|(1<<TWSTA)|(1<<TWINT);
	while(!(TWCR & (1<<TWINT))){};
	
	// ADDRESS
	TWDR = address<<1;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while(!(TWCR & (1<<TWINT))){};
	if((TWSR & 0xF8) != 0x18){ // ACK was not received - may not be connected/listening
		TWCR = (1<<TWINT)|(1<<TWEN)| (1<<TWSTO); // let go of the line (STOP)
		return 0;
	}
	// send the register address
	TWDR = reg;
		
	TWCR = (1<<TWINT) | (1<<TWEN);
	while(!(TWCR & (1<<TWINT))){};
	if((TWSR & 0xF8) != 0x28){ // ACK was not received - may not be connected/listening
		TWCR = (1<<TWINT)|(1<<TWEN)| (1<<TWSTO); // let go of the line (STOP)
		return 0;
	}
	
	TWDR = val;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while(!(TWCR & (1<<TWINT))){};
	if((TWSR & 0xF8) != 0x28){ // ACK was not received - may not be connected/listening
		TWCR = (1<<TWINT)|(1<<TWEN)| (1<<TWSTO); // let go of the line (STOP)
		return 0;
	}
	
	TWCR = (1<<TWINT)|(1<<TWEN)| (1<<TWSTO); // let go of the line (STOP)
	return 1;	
}

char get_register_val(char address, char reg)
{
	char data = 0;
		
	TWCR = (1<<TWEN)|(1<<TWSTA)|(1<<TWINT);
	while(!(TWCR & (1<<TWINT))){};
	
	// ADDRESS
	TWDR = address<<1;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while(!(TWCR & (1<<TWINT))){};
	if((TWSR & 0xF8) != 0x18){ // ACK was not received - may not be connected/listening
		TWCR = (1<<TWINT)|(1<<TWEN)| (1<<TWSTO); // let go of the line (STOP)
		return 0;
	}
	// send the register address
	TWDR = reg;
		
	TWCR = (1<<TWINT) | (1<<TWEN);
	while(!(TWCR & (1<<TWINT))){};
	if((TWSR & 0xF8) != 0x28){ // ACK was not received - may not be connected/listening
		TWCR = (1<<TWINT)|(1<<TWEN)| (1<<TWSTO); // let go of the line (STOP)
		return 0;
	}
	// send repeat address and enter master receiver mode
	TWCR = (1<<TWSTA) | (1<<TWINT) | (1<<TWEN);
	while(!(TWCR & (1<<TWINT))){};
			
			
	TWDR = 	(address << 1) | 1;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while(!(TWCR & (1<<TWINT))){};
	if((TWSR & 0xF8) != 0x40){ // ACK was not received - may not be connected/listening
		TWCR = (1<<TWINT)|(1<<TWEN)| (1<<TWSTO); // let go of the line (STOP)
		return 0;
	}
		
	TWCR = (1<<TWINT) | (0<<TWEA) | (1<<TWEN);
	while(!(TWCR & (1<<TWINT))){};
	if((TWSR & 0xF8) != 0x58){ // ACK was not received - may not be connected/listening
		TWCR = (1<<TWINT)|(1<<TWEN)| (1<<TWSTO); // let go of the line (STOP)
		return 0;
	}		
		
	data = TWDR;
	TWCR = (1<<TWSTO) | (1<<TWINT) | (1<<TWEN);	
	return data;	
}
