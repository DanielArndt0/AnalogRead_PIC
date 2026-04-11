/*
 * ADC library for PIC16F877A
 * Author: Daniel Gier Arndt
 * Compiler: mikroC PRO for PIC v7.2.0
 */

#include "adc.h"

void init(void)
{
  unsigned short clk;

  clk = Clock_MHz();

  /*
   * ADC clock selection
   */
  if (clk <= 1)
  {
    ADCON0.ADCS0 = 0;
    ADCON0.ADCS1 = 0;
    ADCON1.ADCS2 = 0;
  }
  else if (clk <= 2)
  {
    ADCON0.ADCS0 = 0;
    ADCON0.ADCS1 = 0;
    ADCON1.ADCS2 = 1;
  }
  else if (clk <= 5)
  {
    ADCON0.ADCS0 = 1;
    ADCON0.ADCS1 = 0;
    ADCON1.ADCS2 = 0;
  }
  else if (clk <= 10)
  {
    ADCON0.ADCS0 = 1;
    ADCON0.ADCS1 = 0;
    ADCON1.ADCS2 = 1;
  }
  else
  {
    ADCON0.ADCS0 = 0;
    ADCON0.ADCS1 = 1;
    ADCON1.ADCS2 = 1;
  }

  /* Right justified result */
  ADCON1.ADFM = 1;

  /* Configure all supported ADC pins as analog */
  ADCON1.PCFG0 = 0;
  ADCON1.PCFG1 = 0;
  ADCON1.PCFG2 = 0;
  ADCON1.PCFG3 = 0;

  /* Enable ADC */
  ADCON0.ADON = 1;
}

unsigned int read(unsigned char channel)
{
  if (channel > 7)
  {
    return ADC_INVALID_CHANNEL;
  }

  /* Clear CHS2:CHS0 and set new channel */
  ADCON0 &= 0xC7;
  ADCON0 |= (channel << 3);

  /* Acquisition time */
  Delay_us(20);

  /* Start conversion */
  ADCON0.GO_NOT_DONE = 1;
  while (ADCON0.GO_NOT_DONE)
    ;

  return ((unsigned int)ADRESH << 8) | ADRESL;
}