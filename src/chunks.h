#ifndef CHUNKS_H_
	#define CHUNKS_H_

	#ifndef FCPU
		#define F_CPU 16000000UL
	#endif

	#ifndef DEVICE
		#define DEVICE atmega325p
	#endif

	#ifndef BAUD
		#define BAUD 9600
	#endif

	#ifndef __AVR_ATmega328P__
		#define __AVR_ATmega328P__
	#endif

	#include <avr/io.h>
	#include <util/delay.h>
	#include <stdint.h>
	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	#include <util/setbaud.h>
	#include <avr/interrupt.h>


#endif /* CHUNKS_H_ */
