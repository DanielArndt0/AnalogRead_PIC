/*
 * ADC example for PIC16F877A
 * Author: Daniel Gier Arndt
 * Compiler: mikroC PRO for PIC v7.2.0
 */

#include "adc.h"

void main()
{
  unsigned int adcValue;

  init();

  while (1)
  {
    adcValue = read(0);

    /*
     * Example:
     * - send adcValue via UART
     * - show on LCD
     * - use in control logic
     */

    Delay_ms(100);
  }
}