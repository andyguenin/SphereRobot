#define F_CPU 1000000

#include "m_general.h"

int main()
{
	set(DDRD,7);
	while(1)
	{
		toggle(PORTD, 7);		
	}	
}