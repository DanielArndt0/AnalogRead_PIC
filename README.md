# Analog read for PIC

ADC reading example for the **PIC16F877A** using **MikroC PRO**.

## Overview

This repository contains a simple and didactic example of **analog-to-digital conversion (ADC)** on the `PIC16F877A`.  
The project provides a custom ADC library with initialization and reading routines for analog channels **AN0 to AN7**.

It is intended as a basic embedded systems example for students, hobbyists, and developers working with **PIC microcontrollers**.

## Platform and Development Environment

- **Microcontroller:** `PIC16F877A`
- **Language:** `C`
- **IDE:** `MikroC PRO v7.2.0`

## Project Files

- `src/main.c` — example application using the ADC library
- `src/adc.c` — ADC implementation
- `src/adc.h` — ADC public interface
- `docs/pic16f877a.pdf` — PIC16F877A documentation

## Features

- ADC peripheral initialization
- Analog channel selection from `AN0` to `AN7`
- 10-bit conversion result reading
- Reusable ADC module split into `.h` and `.c`
- Example structure for integrating ADC into larger PIC projects

## How It Works

### `init(void)`

Configures the ADC peripheral:

- selects ADC clock settings based on MCU frequency
- sets result formatting
- configures pins for analog input operation
- enables the ADC module

### `read(unsigned char channel)`

Performs one ADC conversion on the selected channel:

- validates the ADC channel
- selects the ADC channel
- waits for acquisition time
- starts conversion
- waits until conversion finishes
- combines `ADRESH` and `ADRESL`
- returns the 10-bit conversion result

## Example Usage

```c
#include "adc.h"

void main()
{
    unsigned int value;

    init();

    while (1)
    {
        value = read(0);   // Read AN0
        Delay_ms(100);
    }
}
```

## ADC Channels

This implementation supports the following analog inputs:

- `0` → `AN0`
- `1` → `AN1`
- `2` → `AN2`
- `3` → `AN3`
- `4` → `AN4`
- `5` → `AN5`
- `6` → `AN6`
- `7` → `AN7`

## Returned Value

The ADC result is a **10-bit value**, so the returned range is:

- **0** → minimum analog input
- **1023** → maximum analog input

For invalid channels, the function returns:

- `ADC_INVALID_CHANNEL`

## Author

[**Daniel Gier Arndt**](https://github.com/DanielArndt0)

This project is a small embedded systems study/example repository focused on ADC reading with the `PIC16F877A`.
