/* This file has been prepared for Doxygen automatic documentation generation.*/
/*! \file *********************************************************************
 *
 * \brief A brief description of the file is written here.
 *
 * A more detailed description of the file should written here.
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
 * $Revision: 843 $
 * $RCSfile$
 * $Date: 2006-02-17 20:35:38 +0100 (fr, 17 feb 2006) $  \n
 ******************************************************************************/

//! \name Output pins to drive stages.
//@{
#define UL  PD6
#define VL  PD5
#define WL  PD3
#define UH  PD7
#define VH  PD4
#define WH  PD2
#define MC_MASK   ((1<<UL)|(1<<VL)|(1<<WL)|(1<<UH)|(1<<VH)|(1<<WH))
//@}



//! \name Port control registers for drive stages.
//@{
#define PORT_MC PORTD
#define DDR_MC  DDRD
#define PIN_MC  PIND
//@}



//! \name Hall sensor input pins.
//@{
#define HALL1 PB1
#define HALL2 PB2
#define HALL3 PB3
#define HALL_MASK  ((1<<HALL1)|(1<<HALL2)|(1<<HALL3))
//@}



//! \name Port control registers for Hall sensor inputs.
//@{
#define PORT_HALL PORTB
#define DDR_HALL  DDRB
#define PIN_HALL  PINB
//@}



#define PATTERN_DRV_OFFSET  0 //!< Offset for drive pattern in table.
#define PATTERN_COM0_OFFSET 6 //!< Offset for Timer 0 Output Compare config pattern in table.
#define PATTERN_COM2_OFFSET 12 //!< Offset for Timer 2 Output Compare config pattern in table.



/*! \name CCW driving configuration
 *
 *  IO driving configuration (driving enabled by setting
 *  IO to output)for counter clockwise rotation.
 */
//@{
#define PDP1_CCW  ((1<<UL)|(0<<VL)|(0<<WL)|(0<<UH)|(1<<VH)|(0<<WH))
#define PDP2_CCW  ((1<<UL)|(0<<VL)|(0<<WL)|(0<<UH)|(0<<VH)|(1<<WH))
#define PDP3_CCW  ((0<<UL)|(1<<VL)|(0<<WL)|(0<<UH)|(0<<VH)|(1<<WH))
#define PDP4_CCW  ((0<<UL)|(1<<VL)|(0<<WL)|(1<<UH)|(0<<VH)|(0<<WH))
#define PDP5_CCW  ((0<<UL)|(0<<VL)|(1<<WL)|(1<<UH)|(0<<VH)|(0<<WH))
#define PDP6_CCW  ((0<<UL)|(0<<VL)|(1<<WL)|(0<<UH)|(1<<VH)|(0<<WH))
//@}



/*! \name CW driving configuration
 *
 *  IO driving configuration (driving enabled by setting
 *  IO to output)for clockwise rotation.
 */
//@{
#define PDP1_CW  ((0<<UL)|(0<<VL)|(1<<WL)|(0<<UH)|(1<<VH)|(0<<WH))
#define PDP2_CW  ((0<<UL)|(0<<VL)|(1<<WL)|(1<<UH)|(0<<VH)|(0<<WH))
#define PDP3_CW  ((0<<UL)|(1<<VL)|(0<<WL)|(1<<UH)|(0<<VH)|(0<<WH))
#define PDP4_CW  ((0<<UL)|(1<<VL)|(0<<WL)|(0<<UH)|(0<<VH)|(1<<WH))
#define PDP5_CW  ((1<<UL)|(0<<VL)|(0<<WL)|(0<<UH)|(0<<VH)|(1<<WH))
#define PDP6_CW  ((1<<UL)|(0<<VL)|(0<<WL)|(0<<UH)|(1<<VH)|(0<<WH))
//@}

#define OVERCURRENT_PIN PC1   //!< Over-current LED signalling (active low).

//! \name PWM output configuration (for both TC0 and TC2)
//@{
#define UL_ON   ((1<<COM0A1)|(0<<COM0A0))
#define UL_OFF  ((0<<COM0A1)|(0<<COM0A0))
#define VL_ON   ((1<<COM0B1)|(0<<COM0B0))
#define VL_OFF  ((0<<COM0B1)|(0<<COM0B0))
#define WL_ON   ((1<<COM2B1)|(0<<COM2B0))
#define WL_OFF  ((0<<COM2B1)|(0<<COM2B0))

