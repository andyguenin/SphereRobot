#define F_CPU 1000000

#include <avr/io.h>

#define set(port, pin) (port |= 1<<pin)
#define clear(port, pin) (port &= ~(1<<pin))

int main()
{
	DDRB &= ~(7);
	DDRD |= (1<<5|1<<6|1<<7);
	
	while(1)
	{
		if(PINB & 1)
			set(PORTD, 5);
		else
			clear(PORTD, 5);
			
		if(PINB & 2)
			set(PORTD, 6);
		else
			clear(PORTD, 6);
		
		if(PINB & 3)
			set(PORTD, 7);
		else
			clear(PORTD, 7);
		
		
	}
}