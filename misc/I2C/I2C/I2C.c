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
volatile char command;

volatile char test_send = 0;


int main(void)
{
	init_all();
	init_i2c_slave_receiver(ADDRESS, 0, 1);
	sei();
	while(1);
	
	
}


void init_all()
{
	CLKPR = 1<<7;
	CLKPR = 0;
}


void init_i2c_slave_receiver(unsigned char address, unsigned char mask, unsigned char respond_to_announce)
{
	motor_command[0] = 0;
	motor_command[1] = 0;
	DDRD = 0x1F;
	PORTD = 0;
	TWAR = address << 1; // sets the slave address
	if(respond_to_announce)
	{
		TWAR |= 1;
	}	
	TWAMR = mask << 1;
	TWDR = 0xFF;
	TWCR = TWI_COMM_MASK;
	PORTD |= 1;	
}

ISR(TWI_vect)
{	
	unsigned char status = TWSR & 0xF8;
	PORTD = status >> 2;
	switch(status)
	{
		// The following are commands received in SRx mode
		case(0x60): // own SLA + W has been received, ACK returned
		case(0x70): // own GA has been received, ACK returned
			pointer = 0;
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
			break;				
		// The following are commands received in STx mode
		case(0xA8): // Own SLA+R has been received, ACK has been returned
			if(motor_command[0] == 0x01)
			{
				PORTD |= 1;
				TWDR = 0x08;
				TWCR = TWI_COMM_MASK & (~(1<<TWEA));
			}
			if(motor_command[0] == 0x02)
			{
				TWDR = 0x0a;
				TWCR = TWI_COMM_MASK;
				test_send = 1;
			}
			
			break;
		case(0xB8):	// Data byte in TWDR has bee Txed, ACK received

			
			if(motor_command[0] == 0x02)
			{
				TWDR = 0x09;
				TWCR = TWI_COMM_MASK & (~(1<<TWEA));			
			}						
				
			break;
		case(0xC8): // Last data byte has been transmitted
			TWCR = TWI_COMM_MASK & ~(1<<TWEA); // switched to non addressed slave mode, sla will be recog
			break;
		default: // Something unexpected happened
			break;
	}
}