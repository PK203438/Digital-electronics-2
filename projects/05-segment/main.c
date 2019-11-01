/*
 * ---------------------------------------------------------------------
 * Author:      Tomas Fryza
 *              Dept. of Radio Electronics, Brno Univ. of Technology
 * Created:     2018-09-27
 * Last update: 2019-09-26
 * Platform:    ATmega328P, AVR 8-bit Toolchain 3.6.2
 * ---------------------------------------------------------------------
 * Description: Blink a LED with delay function.
 * TODO: Verify functionality of LED blinker.
 * NOTE: Macro _BV converts a bit number into a byte value (see AVR Libc
 * Reference Manual).
 */

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

/* Typedef -----------------------------------------------------------*/
/* Define ------------------------------------------------------------*/
#define SDATA   PB0
#define CLK   PD7
#define LATCH   PD4
//#define BLINK_DELAY 500

/* Variables ---------------------------------------------------------*/
/* Function prototypes -----------------------------------------------*/

/* Functions ---------------------------------------------------------*/
/**
  * Brief:  Main program. Blink a LED with delay function.
  * Input:  None
  * Return: None
  */
int main(void)
{
    uint8_t digit = 0b11000000; // DP g f e d c b a
    uint8_t position = 0b10100001; // x x x x 0 1 2 3
    // /* Set output pin */
    // DDRB |= _BV(LED_GREEN);         /* DDRB = DDRB or (0010 0000) */
    // DDRB |= _BV(LED_RED);

    // /* Turn LED off */
    // PORTB &= ~_BV(LED_GREEN);       /* PORTB = PORTB and (0010 0000) */
    // PORTB &= ~_BV(LED_RED);

    // /* Infinite loop */
    // for (;;)
    // {
    //     /* Invert LED and delay */
    //     PORTB ^= _BV(LED_GREEN);    /* PORTB = PORTB xor (0010 0000) */
    //     PORTB ^= _BV(LED_RED);
    //     _delay_ms(BLINK_DELAY);     /* Wait for several milisecs */
    // }

    // DDRB |= _BV(LED_GREEN);
    // DDRB |= _BV(LED_RED);
    // //PORTB &= ~_BV(LED_GREEN);
    // TCCR1B |= _BV(CS11) | _BV(CS10);
    // TIMSK1 |= _BV(TOIE1);
    // TCCR0B |= _BV(CS02) | _BV(CS00);
    // TIMSK0 |= _BV(TOIE0);

    // sei();

    // while (1);

    DDRB |= _BV(SDATA);
    DDRD |= _BV(CLK) | _BV(LATCH);

    for (uint8_t i = 0; i < 8; i++)
    {
        if ((digit & _BV(7-i)) == 0)
          PORTB &= ~_BV(SDATA);
        else 
          PORTB |= _BV(SDATA);
          
        PORTD &= ~_BV(CLK);
        _delay_us(1);
        PORTD |= _BV(CLK);
        _delay_us(1);
    }

    for (uint8_t i = 0; i < 8; i++)
    {
        if ((position & _BV(7-i)) == 0)
          PORTB &= ~_BV(SDATA);
        else 
          PORTB |= _BV(SDATA);
          
        PORTD &= ~_BV(CLK);
        _delay_us(1);
        PORTD |= _BV(CLK);
        _delay_us(1);
    }

    PORTD &= ~_BV(LATCH);
    _delay_us(1);
    PORTD |= _BV(LATCH);
    _delay_us(1);

    return (0);
}

// ISR(TIMER1_OVF_vect)
// {
//   PORTB ^= _BV(LED_GREEN);
// }

// ISR(TIMER0_OVF_vect)
// {
//   PORTB ^= _BV(LED_RED);
// }
