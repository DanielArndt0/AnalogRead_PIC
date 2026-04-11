/*
 * ADC library for PIC16F877A
 * Author: Daniel Gier Arndt
 * Compiler: mikroC PRO for PIC v7.2.0
 */

#ifndef ADC_H
#define ADC_H

#define ADC_INVALID_CHANNEL 0xFFFFu

void init(void);
unsigned int read(unsigned char channel);

#endif