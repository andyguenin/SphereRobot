/* Doxygen documentation mainpage ********************************************/
/*! \mainpage
 * \section intro Introduction
 * This documents the software for application note AVR443. This is an example
 * of how to use an ATmega48/88/168 to control a three phase BLDC motor with
 * hall sensors.
 *
 * \section compinfo Compilation Info
 * This software was compiled with IAR Embedded Workbench, 4.12A. Details about
 * compiler settings can be found in "related pages".\n
 *
 * \section deviceinfo Device Info
 * The code is targeting ATmega48/88/168. The concepts used can also be applied
 * when using other AVRs, though some rewriting of the code will be required.
 *
 * \section contactinfo Contact Info
 * For more info about Atmel AVR visit http://www.atmel.com/products/AVR/ \n
 * For application notes visit
 * http://www.atmel.com/dyn/products/app_notes.asp?family_id=607 \n
 * Support mail: avr@atmel.com
 */

/*! \page comp_set Compiler settings
 * This code has been compiled and tested using the AIR EWAVR 4.12A compiler.\n
 * \n
 * The following file(s) should be added to the IAR project:
 *    - sensor_three_phase_BLDC.c
 *    - info.h (no code, only documentation).
 *
 * The compiler settings (Project options) should be set as follows
 * to compile the code:
 *    - Processor configuration = ATmega48 (in General Options->Target).
 *    - Enable bit definitions in I/O-Include file (in General Options->System).
 *    - Lock for global variables = 6 (in Compiler C/C++ ->Code).
 *    - Linker output format for debug = UBROF8 (in Linker->output).
 *    - Linker output format for release = Intel extended hex (in Linker->output).
 *    - Optimization settings
 *         - Release = high speed optimization (cross call enabled).
 *         - Debug = low size optimization (default).
 *
 * Compiler output files can be found in the debug and release directories.
 * The debug output (UBROF8 format) is using low optimization, while the
 * release output (intel extended hex format) is using high optimization (default
 * is size optimization).\n
 * Code size for release is 427 bytes.
 */

/*! \page hw_conf Hardware configuration
 * The hardware configuration (pin used) can be changed in the
 * sensor_three_phase_BLDC.h file. \n
 * \n
 * The default configuration for hall sensor inputs are:
 *    - HALL1 = PB1
 *    - HALL2 = PB2
 *    - HALL3 = PB3
 *
 * The default configuration for driver control signals are:
 *    - UL = PD6
 *    - VL = PD5
 *    - WL = PD3
 *    - UH = PD7
 *    - VH = PD4
 *    - WH = PD2
 *
 * The default input for speed reference and overcurrent are:
 *    - Speed reference = ADC0 = PC0
 *    - Overcurrent = ADC4 = PC4
 */

/*! \page ana_input Analog inputs
 * The implementation is designed to use a 5V voltage reference. The ADC is
 * configured to use external reference, and therefore 5V must be applied on
 * AREF externally. If STK500 is used, connect the AREF jumper and configure
 * STK500 to provide a 5V reference (from AVR Studio).\n
 * \n
 * The analog input used as speed reference is in the range 0-2.5V.\n
 * \n
 * The overvoltage detection is set to 1A, assuming that a 0.22 ohm shunt
 * resistor is used. The OVERCURRENT_PIN is drawn low when over current is
 * detected.
*/