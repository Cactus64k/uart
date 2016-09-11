#ifndef UART_H_
	#define UART_H_

	#include <stdio.h>
	#include <avr/interrupt.h>
	#include <stdint.h>
	#include <stdlib.h>


	#define STDOUT_BUFF_SIZE 16

	typedef struct STDOUT_BUFF
	{
		uint8_t pos;
		volatile uint8_t count;
		uint8_t buff[STDOUT_BUFF_SIZE];

	} STDOUT_BUFF;

	void uart_init_stdio();
	void uart_init(uint64_t f_cpu, uint64_t baud);

#endif /* UART_H_ */
