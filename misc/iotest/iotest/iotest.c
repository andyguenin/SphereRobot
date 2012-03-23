#define F_CPU 1000000

#include "m_general.h"

int main()
{
	/*set(DDRD, 5);
	set(DDRD, 6);
	set(DDRD, 7);
	clear(DDRB, 1);
	clear(DDRB, 2);
	(DDRB, 3);
	
	set(PORTD, 5);
	set(PORTD, 6);
	set(PORTD, 7);
	
	
	while(1)
	{
		if(check(PINB, 1))
			set(PORTD, 7);
		else
			clear(PORTD, 7);
		if(check(PINB, 2))
			set(PORTD, 6);
		else
			clear(PORTD, 6);
		if(check(PINB, 3))
			set(PORTD, 5);
		else
			clear(PORTD, 5);
	}*/
	
	set(DDRD, 4);
	set(DDRD, 3);
	while(1)
	{
		toggle(PORTD, 3);
		toggle(PORTD, 4);
	}
	
}