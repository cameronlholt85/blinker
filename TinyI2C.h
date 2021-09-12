#include <avr/io.h>
#include "defs.h"

#ifndef TinyI2C__h
#define TinyI2C__h

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>

#define DELAY_T2TWI (_delay_us(2)) // >1.3us
#define DELAY_T4TWI (_delay_us(1)) // >0.6us

#define TWI_NACK_BIT 0 // Bit position for (N)ACK bit.

// Constants
// Prepare register value to: Clear flags, and set USI to shift 8 bits i.e. count 16 clock edges.
const unsigned char USISR_8bit = 1 << USISIF | 1 << USIOIF | 1 << USIPF | 1 << USIDC | 0x0 << USICNT0;
// Prepare register value to: Clear flags, and set USI to shift 1 bit i.e. count 2 clock edges.
const unsigned char USISR_1bit = 1 << USISIF | 1 << USIOIF | 1 << USIPF | 1 << USIDC | 0xE << USICNT0;

class TinyI2C_
{

  public:
	TinyI2C_();
	void initMaster(void);
	uint8_t read(void);
	uint8_t readLast(void);
	bool write(uint8_t data);
	bool start(uint8_t address, int readcount);
	bool restart(uint8_t address, int readcount);
	void stop(void);

  private:
	int I2Ccount;
	uint8_t transfer(uint8_t data);
};

extern TinyI2C_ TinyI2C;

#endif
