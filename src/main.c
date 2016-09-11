#include "uart.h"
#include "chunks.h"

#define LED_PIN PB5
#define GREEN_LED_PIN PB4


int main(void)
{
	uart_init_stdio();
	uart_init(F_CPU, BAUD);

	//#####################################

	ADMUX	= _BV(REFS0) | _BV(REFS1) | _BV(MUX3);					// внутренний источник на 1.1 вольт и температурный сенсор
	ADCSRA	= _BV(ADEN) | _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);		// предделитель на 128

	//#####################################

	sei();

	DDRB = DDRB | _BV(LED_PIN);
	DDRB = DDRB | _BV(GREEN_LED_PIN);

	while(1)
	{
		ADCSRA	= ADCSRA | _BV(ADSC);
		loop_until_bit_is_set(ADCSRA, ADIF);
		uint16_t val	= (ADCW - 324.31 ) / 1.22;
		_delay_ms(1000);
		printf("temp = %d\n", val);

		_delay_ms(200);
	}
}
