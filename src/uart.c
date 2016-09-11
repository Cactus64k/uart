#include "uart.h"

static int uart_putchar(char c, FILE *stream)
{
	STDOUT_BUFF* buff = fdev_get_udata(stdout);

	while(buff->count == STDOUT_BUFF_SIZE);

	buff->buff[buff->count] = c;
	buff->count++;

	UCSR0B = UCSR0B | _BV(UDRIE0);			// разрешаем прерывание по опустошению буфера УАРТА
	UCSR0A = UCSR0A | _BV(UDRE0);			// ставим флаг, на который запустится прерывание(буфер пуст)

	return 0;
}

static int uart_getchar(FILE *stream)
{
	loop_until_bit_is_set(UCSR0A, RXC0);
	return UDR0;
}

ISR(USART_UDRE_vect)
{
	STDOUT_BUFF* buff = fdev_get_udata(stdout);
	if((buff->count != 0) && (buff->pos < STDOUT_BUFF_SIZE))		// вторую проверку можно убрать
	{
		UDR0 = buff->buff[buff->pos];
		buff->pos++;

		if(buff->pos >= buff->count)
		{
			UCSR0B = UCSR0B & ~_BV(UDRIE0);
			buff->count	= 0;
			buff->pos	= 0;
		}
	}
}

void uart_init(uint64_t f_cpu, uint64_t baud)
{
	UBRR0	= (((f_cpu) + 8UL * (baud)) / (16UL * (baud)) -1UL);	// взято напрямую из setbaud.h
	UCSR0A	= 0;
	UCSR0B	= _BV(RXEN0) | _BV(TXEN0);								// приемопередача включена
	UCSR0C	= _BV(UCSZ01) | _BV(UCSZ00);							// 8 bit
}

void uart_init_stdio()
{
	static FILE f[2];
	static STDOUT_BUFF stdout_buff = {.pos=0, .count=0};
	stdout	= f;
	stdin	= f+1;

	fdev_setup_stream(stdout, uart_putchar, NULL, _FDEV_SETUP_WRITE);
	fdev_setup_stream(stdin, NULL, uart_getchar, _FDEV_SETUP_READ);

	fdev_set_udata(stdout, &stdout_buff);
}
