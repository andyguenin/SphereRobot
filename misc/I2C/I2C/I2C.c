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




int main(void)
{
	init_all();
	init_i2c_slave_receiver(ADDRESS, 0, 1);
	while(motor_command[2]!=0x08);
	
	
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
	cli();
	TWCR = TWI_COMM_MASK;	
}

ISR(TWI_vect)
{	
	unsigned char status = TWSR & 0xF8;
	switch(status)
	{
		case(0x60): 
		case(0x70):
			pointer = 0;
			TWCR = TWI_COMM_MASK;
			break;
		case(0x80):
		case(0x90):
			motor_command[pointer] = TWDR;
			pointer++;
			TWCR = TWI_COMM_MASK;
			break;
		case(0xA0):
			TWCR = TWI_COMM_MASK;
			break;		
		default:
			break;
	}
}