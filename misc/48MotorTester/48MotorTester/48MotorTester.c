/*
 * _48MotorTester.c
 *
 * Created: 3/13/2012 5:22:26 PM
 *  Author: Andy
 */ 

#include "m_general.h"
#include "m_usb.h"

#define showlights

void init();

int main(void)
{
	init();
	while(1)
	{
		
		while(!m_usb_rx_available());
		char rx = m_usb_rx_char();
		switch(rx)
		{
			case 3:
				m_green(OFF);
				m_red(OFF);
				clear(PORTB, 2);
				clear(PORTB, 3);
				break;
			case 2:
				clear(PORTB, 2);
				set(PORTB,3);
				#ifdef showlights
				m_red(OFF);
				m_green(ON);
				#endif
				break;
			case 1:
				set(PORTB, 2);
				clear(PORTB,3);
				#ifdef showlights
				m_green(OFF);
				m_red(ON);
				#endif
			default:
				break;
		}				
	}
}

void init()
{
	m_clockdivide(0);
	
	m_usb_init();
	while(!m_usb_isconnected());
	for(int i=0;i<4;i++)
	{
		m_green(ON);
		m_wait(100);
		m_green(OFF);
		m_wait(100);
	}
	
	set(DDRB, 2);
	set(DDRB, 3);
	
	
	
}