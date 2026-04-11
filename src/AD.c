/*
 * ADC example for PIC16F877A
 * Author: Daniel Gier Arndt
 * Compiler: mikroC PRO for PIC v7.2.0
 */

#define ADC_INVALID_CHANNEL 0xFFFF

void init(void);
unsigned int analogRead(unsigned char channel);

void main()
{
  unsigned int adcValue;

  init();

  while (1)
  {
    adcValue = analogRead(0);

    /*
     * Example:
     * - send adcValue via UART
     * - show on LCD
     * - use in control logic
     */

    Delay_ms(100);
  }
}

void init(void)
{
  unsigned short clk;

  clk = Clock_MHz();

  /*
   * ADC clock selection
   * Keep your original logic, but fix range coverage.
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

  /*
   * Configure analog inputs.
   * Here you are keeping all ADC channels available.
   */
  ADCON1.PCFG0 = 0;
  ADCON1.PCFG1 = 0;
  ADCON1.PCFG2 = 0;
  ADCON1.PCFG3 = 0;

  /* Enable ADC once */
  ADCON0.ADON = 1;
}

unsigned int analogRead(unsigned char channel)
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