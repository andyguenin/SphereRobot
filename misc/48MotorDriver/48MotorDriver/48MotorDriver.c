/* This file has been prepared for Doxygen automatic documentation generation.*/
/*! \file *********************************************************************
 *
 * \brief A (slightly) modified version of the AVR 443 example project 
 *
 * This code has been modified from the original version, published by AVR,
 * in order to compile on a GCC compiler.  
 *
 * \par Application note:
 * AVR443: Sensorbased control of three-phase BLDC motor
 * \par
 * For comprehensive code documentation, supported compilers, compiler settings
 * and supported devices see readme.html\n
* Target device: ATmega48/88/168
 *
 * \author               Atmel Corporation: http://www.atmel.com \n
 *                       Support email: avr@atmel.com
 *
 * $Name$
 * $Revision: 2441 $
 * $RCSfile$
 * $Date: 2007-09-18 07:56:18 +0200 (ti, 18 sep 2007) $  \n
 ******************************************************************************/
#include <avr/io.h>
#include <avr/interrupt.h>
#include "sensor_three_phase_BLDC.h"
#include "i2c.h"
#include <avr/wdt.h>

#define ADDRESS 2
#define SPEED 70
#define EXTENT 1000

void Set_Speed(unsigned char speed);
void Set_Direction(unsigned char direction);
void brake();
void unbrake();
char limit_switch();

char current_direction = 0;

/*! \brief CCW rotation patterns.
 *
 * Configuration of pin drive levels
 * and timer COM bits in different
 * phases for CounterClockWise rotation.
 */
unsigned char drvPatternsCCW[] = {
  0,    //Stop
  // MC_PORT drive config
  PDP2_CCW, //Phase2
  PDP4_CCW, //Phase4
  PDP3_CCW, //Phase3
  PDP6_CCW, //Phase6
  PDP1_CCW, //Phase1
  PDP5_CCW, //Phase5
  // Configuration of Output Compare operation for timer 0
  COM0P2_CCW, //Phase2
  COM0P4_CCW, //Phase4
  COM0P3_CCW, //Phase3
  COM0P6_CCW, //Phase6
  COM0P1_CCW, //Phase1
  COM0P5_CCW, //Phase5
  // Configuration of Output Compare operation for timer 2
  COM2P2_CCW, //Phase2
  COM2P4_CCW, //Phase4
  COM2P3_CCW, //Phase3
  COM2P6_CCW, //Phase6
  COM2P1_CCW, //Phase1
  COM2P5_CCW  //Phase5
};

char limit_switch()
{
	return (PINB & (1<<7));
}

void turn_on()
{
	PORTB |= (1<<7);
}

void turn_off()
{
	PORTB &= ~(1<<7);
}

/*! \brief CW rotation patterns.
 *
 * Configuration of pin drive levels
 * and timer COM bits in different
 * phases for ClockWise rotation.
 */
unsigned char drvPatternsCW[] = {
  0,    //Stop
  // MC_PORT drive config
  PDP2_CW, //Phase2
  PDP6_CW, //Phase6
  PDP1_CW, //Phase1
  PDP4_CW, //Phase4
  PDP3_CW, //Phase3
  PDP5_CW,  //Phase5
  // Configuration of Output Compare operation for timer 0
  COM0P2_CW, //Phase2
  COM0P6_CW, //Phase6
  COM0P1_CW, //Phase1
  COM0P4_CW, //Phase4
  COM0P3_CW, //Phase3
  COM0P5_CW,  //Phase5
  // Configuration of Output Compare operation for timer 2
  COM2P2_CW, //Phase2
  COM2P6_CW, //Phase6
  COM2P1_CW, //Phase1
  COM2P4_CW, //Phase4
  COM2P3_CW, //Phase3
  COM2P5_CW  //Phase5
};



//! Stores the current motor driver pattern.

register unsigned char *pDrvPattern asm("r14");




