#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>
#include "utils.h"
#include "defs.h"
#include "TinyI2C.h"
#include <avr/pgmspace.h>

uint8_t ss = 0, mm = 0, hh = 0, d = 0, m = 0;
uint16_t y = 0;

void sleep()
{

    GIMSK |= _BV(PCIE);                  // Enable Pin Change Interrupts
    PCMSK |= _BV(PCINT1);                // Use PB1 as interrupt pin
    ADCSRA &= ~_BV(ADEN);                // ADC off
    set_sleep_mode(SLEEP_MODE_PWR_DOWN); // replaces above statement

    sleep_enable(); // Sets the Sleep Enable bit in the MCUCR Register (SE BIT)
    sei();          // Enable interrupts
    sleep_cpu();    // sleep

    cli();                 // Disable interrupts
    PCMSK &= ~_BV(PCINT1); // Turn off PB1 as interrupt pin
    sleep_disable();       // Clear SE bit
    ADCSRA |= _BV(ADEN);   // ADC on

    sei(); // Enable interrupts
} // sleep

ISR(PCINT0_vect)
{
    // This is called when the interrupt occurs, but I don't need to do anything in it
}

int main()
{

    TinyI2C.initMaster();

    SetClock(0x05, 0x46, 0x00);

    //Set PB3 and PB4 to output
    DDRB |= (1 << PB3);
    DDRB |= (1 << PB4);

    while (1)
    {

        //Get Current Time
        TinyI2C.start(DS1307, 0);
        TinyI2C.write(0);
        TinyI2C.restart(DS1307, 7);
        ss = TinyI2C.read();
        mm = TinyI2C.read();
        hh = TinyI2C.read();
        TinyI2C.read();
        d = TinyI2C.read();
        m = TinyI2C.read();
        y = TinyI2C.read() + 2000;
        TinyI2C.stop();

        // Adjust for 12 hour clock
        if (hh > 12)
        {
            hh = hh - 12;
        }
        mm = 9;

        updateDisplay(hh, mm);

        sleep();
    }
}
