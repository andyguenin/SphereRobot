/*
 * I2C.c
 *
 * Created: 4/2/2012 6:00:47 PM
 *  Author: Andy
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "i2c.h"

#define ADDRESS 1
#define RESPOND_TO_ANNOUNCE 1


volatile char motor_command[2];
volatile char pointer = 0;

volatile char test_send = 0;
volatile char run_command = 0;

volatile char* tx_num;

int main(void)
{
	init_all();
	init_i2c_slave_receiver(ADDRESS, 0, 1);
	char a = 0xaa;
	tx_var(&a);
	sei();
	while(1)
	{
		if(command_ready())
		{
			char* m_c = command();
			switch(m_c[0])
			{
			case(CALIBRATE):
				break;
			case(IN):
				DDRB |= (1<<6)|(1<<7);
				if(m_c[1] == 2)
				{
					PORTB |= 1<<6;
				}
				else
				{
					PORTB |= 1<<7;
				}				
				break;
			case(OUT):
				break;
			case(STOP):
				DDRD |= (1<<6)|(1<<7);
				if(m_c[1] == 4)
				{
					PORTD |= 1<<6;
				}
				else
				{
					PORTD |= 1<<7;
				}	
				break;
			default:
				break;
			}			
		}
	}
	
	
}

void tx_var(char* txv)
{
	tx_num = txv;
}


void init_all()
{
	CLKPR = 1<<7;
	CLKPR = 0;
}

char command_ready()
{
	return run_command;
}

char* command()
{
	run_command = 0;
	return motor_command;
}

void init_i2c_slave_receiver(unsigned char address, unsigned char mask, unsigned char respond_to_announce)
{
	motor_command[0] = 0;
	motor_command[1] = 0;
	TWAR = address << 1; // sets the slave address
	if(respond_to_announce)
	{
		TWAR |= 1;
	}	
	TWAMR = mask << 1;
	TWDR = 0xFF;
	TWCR = TWI_COMM_MASK;
	DDRD = 0xf;
}

ISR(TWI_vect)
{	
	unsigned char status = TWSR & 0xF8;
	switch(status)
	{
		// The following are commands received in SRx mode
		case(0x60): // own SLA + W has been received, ACK returned
		case(0x70): // own GA has been received, ACK returned
			pointer = 0;
			motor_command[0] = 0;
			motor_command[1] = 0;
			TWCR = TWI_COMM_MASK; // Data byte will be received and ACK returned
			break;
		case(0x80): // already addressed with SLA, data has been received and ACK returned
		case(0x90): // already addressed with GA, data has been received and ACK returned
			if(pointer < 2)
			{
				motor_command[pointer] = TWDR;
				pointer++;
			}			
			TWCR = TWI_COMM_MASK; // Data byte will be received and ACK returned
			break;
		case(0xA0): // STOP condition or repeated START condition 
			TWCR = TWI_COMM_MASK; // Switch to the not addressed slave mode, but SLA will be recognized
			run_command = 1;
			break;				
		// The following are commands received in STx mode
		case(0xA8): // Own SLA+R has been received, ACK has been returned
			if(motor_command[0] == TX)
			{
				TWDR = *(tx_num);
				TWCR = (TWI_COMM_MASK & (~(1<<TWEA)));
			}
			break;
		case(0xB8):	// Data byte in TWDR has bee Txed, ACK received	
			break;
		case(0xC8):
		case(0xC0): // Last data byte has been transmitted
			TWDR = 0;
			TWCR = TWI_COMM_MASK; // switched to non addressed slave mode, sla will be recog
			break;
		default: // Something unexpected happened
			break;
	}
}