#define COM0P1_CCW  ((UL_ON)|(VL_OFF)|(1<<WGM01)|(1<<WGM00))
#define COM2P1_CCW  ((WL_OFF)|(1<<WGM21)|(1<<WGM20))
#define COM0P2_CCW  ((UL_ON)|(VL_OFF)|(1<<WGM01)|(1<<WGM00))
#define COM2P2_CCW  ((WL_OFF)|(1<<WGM21)|(1<<WGM20))
#define COM0P3_CCW  ((UL_OFF)|(VL_ON)|(1<<WGM01)|(1<<WGM00))
#define COM2P3_CCW  ((WL_OFF)|(1<<WGM21)|(1<<WGM20))
#define COM0P4_CCW  ((UL_OFF)|(VL_ON)|(1<<WGM01)|(1<<WGM00))
#define COM2P4_CCW  ((WL_OFF)|(1<<WGM21)|(1<<WGM20))
#define COM0P5_CCW  ((UL_OFF)|(VL_OFF)|(1<<WGM01)|(1<<WGM00))
#define COM2P5_CCW  ((WL_ON)|(1<<WGM21)|(1<<WGM20))
#define COM0P6_CCW  ((UL_OFF)|(VL_OFF)|(1<<WGM01)|(1<<WGM00))
#define COM2P6_CCW  ((WL_ON)|(1<<WGM21)|(1<<WGM20))

#define COM0P1_CW  ((UL_OFF)|(VL_OFF)|(1<<WGM01)|(1<<WGM00))
#define COM2P1_CW  ((WL_ON)|(1<<WGM21)|(1<<WGM20))
#define COM0P2_CW  ((UL_OFF)|(VL_OFF)|(1<<WGM01)|(1<<WGM00))
#define COM2P2_CW  ((WL_ON)|(1<<WGM21)|(1<<WGM20))
#define COM0P3_CW  ((UL_OFF)|(VL_ON)|(1<<WGM01)|(1<<WGM00))
#define COM2P3_CW  ((WL_OFF)|(1<<WGM21)|(1<<WGM20))
#define COM0P4_CW  ((UL_OFF)|(VL_ON)|(1<<WGM01)|(1<<WGM00))
#define COM2P4_CW  ((WL_OFF)|(1<<WGM21)|(1<<WGM20))
#define COM0P5_CW  ((UL_ON)|(VL_OFF)|(1<<WGM01)|(1<<WGM00))
#define COM2P5_CW  ((WL_OFF)|(1<<WGM21)|(1<<WGM20))
#define COM0P6_CW  ((UL_ON)|(VL_OFF)|(1<<WGM01)|(1<<WGM00))
#define COM2P6_CW  ((WL_OFF)|(1<<WGM21)|(1<<WGM20))

#define HP1 ((1<<HALL1)|(0<<HALL2)|(1<<HALL3))
#define HP2 ((1<<HALL1)|(0<<HALL2)|(0<<HALL3))
#define HP3 ((1<<HALL1)|(1<<HALL2)|(0<<HALL3))
#define HP4 ((0<<HALL1)|(1<<HALL2)|(0<<HALL3))
#define HP5 ((0<<HALL1)|(1<<HALL2)|(1<<HALL3))
#define HP6 ((0<<HALL1)|(0<<HALL2)|(1<<HALL3))
//@}


// Direction control
#define CLOCKWISE         1 //!< Used by Set_Direction() for CW rotation.
#define COUNTERCLOCKWISE  0 //!< Used by Set_Direction() for CCW rotation.



//! \name ADC multiplexing
//@{
#define ADC_MUX_SPEED_REF   ((0 << REFS1) | (0 << REFS0) | (1 << ADLAR))
#define ADC_MUX_SHUNT_H     ((0 << REFS1) | (0 << REFS0) | (1 << ADLAR) | (1 << MUX2))
#define ADC_MUX_SHUNT_L     ((0 << REFS1) | (0 << REFS0) | (1 << ADLAR) | (1 << MUX2) | (1 << MUX0))
//@}



// Current limiting
#define MAX_CURRENT                     1.0f   //!< Max motor current in Amperes.
#define CURRENT_SHUNT_RESISTANCE        0.22f  //!< Current shunt resistanse in Ohms.
#define ADC_REF_VOLTAGE                 5.0f   //!< ADC reference voltage in Volts.

#define VOLTS_PER_ADC_STEP              (ADC_REF_VOLTAGE / 256)  //!< Volts per LSB with 8-bit ADC.
#define MAX_SHUNT_VOLTAGE               (MAX_CURRENT * CURRENT_SHUNT_RESISTANCE)  //!< Max current shunt voltage.
#define MAX_CURRENT_ADC                 (signed int)(MAX_SHUNT_VOLTAGE / VOLTS_PER_ADC_STEP) //!< Calc max value for raw ADC reading.
