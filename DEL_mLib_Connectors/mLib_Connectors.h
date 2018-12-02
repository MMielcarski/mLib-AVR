/*! 
\file mLib_Connectors.h
\author Maciej Mielcarski
\date 02.12.2018
\brief pin input / output handle
tested on atmega328p
*/

#ifndef MLIB_CONNECTORS_H
#define MLIB_CONNECTORS_H

#include <avr/io.h>

#define F_CPU 16000000UL

/*!
\breif pin state check
*/
unsigned int is_pin(uint8_t pin, volatile uint8_t *pin_pin);


void pin_init(uint8_t pin, volatile uint8_t *pin_ddr, volatile uint8_t *pin_port, unsigned int b_in_or_out, unsigned int b_def_state_or_pullup);


void pin_set_state(uint8_t pin, volatile uint8_t *pin_port, volatile uint8_t *pin_pin, unsigned int mode);

#endif