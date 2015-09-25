/*
 * ex1_basic_led.c
 *  Author: thibaut.viard
 */ 

#include "sam.h"

/*
 * LED0 definitions
 */
#define LED0_PIO   PIOD
#define LED0_PIN   PIO_PD22

/**
 * \brief Application entry point.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main(void)
{
  // Disable Watchdog
  WDT->WDT_MR = WDT_MR_WDDIS ;

  // Assign the LED1 pin as OUTPUT
  LED0_PIO->PIO_OER=LED0_PIN ;
  // Clear the LED1 pin level, ie put to 0V -> the pin is connected to the LED cathode, anode is connected to +3.3V.
  LED0_PIO->PIO_CODR=LED0_PIN ;
}

