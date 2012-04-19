/*
 * _32U4IMU.c
 *
 * Created: 4/16/2012 8:17:38 PM
 *  Author: Andy
 */ 
#define F_CPU 16000000

#include "m_general.h"
#include "m_usb.h"

char get_register_val(char, char);
char set_register_val(char address, char reg, char val);
void init(void);
void write(int);
char send_instruc(char address, char inst);

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
void init()
{
	m_clockdivide(0);
	
	// ENABLE PULLUPS
	set(PORTD,0);
	set(PORTD,1);
	set(PORTD,2);
	
	// CONFIGURE THE CLOCK
	TWBR = 12;	// CLK freq = CPU clock / (16 + 2*TWBR*(4^TWPS)), 16MHz clock, TWBR=12, TWPS=00 -> 400kHz
	
	char address = 0x69;
	char list[12];
	set_register_val(address, 107,0);
	set_register_val(address, 27, 8);


	
	m_usb_init();
	m_red(ON);
	while(!m_usb_isconnected());
	m_green(ON);
	m_red(OFF);
	while(1)
	{
		if(m_usb_rx_available())
		{

			char val = m_usb_rx_char();
			if(val == 5)
			{
				int offset= 59;
				int start = 0;
				for(start = 0; start+offset <= 72; start++)
				{
					if(start+offset == 65)
					{
						offset +=2;
					}
					list[(start/2)*2 + (1-start%2)] = get_register_val(address, start + offset);
				
				}
				m_usb_tx_char(list[0]);
				m_usb_tx_char(list[1]);
				m_usb_tx_char(list[2]);
				m_usb_tx_char(list[3]);
				m_usb_tx_char(list[4]);
				m_usb_tx_char(list[5]);
				m_usb_tx_char(list[6]);
				m_usb_tx_char(list[7]);
				m_usb_tx_char(list[8]);
				m_usb_tx_char(list[9]);
				m_usb_tx_char(list[10]);
				m_usb_tx_char(list[11]);
				m_usb_tx_push();

			}
			else
			{
				while(!m_usb_rx_available());
				char address = val;
				char inst = m_usb_rx_char();
				if(send_instruc(address, inst))
				{
				}
				else
				{
					m_red(ON);
				}
			}
		}
	}
}

char send_instruc(char address, char inst)
{

	TWCR = (1<<TWEN)|(1<<TWSTA)|(1<<TWINT);
	while(!(TWCR & (1<<TWINT))){};
	// ADDRESS
	TWDR = address<<1;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while(!(TWCR & (1<<TWINT))){};
	if((TWSR & 0xF8) != 0x18){ // ACK was not received - may not be connected/listening
		TWCR = (1<<TWINT)|(1<<TWEN)| (1<<TWSTO); // let go of the line (STOP)
		return 1;
	}
	else
	{
		TWDR = inst;
		TWCR = (1<<TWINT) | (1<<TWEN);

		while(!(TWCR & (1<<TWINT))){};
			if((TWSR & 0xF8) != 0x28){ // ACK was not received - may not be connected/listening
			TWCR = (1<<TWINT)|(1<<TWEN)| (1<<TWSTO); // let go of the line (STOP)
			return 1;
		}

		TWCR = (1<<TWINT)|(1<<TWEN)| (1<<TWSTO); // let go of the line (STOP)
	}
	return 0;

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
