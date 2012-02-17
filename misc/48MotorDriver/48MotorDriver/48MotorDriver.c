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




//! Used for optimized temporary varables.
register union _fastTemp{
	unsigned int word;
	struct{
		unsigned char LByte;
		unsigned char HByte;
	};
} fastTemp asm("r12");

	
register unsigned char hallMask asm("r11");
//__regvar __no_init unsigned char hallMask @11; //!< Workaround for internal compiler error
register unsigned char count asm("r10");
//__regvar __no_init unsigned char count @10; //!< Optimized variable decremented every pin change int.



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
  unsigned char *pTemp;
  fastTemp.word = ((PIN_HALL & hallMask)>>1);  // Read Hall, Mask Pins, shift to use as pointer offset
//  Line below is desirable performance wise, but causes an internal error in compiler
//  fastTemp.LByte = (PIN_HALL & HALL_MASK)>>1;   // Read Hall, Mask Pins, shift to use as pointer offset

  pTemp = pDrvPattern + fastTemp.word;
//  TCCR0A = fastTemp.HByte; //Disable PWM outputs (and thereby close low side FET)
//  TCCR2A = fastTemp.HByte; //Disable PWM output (and thereby close low side FET)

  PORT_MC = *(pTemp);    //Change drive levels on high side

  TCCR0A = *(pTemp + PATTERN_COM0_OFFSET);    // Reconfigure output compare operation for T0
  TCCR2A = *(pTemp + PATTERN_COM2_OFFSET); // Reconfigure output compare operation for T2
  count--;
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
  PCMSK0 = (1<<PCINT1)|(1<<PCINT2)|(1<<PCINT3); //Enable pin change interrupt on PB1:3
  PCICR = 1<<PCIE0;    // Enable pin change interrupt0 (PORTB)
}



/*! \brief  Start an AD convertion and return result.
 *
 * Starts an AD conversion on the specified ADC channel and returns
 * the result when the conversin is completed. Uses polling to wait for
 * the AD conversion to complete.
 *
 *  \param channel Specify the ADMUX register settings to access the correct channel.
 *
 *  \return adcResult 8-bit result (high byte of AD convertion).
 */
unsigned char Get_ADC8(unsigned char muxSetting)
{
    ADMUX = muxSetting;
    // Start AD conversion.
    ADCSRA |= (1 << ADSC);
    // Wait for ADC conversion to complete.
    while ( ADCSRA & (1 << ADSC) );
    return ADCH;
}


//!
/*! \brief  Initialize motor control timers.
 *
 * Initialize the Timer 1 and timer 2 to run in phase and frequency correct
 * PWM mode (symmetric PWM). The base frequency is set to 32kHz (can be
 * reduced at the expense of lower resolution on the speed control). The
 * functions also ensures that the timers are counting in synch.
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
           (0<<CS02)|(0<<CS01)|(1<<CS00); // Prescaler = CLK/1

  //Timer Counter 2. OCRA and OCRB used for motor
  TCCR2A = (0<<COM2A1)|(0<<COM2A0)|        // OCRA not connected
           (1<<COM2B1)|(0<<COM2B0)|        // Clear OCRB on compare match
           (1<<WGM01)|(1<<WGM00);         // Fast PWM mode
  TCCR2B = (0<<FOC2A)|(0<<FOC2B)|
           (0<<WGM22)|                     // Fast PWM mode
           (0<<CS22)|(0<<CS21)|(1<<CS20); // Prescaler = CLK/1

  // Synchronize timers
  TCNT0 = 0;
  TCNT2 = 3;

  TIFR0 = TIFR0;    // Clear TC0 interrupt flags
  TIFR1 = TIFR1;    // Clear TC2 interrupt flags
}



/*! \brief Initialize ADC module.
 *
 * Sets up the ADC with prescaler value 4, which means a maximum sample speed
 * of CPU frequency divided by 52 (13*4). With the ADC measuring the speed set
 * point and shunt voltage, this gives a reaction time of two samples for
 * detecting over-current.
 *
 *  \param void
 *
 *  \return void
 */
static void Init_ADC( void )
{
  ADCSRA = (1 << ADEN) | (1 << ADPS1); // Enable ADC, clock prescaler = 4
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
static void Set_Speed(unsigned char speed)
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
static void Set_Direction(unsigned char direction)
{
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
  unsigned char speed = 0;
  unsigned char setspeed = 0;
  signed int current;
  MCUCR |= (1<<PUD);  // Disable all pull-ups
  hallMask = HALL_MASK; // Initialize hallMask variable
  //Set initial direction.
  Set_Direction( CLOCKWISE );

  Init_MC_timers();
  Init_MC_pin_change_interrupt();
  Init_ADC();

  DDR_HALL |= HALL_MASK;    //Lock HALL sensor by driving Hall lines
  PORT_HALL |= HALL_MASK;
  PORT_HALL &= ~HALL_MASK;  //Release HALL sensor lines and trigger PC interrupt
  DDR_HALL &= ~HALL_MASK;
  sei();
  Set_Speed(speed);
  DDR_MC = MC_MASK;        // Enable outputs

  DDRC |= (1<<PC1);
  for(;;) {
    // Get shunt voltage (current measurement)
    current = Get_ADC8(ADC_MUX_SHUNT_H);
    // If current consumption is too high, limit current
    if (current > MAX_CURRENT_ADC )
    {
      PORTC &= ~(1<<OVERCURRENT_PIN);   //Turn on over-current LED (active low)
      if( speed >= 2 )
      {
        speed -= 2; // Slow down if too fast.
      }
    }
    else
    {
      PORTC |= (1<<OVERCURRENT_PIN); // Turn off over-current LED (active low)
      // Get speed reference voltage (Assumes 2.5V to be maximum analog input,
      // multiplied by 2 to convert to PWM range).
      setspeed = Get_ADC8(ADC_MUX_SPEED_REF)*2;
      // Approach speed set point.
      if( setspeed > speed )
      {
        ++speed;
      }
      else
      {
        if( setspeed < speed )
        {
          --speed;
        }
      }
    }

    Set_Speed(speed);
  }
  return 0;
}