//! Used for optimized temporary variables.
register union _fastTemp{
	unsigned int word;
	struct{
		unsigned char LByte;
		unsigned char HByte;
	};
} fastTemp asm("r12");

	
register unsigned char hallMask asm("r11");
//__regvar __no_init unsigned char hallMask @11; //!< Workaround for internal compiler error
//register unsigned char count asm("r10");
//__regvar __no_init unsigned char count @10; //!< Optimized variable decremented every pin change int.
unsigned int count = 0;


/*! \brief  Pin Change Interrupt Service Routine.
 *
 * Updates the PWM outputs controlling the low side of the driver and
 * the IO controlling the high side of the driver. To ensure a speed
 * optimal interrupt the variables used in the interrupt are placed
 * in reserved registers (locked for this purpose only). Further, the
 * information required to do the commutation is placed in tables that
 * are accessed very efficiently using the Hall sensor input signals
 * as offset.
 *
 *  \param void
 *
 *  \return void
 */
//!
ISR(PCINT0_vect)
{
 PORTD ^= 1;

  unsigned char *pTemp;
  fastTemp.word = (PIN_HALL & hallMask);  // Read Hall, Mask Pins, shift to use as pointer offset
//  Line below is desirable performance wise, but causes an internal error in compiler
//  fastTemp.LByte = (PIN_HALL & HALL_MASK)>>1;   // Read Hall, Mask Pins, shift to use as pointer offset

  pTemp = pDrvPattern + fastTemp.word;
//  TCCR0A = fastTemp.HByte; //Disable PWM outputs (and thereby close low side FET)
//  TCCR2A = fastTemp.HByte; //Disable PWM output (and thereby close low side FET)

  PORT_MC = *(pTemp);    //Change drive levels on high side

  TCCR0A = *(pTemp + PATTERN_COM0_OFFSET);    // Reconfigure output compare operation for T0
  TCCR2A = *(pTemp + PATTERN_COM2_OFFSET); // Reconfigure output compare operation for T2
 
 // if(current_direction == COUNTERCLOCKWISE)
  //{
//	  count--;
 // }
 // else
  //{
//	  count++;
 // }
 
}


/*! \brief  Initialize pin change interrupts for PORTB pin 1, 2 and 3.
 *
 * Sets up the pins used to sense the Hall sensor signals to generate
 * interrupt if the pin level changes (both rising and falling edge).
 *
 *  \param void
 *
 *  \return void
 */
static void Init_MC_pin_change_interrupt( void )
{

  PCMSK0 = (1<<PCINT0)|(1<<PCINT1)|(1<<PCINT2); //Enable pin change interrupt on PB1:3
  PCICR = 1<<PCIE0;    // Enable pin change interrupt0 (PORTB)
}


void brake()
{
	cli();
	PCICR &= ~(1<<PCIE0);
	sei();
	PORTD &= ~(148);
}

void unbrake()
{
	cli();
	PCICR |= (1<<PCIE0);
	sei();
	DDR_HALL |= HALL_MASK;    //Lock HALL sensor by driving Hall lines
	PORT_HALL |= HALL_MASK;
	PORT_HALL &= ~HALL_MASK;  //Release HALL sensor lines and trigger PC interrupt
	DDR_HALL &= ~HALL_MASK;
}



//!
/*! \brief  Initialize motor control timers.
 *
 * Initialize the Timer 1 and timer 2 to run in phase and frequency correct
 * PWM mode (symmetric PWM). The base frequency is set to 32kHz (can be
 * reduced at the expense of lower resolution on the speed control). The
 * functions also ensures that the timers are counting in sync.
 *
 *  \param void
 *
 *  \return void
 */
