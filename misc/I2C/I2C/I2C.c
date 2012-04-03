/*
 * I2C.c
 *
 * Created: 4/2/2012 6:00:47 PM
 *  Author: Andy
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#define ADDRESS 1
#define RESPOND_TO_ANNOUNCE

void init_i2c_slave_receiver();
void init_all();

#define TWI_COMM_MASK ((1<<TWEN)|(0<<TWSTO)|(0<<TWWC)|(1<<TWIE)|(1<<TWEA)|(0<<TWSTA)|(1<<TWINT))

volatile char motor_command[2];
volatile char pointer = 0;

int main(void)
{
	init_all();
	init_i2c_slave_receiver();
	while(motor_command[2]!=0x08);
	
	
}


void init_all()
{
	CLKPR = 1<<7;
	CLKPR = 0;
}


void init_i2c_slave_receiver()
{
	motor_command[0] = 0;
	motor_command[1] = 0;
	DDRD = 0x1F;
	PORTD = 0;
	TWAR = ADDRESS << 1; // sets the slave address
	//#ifdef RESPOND_TO_ANNOUNCE
		TWAR |= 1;
	//#endif
	TWDR = 0xFF;
	cli();
	TWCR = TWI_COMM_MASK;
		
	sei();
	
	while(motor_command[0] !=0x08);
	PORTD = 1;
	
}

ISR(TWI_vect)
{	
	unsigned char status = TWSR & 0xF8;
//	PORTD = status >> 3;
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