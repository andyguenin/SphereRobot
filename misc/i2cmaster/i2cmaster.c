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
	m_usb_tx_string("sending address + w");
	m_usb_tx_push();
	status = send_byte(address<<1);
	m_usb_tx_string("status: ");
	m_usb_tx_uint(status);
	m_usb_tx_push();
	if(status== 0x20){ // ACK was not received - may not be connected/listening
		TWCR = (1<<TWINT)|(1<<TWEN)| (1<<TWSTO); // let go of the line (STOP)
		return 0;	// failure
	}
	PORTF = (0xF0 & status) | ((0x8 & status) >> 2);
	


    if(status == 0x18)
	{
		TWDR = 0x08;
		TWCR = (0 << TWSTA)|(0<<TWSTO)|(1<<TWINT)|(1<<TWEN);
		if(twi_wait())
		{
			status = TWSR & 0xf8;
			m_usb_tx_string("status: ");
			m_usb_tx_uint(status);
			m_usb_tx_push();
			if(status == 0x28)
			{
				TWCR = (0 <<TWSTA)|(1<<TWSTA)|(1<<TWINT);
				m_green(ON);
			}
		}
		else
		{
			m_red(ON);	
		}
	}
	/*if(status == 0x30)
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


