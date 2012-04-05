#include "m_general.h"
#include "m_bus.h"
#include "m_usb.h"

#define MWIITWIADDR		0x58
#define TWI_MAX_WAIT	1000
#define INTERPACKET		10


unsigned char start_write(unsigned char address);
unsigned char start_read(unsigned char address);
unsigned char send_byte(unsigned char byte);
unsigned char twi_wait(void);
void end(void);


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

	unsigned char address = 1;
	unsigned char status;
	// START
	TWCR = (1<<TWEN)|(1<<TWSTA)|(1<<TWINT); // Enables TWI, tries to become master, and clears the interrupt flag
	if(!twi_wait())
	{
		return 0;
	}
	DDRF |= 0xF2;
	PORTF = 0;
	// ADDRESS
	m_usb_tx_string("sending address + r");
	m_usb_tx_push();
	status = send_byte((address<<1));
	m_usb_tx_string("status: ");
	m_usb_tx_uint(status);
	m_usb_tx_push();
	if(status== 0x20){ // ACK was not received - may not be connected/listening
		TWCR = (1<<TWINT)|(1<<TWEN)| (1<<TWSTO); // let go of the line (STOP)
		return 0;	// failure
	}
	//PORTF = (0xF0 & status) | ((0x8 & status) >> 2);
	m_usb_tx_string("status: ");
	m_usb_tx_uint(status);
	m_usb_tx_push();
	if(status == 0x18)
	{
		TWDR = 0x01;
		TWCR = (0<<TWSTA)|(0<<TWSTO)|(1<<TWINT)|(1<<TWEN);
		while(!(TWCR & (1<<TWINT)));
		status = TWSR & 0xF8;
		m_usb_tx_string("status: ");
		m_usb_tx_uint(status);
		m_usb_tx_push();
		TWCR = (1<<TWSTA)|(0<<TWSTO)|(1<<TWINT)|(1<<TWEN);
		while(!(TWCR & (1<<TWINT)));
		status = TWSR & 0xF8;
		m_usb_tx_string("status: ");
		m_usb_tx_uint(status);
		m_usb_tx_push();
		TWDR = ((address << 1)|1);
		TWCR = (0<<TWSTA)|(0<<TWSTO)|(1<<TWINT)|(1<<TWEN);
		while(!(TWCR & (1<<TWINT)));
		status = TWSR & 0xF8;
		m_usb_tx_string("status: ");
		m_usb_tx_uint(status);
		m_usb_tx_push();
		if(status != 0x40)
			return 0;
		TWCR= (1<<TWEN)|(0<<TWSTA)|(0<<TWSTO)|(1<<TWINT)|(0<<TWEA);
		while(!(TWCR & (1<<TWINT)));
		status = TWSR & 0xF8;
		m_usb_tx_string("status: ");
		m_usb_tx_uint(status);
		m_usb_tx_push();
		if(status != 0x58)
			return 0;
		m_usb_tx_string("value: ");
		m_usb_tx_uint(TWDR);
		m_usb_tx_push();
		if(TWDR == 0x08)
		{
			TWCR = (1<<TWSTA)|(0<<TWSTO)|(1<<TWINT)|(1<<TWEN);
			m_green(ON);
		}
	}
	else
	{
		m_red(ON);
	}


	TWCR = (1<<TWEN)|(1<<TWSTA)|(1<<TWINT); // Enables TWI, tries to become master, and clears the interrupt flag
	while(!(TWCR & (1<<TWINT)));
	status = 0xf8 & TWSR;
	m_usb_tx_string("status: ");
	m_usb_tx_uint(status);
	m_usb_tx_push();
	m_usb_tx_string("sending address + r");
	m_usb_tx_push();
	status = send_byte((address<<1));
	m_usb_tx_string("status: ");
	m_usb_tx_uint(status);
	m_usb_tx_push();
	if(status== 0x20){ // ACK was not received - may not be connected/listening
		TWCR = (1<<TWINT)|(1<<TWEN)| (1<<TWSTO); // let go of the line (STOP)
		return 0;	// failure
	}
	//PORTF = (0xF0 & status) | ((0x8 & status) >> 2);
	m_usb_tx_string("status: ");
	m_usb_tx_uint(status);
	m_usb_tx_push();
	if(status == 0x18)
	{
		TWDR = 0x02;
		TWCR = (0<<TWSTA)|(0<<TWSTO)|(1<<TWINT)|(1<<TWEN);
		while(!(TWCR & (1<<TWINT)));
		status = TWSR & 0xF8;
		m_usb_tx_string("status: ");
		m_usb_tx_uint(status);
		m_usb_tx_push();
		TWCR = (1<<TWSTA)|(0<<TWSTO)|(1<<TWINT)|(1<<TWEN);
		while(!(TWCR & (1<<TWINT)));
		status = TWSR & 0xF8;
		m_usb_tx_string("status: ");
		m_usb_tx_uint(status);
		m_usb_tx_push();
		TWDR = ((address << 1)|1);
		TWCR = (0<<TWSTA)|(0<<TWSTO)|(1<<TWINT)|(1<<TWEN);
		while(!(TWCR & (1<<TWINT)));
		status = TWSR & 0xF8;
		m_usb_tx_string("status: ");
		m_usb_tx_uint(status);
		m_usb_tx_push();
		if(status != 0x40)
			return 0;
		TWCR= (1<<TWEN)|(0<<TWSTA)|(0<<TWSTO)|(1<<TWINT)|(1<<TWEA);
		while(!(TWCR & (1<<TWINT)));
		status = TWSR & 0xF8;
		m_usb_tx_string("status: ");
		m_usb_tx_uint(status);
		m_usb_tx_push();
		if(status != 0x40)
			return 0;
		m_usb_tx_string("value: ");
		m_usb_tx_uint(TWDR);
		m_usb_tx_push();
		TWCR= (1<<TWEN)|(0<<TWSTA)|(0<<TWSTO)|(1<<TWINT)|(0<<TWEA);
		while(!(TWCR & (1<<TWINT)));
		status = TWSR & 0xF8;
		m_usb_tx_string("status: ");
		m_usb_tx_uint(status);
		m_usb_tx_push();
		if(status != 0x58)
			return 0;
		m_usb_tx_string("value: ");
		m_usb_tx_uint(TWDR);
		m_usb_tx_push();
		if(TWDR == 0x0a)
		{
			TWCR = (0<<TWSTA)|(1<<TWSTO)|(1<<TWINT)|(1<<TWEN);
			m_green(ON);
		}
	}
	else
	{
		m_red(ON);
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
}

unsigned char start_write(unsigned char address)
{
	unsigned char status;
	// START
	TWCR = (1<<TWEN)|(1<<TWSTA)|(1<<TWINT);
	if(!twi_wait())
	{
		return 0;
	}
	
	// ADDRESS
	status = send_byte(address<<1);
	if(status== 0x20){ // ACK was not received - may not be connected/listening
		TWCR = (1<<TWINT)|(1<<TWEN)| (1<<TWSTO); // let go of the line (STOP)
		return 0;	// failure
	}	
	return 1;	// success
}	

unsigned char start_read(unsigned char address)
{
	unsigned char status;
	// START
	TWCR = (1<<TWEN)|(1<<TWSTA)|(1<<TWINT);
	if(!twi_wait())
	{
		return 0;
	}
	
	// ADDRESS
	status = send_byte(((address<<1) + 1));
	if(status== 0x48){ // ACK was not received - may not be connected/listening
		TWCR = (1<<TWINT)|(1<<TWEN)| (1<<TWSTO); // let go of the line (STOP)
		return 0;	// failure
	}	
	return 1;	// success
}	

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


