#include "m_general.h"
#include "m_bus.h"
#include "m_usb.h"
#include <string.h>

#define MWIITWIADDR		0x58
#define TWI_MAX_WAIT	1000
#define INTERPACKET		10


unsigned char send_byte(unsigned char byte);
unsigned char twi_wait(void);
void end(void);
unsigned char get_motor_speed(void);
char send_data(char command, char data);


void wait()
{
	m_wait(1000);
}

unsigned char address = 1;

int main()
{
	m_clockdivide(0);
	m_bus_init();
	
	m_usb_init();
	while(!m_usb_isconnected());
	m_green(ON);
	TWBR = 43;

	for(int i = 0; i < 3; i ++)
	{	
		m_wait(2000);
	}
	m_green(OFF);

	m_usb_tx_string("value: ");
	int send = (int)(get_motor_speed());
	m_usb_tx_uint(send);
	m_usb_tx_push();
	send_data(0x01, 0x02);
	m_red(ON);
	m_usb_tx_string("sent1: ");
	m_usb_tx_push();
	send_data(0x03, 0x04);
	m_usb_tx_string("sent2: ");
	m_usb_tx_push();

	
	// START

}

unsigned char get_motor_speed()
{
	unsigned char status;
	TWCR = (1<<TWEN)|(1<<TWSTA)|(1<<TWINT); // Enables TWI, tries to become master, and clears the interrupt flag
	if(!twi_wait())
	{
		return 0;
	}
	DDRF |= 0xF2;
	PORTF = 0;
	// ADDRESS
	status = send_byte((address<<1)); // 0x08 start cond trans

	if(status== 0x20){ // ACK was not received - may not be connected/listening
		TWCR = (1<<TWINT)|(1<<TWEN)| (1<<TWSTO); // let go of the line (STOP)
		return 0;	// failure
	}
	//PORTF = (0xF0 & status) | ((0x8 & status) >> 2);
	if(status == 0x18) //SLA+W txed, ack received
	{
		TWDR = 0x04;
		TWCR = (0<<TWSTA)|(0<<TWSTO)|(1<<TWINT)|(1<<TWEN); //data will be txed
		while(!(TWCR & (1<<TWINT)));
		status = TWSR & 0xF8;
		if(status  != 0x28)
			return 0;
		TWCR = (1<<TWSTA)|(0<<TWSTO)|(1<<TWINT)|(1<<TWEN); // data  has been txed
		while(!(TWCR & (1<<TWINT)));
		status = TWSR & 0xF8;
		if(status != 0x10)
			return 0;
		TWDR = ((address << 1)|1);
		TWCR = (0<<TWSTA)|(0<<TWSTO)|(1<<TWINT)|(1<<TWEN);
		while(!(TWCR & (1<<TWINT)));
		status = TWSR & 0xF8;
		if(status != 0x40)
			return 0;
		TWCR= (1<<TWEN)|(0<<TWSTA)|(0<<TWSTO)|(1<<TWINT)|(0<<TWEA);
		while(!(TWCR & (1<<TWINT)));
		status = TWSR & 0xF8;
		if(status != 0x58)
			return 0;
		char data = TWDR;
		TWCR = (0<<TWSTA)|(1<<TWSTO)|(1<<TWINT)|(1<<TWEN);
		return data;
	}
	return 0x00;
}


char send_data(char command, char data)
{
	unsigned char status=0;
	TWCR = (1<<TWEN)|(1<<TWSTA)|(1<<TWINT); // Enables TWI, tries to become master, and clears the interrupt flag
	while(!(TWCR & (1<<TWINT)));
	status = 0xf8 & TWSR;
	status = send_byte((address<<1));
	if(status== 0x20){ // ACK was not received - may not be connected/listening
		TWCR = (1<<TWINT)|(1<<TWEN)| (1<<TWSTO); // let go of the line (STOP)
		return 0;	// failure
	}
	//PORTF = (0xF0 & status) | ((0x8 & status) >> 2);
	if(status == 0x18)
	{
		TWDR = command;
		TWCR = (0<<TWSTA)|(0<<TWSTO)|(1<<TWINT)|(1<<TWEN); //data will be txed
		while(!(TWCR & (1<<TWINT)));
		status = TWSR & 0xF8;
		if(status  != 0x28)
			return 0;
		TWDR = data;
		TWCR = (0<<TWSTA)|(0<<TWSTO)|(1<<TWINT)|(1<<TWEN); // data  has been txed
		while(!(TWCR & (1<<TWINT)));
		status = TWSR & 0xF8;
		if(status != 0x28)
			return 0;
		TWCR = (0<<TWSTA)|(1<<TWSTO)|(1<<TWINT)|(1<<TWEN);		
		return 1;

	}
	return 0;
}

/*
    if(status == 0x40)
	{
		int received = 0;
		TWCR = (0 << TWSTA)|(0<<TWSTO)|(1<<TWINT)|(1<<TWEA)|(1<<TWEN);
		int cont = 1;
		while(cont)
		{
			while(!(TWCR & (1<<TWINT)));

			{
				int ss = TWSR & 0xf8;
					m_usb_tx_string("status: ");
					m_usb_tx_uint(ss);
					m_usb_tx_push();
				if(ss == 0x50)
				{
					m_usb_tx_string("received: ");
					received = TWDR;
					m_usb_tx_int(received);
					m_usb_tx_string(":end;;;;;;");
					m_usb_tx_push();
					m_wait(1000);
					if(received != 10)
					{
						TWCR = (0 <<TWSTA)|(0<<TWSTO)|(1<<TWINT)|(1<<TWEA)|(1<<TWEN);
					}
					else
					{
						TWCR = (0 <<TWSTA)|(0<<TWSTO)|(1<<TWINT)|(0<<TWEA)|(1<<TWEN);
					}
					m_green(ON);
				}
				if(ss == 0x58)
				{
					TWCR = (0<<TWSTA)|(1<<TWSTO)|(1<<TWINT)|(1<<TWEN);
					m_green(OFF);
					cont = 0;
				}
			}
		}
	}
	else
	{
		m_red(ON);
	}
	if(status == 0x30)
	{
		status = send_byte(8);
		if(status == 0x28)
		{
			m_green(ON);
		}
		else
		{
			return 0;
		}
	}
	else
	{
		m_red(ON);
	}	*/	



unsigned char send_byte(unsigned char byte)
{
	TWDR = byte;					// load the byte
	TWCR = (1<<TWINT) | (1<<TWEN);	// send the byte
	if(twi_wait())					// timed out
	{
		return (TWSR & 0xF8);		// return the status with prescaler bits masked out
	} else {
		return 0;					// comm failure
	}
}

unsigned char twi_wait(void)
{
	unsigned int wait=0;
	while((!(TWCR & (1<<TWINT))) && (wait++<TWI_MAX_WAIT)){};	// wait for acknowledgement that they byte was sent
	if(wait==TWI_MAX_WAIT)
	{
		return 0;					// fail
	} else {
		return 1;					// success
	}
}


