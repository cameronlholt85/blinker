#include "defs.h"
#include <stdio.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <string.h>
#include "utils.h"
#include <stdlib.h>

void SetClock(int hr, int min, int sec)
{
    TinyI2C.start(DS1307, 0);
    TinyI2C.write(0);
    TinyI2C.write(sec);
    TinyI2C.write(min);
    TinyI2C.write(hr);
    TinyI2C.write(0);
    TinyI2C.write(0x01);
    TinyI2C.write(0x01);
    TinyI2C.write(0x01);
    TinyI2C.write(0);
    TinyI2C.stop();
}

void WriteCommand(int commandArray[], uint8_t commandArraySize)
{

    TinyI2C.start(SSD1306, 0);
    TinyI2C.write(COMMANDS);
    for (int i = 0; i < commandArraySize; i++)
    {
        TinyI2C.write(commandArray[i]);
    }
    TinyI2C.stop();
}

void WriteSingleCommand(int command)
{
    TinyI2C.start(SSD1306, 0);
    TinyI2C.write(COMMANDS);
    TinyI2C.write(command);
    TinyI2C.stop();
}

// Write a single command
void Single(uint8_t x)
{
    TinyI2C.write(ONECOMMAND);
    TinyI2C.write(x);
}

bool digitalRead(void)
{
    uint8_t x;
    x = PINB & 0x02;
    if (x == 2)
        return 1;

    return 0;
}

void dec2bin(int num)
{

    bool binArray[8] = {};

    int tmp = num;

    for (int i = 4; i > 0; i--)
    {
        binArray[i - 1] = tmp % 2;
        tmp = tmp / 2;
    }

    for (int i = 0; i < 4; i++)
    {
        if (binArray[i])
        {
            PORTB |= (1 << PB3);  //HIGH
            PORTB &= ~(1 << PB4); //LOW
        }
        else
        {
            PORTB |= (1 << PB4);  //HIGH
            PORTB &= ~(1 << PB3); //LOW
        }
        _delay_ms(500);

        PORTB &= ~(1 << PB3); //LOW
        PORTB &= ~(1 << PB4); //LOW
        _delay_ms(200);
    }
}

void updateDisplay(int hh, int mm)
{
    dec2bin(hh);

    dec2bin(mm);
}
