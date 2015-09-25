#include "sam.h"

#ifdef __cplusplus
extern "C" {
#endif

#define __SYSTEM_CLOCK_4MHZ            (4000000UL)
#define __SYSTEM_CLOCK_120MHZ          (120000000UL)

/* Clock Settings (4MHz) using Internal Fast RC */
uint32_t SystemCoreClock = __SYSTEM_CLOCK_4MHZ ;

/**
 * \brief Setup the microcontroller system.
 *
 * Initialize the System and update the SystemFrequency variable.
 */
void SystemInit( void )
{
  /* Set 6 FWS for Embedded Flash Access */
  EFC->EEFC_FMR = EEFC_FMR_FWS(5) | EEFC_FMR_CLOE ;

	/* Initialize main oscillator */
	if ( !(PMC->CKGR_MOR & CKGR_MOR_MOSCSEL) )
  {
  	PMC->CKGR_MOR = CKGR_MOR_KEY_PASSWD | CKGR_MOR_MOSCXTST(0x8U) | CKGR_MOR_MOSCRCEN | CKGR_MOR_MOSCXTEN ;
  	while ( !(PMC->PMC_SR & PMC_SR_MOSCXTS) ) ;
	}

	/* Switch to 3-20MHz Xtal oscillator */
	PMC->CKGR_MOR = CKGR_MOR_KEY_PASSWD | CKGR_MOR_MOSCXTST(0x8U) | CKGR_MOR_MOSCRCEN | CKGR_MOR_MOSCXTEN | CKGR_MOR_MOSCSEL;
	while ( !(PMC->PMC_SR & PMC_SR_MOSCSELS) ) ;

	PMC->PMC_MCKR = (PMC->PMC_MCKR & ~(uint32_t)PMC_MCKR_CSS_Msk) | PMC_MCKR_CSS_MAIN_CLK ;
	while ( !(PMC->PMC_SR & PMC_SR_MCKRDY) ) ;

	/* Initialize PLLA */
	PMC->CKGR_PLLAR = CKGR_PLLAR_ONE | CKGR_PLLAR_MULA(0x13U) | CKGR_PLLAR_PLLACOUNT(0x3fU) | CKGR_PLLAR_DIVA(0x1U) ;
	while ( !(PMC->PMC_SR & PMC_SR_LOCKA) ) ;

	/* Switch to main clock */
	PMC->PMC_MCKR = ((PMC_MCKR_PRES_CLK_2 | PMC_MCKR_CSS_PLLA_CLK) & ~PMC_MCKR_CSS_Msk) |	PMC_MCKR_CSS_MAIN_CLK ;
	while ( !(PMC->PMC_SR & PMC_SR_MCKRDY) ) ;

	/* Switch to PLLA */
	PMC->PMC_MCKR = PMC_MCKR_PRES_CLK_2 | PMC_MCKR_CSS_PLLA_CLK ;
	while ( !(PMC->PMC_SR & PMC_SR_MCKRDY) ) ;

  SystemCoreClock=__SYSTEM_CLOCK_120MHZ ;
}

/**
 * \brief Get Core Clock Frequency.
 */
void SystemCoreClockUpdate( void )
{
}

#ifdef __cplusplus
}
#endif