static void Init_MC_timers( void )
{
  //Timer Counter 0. OCRA and OCRB used for motor
 TCCR0A = (1<<COM0A1)|(0<<COM0A0)|        // Clear OCRA on compare match
           (1<<COM0B1)|(0<<COM0B0)|        // Clear OCRB on compare match
           (1<<WGM01)|(1<<WGM00);         // Fast PWM mode
  TCCR0B = (0<<FOC0A)|(0<<FOC0B)|
           (0<<WGM02)|                     // Fast PWM mode
           (1<<CS02)|(0<<CS01)|(1<<CS00); // Prescaler = CLK/1024

  //Timer Counter 2. OCRA and OCRB used for motor
  TCCR2A = (0<<COM2A1)|(0<<COM2A0)|        // OCRA not connected
           (1<<COM2B1)|(0<<COM2B0)|        // Clear OCRB on compare match
           (1<<WGM01)|(1<<WGM00);         // Fast PWM mode
  TCCR2B = (0<<FOC2A)|(0<<FOC2B)|
           (0<<WGM22)|                     // Fast PWM mode
           (1<<CS22)|(1<<CS21)|(1<<CS20); // Prescaler = CLK/1024
	
  // Synchronize timers
  TCNT0 = 0;
  TCNT2 = 3;

  TIFR0 = TIFR0;    // Clear TC0 interrupt flags
  TIFR2 = TIFR2;    // Clear TC2 interrupt flags
}




/*! \brief Set motor speed.
 *
 * Updates the output compare registers of the timer 0 and timer 2 which
 * control the duty cycle of the PWM output and thereby the speed of the
 * motor. The method used ensures that that all PWM channels are behaving
 * same duty cycle.
 *
 *  \param speed Compare match value that defines PWM duty cycle.
 *
 *  \return void
 */
void Set_Speed(unsigned char speed)
{
  TIFR0 = TIFR0;    // Clear TC0 interrupt flags
  while( !(TIFR0 & (1<<TOV0)));  // Wait for TOV to ensure that all registers are
                            //  updated in the same timer cycle
  cli();
  OCR0A = speed;        // Change the duty cycle
  OCR0B = speed;
  OCR2B = speed;
  
  sei();
}



/*! \brief Set motor direction, CW og CCW.
 *
 * Set the commutation table pointer up to point at either the clockwise
 * or counter clockwise direction table. Note that it is not recommended
 * to change direction without first reducing the speed of the motor,
 * preferably stopping it fully.
 *
 *  \param direction Direction is given as Clockwise or Counter Clockwise.
 *
 *  \return void
 */
void Set_Direction(unsigned char direction)
{
	current_direction = direction;
	if(direction == CLOCKWISE)
	{
		cli();        //Variable also used in interrupt and access most be protected
		pDrvPattern = drvPatternsCW;   // Set dir to CW, by pointing to CW pattern
		sei();
	}
	else
	{
		cli();        //Variable also used in interrupt and access most be protected
		pDrvPattern = drvPatternsCCW;   // Set dir to CCW, by pointing to CCW pattern
		sei();
	}
}



/*! \brief Main function for motor control example.
 *
 * Initialize speed variables to zero speed, and enabled operation in clockwise
 * direction. Hence a speed reference input is read from ADC_MUX_SPEED_REF. If
 * Current exeeds the MAX_CURRENT_ADC limit the speed (PWM duty cycle) is reduced.
 *
 *  \param void
 *
 *  \return void
 */



