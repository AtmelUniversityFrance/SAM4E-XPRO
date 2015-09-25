/*
 * ex2_basic_button.c
 *  Author: thibaut.viard
 */ 

#include "sam.h"

/*
 * LED0 definitions
 */
#define LED0_PIO   PIOD
#define LED0_PIN   PIO_PD22

/*
 * SW0 definitions
 */
#define SW0_PIO    PIOA
#define SW0_PIN    PIO_PA2
#define SW0_PID    ID_PIOA

// Global state variable for LED toggle
static uint32_t ul_toggle=0 ;

/*
 * \brief Initialization of board components.
 *
 */
void hardware_init( void )
{
  // Assign the LED0 pin as OUTPUT
  LED0_PIO->PIO_OER = LED0_PIN ;
  // Clear the LED0 pin level, ie put to 0V -> the pin is connected to the LED cathode, anode is connected to +3.3V.
  LED0_PIO->PIO_CODR = LED0_PIN ;
  
  // Assign the SW0 pin as INPUT
  SW0_PIO->PIO_ODR = SW0_PIN ;

  // Clock the SW0 associated PIO, to allow input measure
  PMC->PMC_PCER0 = 1 << SW0_PID ;
}

/*
 * \brief Toggle the LED.
 *
 */
void toggle_LED( void )
{
  if ( ul_toggle == 0 )
  {
    // Set the LED0 pin level, ie put to 3.3V -> this light off the LED
    LED0_PIO->PIO_SODR=LED0_PIN ;

	ul_toggle=1 ;
  }
  else
  {
    // Clear the LED0 pin level, ie put to 0V -> this light on the LED
    LED0_PIO->PIO_CODR=LED0_PIN ;

    ul_toggle=0 ;
  }
}


/**
 * \brief Application entry point.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main( void )
{
  // Disable Watchdog
  WDT->WDT_MR = WDT_MR_WDDIS ;

  // Initialize hardware
  hardware_init() ;

  while ( 1 )
  {
    if ( (SW0_PIO->PIO_PDSR & SW0_PIN) == 0 )
    {
      toggle_LED() ;
    }
  }
}