int main( void )
{

	CLKPR = (1<<CLKPCE); 
	CLKPR=0x01;
	DDRD |= 1;
	PORTD |= 1;
	MCUCR |= (1<<PUD);  // Disable all pull-ups
	hallMask = HALL_MASK; // Initialize hallMask variable
	//Set initial direction.
	Set_Direction( CLOCKWISE );  
	Init_MC_timers();
	Init_MC_pin_change_interrupt();
	init_i2c_slave_receiver(ADDRESS, 0, 0); // open I2C channel, ?, do not respond to GA

	DDR_HALL |= HALL_MASK;    //Lock HALL sensor by driving Hall lines
	PORT_HALL |= HALL_MASK;
	PORT_HALL &= ~HALL_MASK;  //Release HALL sensor lines and trigger PC interrupt
	DDR_HALL &= ~HALL_MASK;
	sei();
  
	DDR_MC = MC_MASK;        // Enable outputs

	DDRB &= ~(1<<7); // limitswitch on input
  
	Set_Speed(0);
	brake();
	
	char switching = 0;
	char switch_direction = CLOCKWISE;
	char speed = 0;
	char in_command = 0;
	PORTD &= ~1;
	while(1)
	{
		if(switching)
		{
			
			Set_Direction(switch_direction);
			Set_Speed(speed);
			unbrake();
			
			if(in_command == CALIBRATE)
			{
			//	PORTD |= 1;
			unsigned char spd=0;
			unsigned int counter=0;
				while(!limit_switch()){
					if(counter++>80)
					{
						counter = 0;
						spd++;
					//	PORTD ^= 1;
					}
					if(spd>20){
						spd=20;
					}
					Set_Speed(spd);
					
				}
			//	PORTD &= ~1;
				
			}
			else
			{
				if(in_command == IN)
				{
					while(!limit_switch() && !(count < 40));
				}
				else
				{
					if(in_command == OUT)
					{
						while(!limit_switch() && !(count > EXTENT - 10));
					}
				}
			}
			brake();
			Set_Speed(0);				
			switching = 0;
		}
		
		if(command_ready())
		{
			char* m_c = command();
			in_command = m_c[0];
			switch(m_c[0])
			{
				case CALIBRATE:
					speed = 0;
					switch_direction = COUNTERCLOCKWISE;
					break;
				case IN:
					speed = SPEED;
					switch_direction = COUNTERCLOCKWISE;
					break;
				case OUT:
					speed = SPEED;
					switch_direction = CLOCKWISE;
					break;
					
			}
			switching = 1;
		}
	}
	
	/*
	Set_Direction(COUNTERCLOCKWISE);
	Set_Speed(155);
	unbrake();
	while(!limit_switch());
	Set_Speed(0);
	brake();
	while(1);*/
  /*
	count = 0;
	wdt_reset();
	wdt_enable(WDTO_1S);
	while(1)
	{
		
		if(command_ready())
		{
			char* m_c = command();
			switch(m_c[0])
			{
				case CALIBRATE:
									
					break;
				case IN:
					Set_Direction(CLOCKWISE);
					Set_Speed(175);
					unbrake();
					
					break;
				case OUT:
					Set_Speed(0);
					brake();
					break;
				default:
					break;
			
			}

		}				
	}

	while(1) {
		char* m_c = command();
		switch(m_c[0])
		{
			case(CALIBRATE):
				unbrake();
				Set_Direction(COUNTERCLOCKWISE);
				Set_Speed(100);				
				while(!(PINB & (1<<7)));
				count = 0;
				Set_Speed(0);
				brake();
				break;
			case(IN):
				Set_Speed(0);
				brake();
				Set_Direction(COUNTERCLOCKWISE);
				Set_Speed(100);
				while(count >= 10 && (PINB & (1<<7)) == 0);
				Set_Speed(0);
				brake();
				break;
			case(OUT):
				unbrake();
				Set_Direction(CLOCKWISE);
				Set_Speed(100);
				Set_Direction(CLOCKWISE);
				Set_Speed(100);
				while(count < 1000);
				Set_Speed(0);
				brake();
				break;
		}		
	}

 	
    char enabled = 0;
  count = 0;
  brake();
  DDRD = (1<<7)|(1<<4)|(2<<1);
  PORTD = 1<<7;
  while(1) {  				
			char* m_c = command();
			switch(m_c[0])
			{
				case(CALIBRATE):
					unbrake();
					Set_Direction(COUNTERCLOCKWISE);
					Set_Speed(100);				
					while(!(PINB & (1<<7)));
					count = 0;
					Set_Speed(0);
					brake();
					break;
				case(IN):
					Set_Speed(0);
					brake();
					Set_Direction(COUNTERCLOCKWISE);
					Set_Speed(100);
					while(count >= 10 && (PINB & (1<<7)) == 0);
					Set_Speed(0);
					brake();
					break;
				case(OUT):
					unbrake();
					Set_Direction(CLOCKWISE);
					Set_Speed(100);
					Set_Direction(CLOCKWISE);
					Set_Speed(100);
					while(count < 1000);
					Set_Speed(0);
					brake();
					break;
		  }
		  
	  }  
  }	*/
}


