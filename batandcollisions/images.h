#pragma once

// For uint8_t
#include <stdint.h>

// For PROGMEM
#include <avr/pgmspace.h>

uint8_t getImageHeight(const uint8_t *image) { //filmote

  return pgm_read_byte(image + 1);

}

//sprites
const uint8_t batflap[] PROGMEM
{
	// width, height,
	16, 8,
	0x40, 0x60, 0x60, 0x60, 0x70, 0x30, 0x1f, 0x3e, 0x36, 0x3f, 0x16, 0x30, 0x70, 0x70, 0x60, 0x40, 
};

const uint8_t batglide[] PROGMEM
{
	// width, height,
	16, 8,
	0x02, 0x06, 0x06, 0x0e, 0x0e, 0x0c, 0x3e, 0x7c, 0x6c, 0x7e, 0x2c, 0x0e, 0x0e, 0x0e, 0x06, 0x02, 
};

const uint8_t batdive[] PROGMEM
{
	// width, height,
	8, 16,
	0x00, 0x80, 0xe0, 0x00, 0xc0, 0x00, 0x00, 0x00, 
	0x00, 0x1f, 0x7f, 0xf8, 0xdf, 0xff, 0x58, 0x00, 
};

const uint8_t sonicbullet[] PROGMEM
{
	// width, height,
	4, 4,
	0x06, 0x09, 0x09, 0x06, 
};

//sprites for background
const uint8_t flat[] PROGMEM
{
	// width, height,
	32, 9,
	0x80, 0x40, 0xa0, 0x40, 0x80, 0x40, 0x80, 0x40, 0xa0, 0x40, 0xa0, 0x40, 0xa0, 0x50, 0x80, 0x40, 0xa0, 0x40, 0xa0, 0x40, 0xa0, 0x50, 0xa0, 0x40, 0xa0, 0x40, 0x80, 0x40, 0xa0, 0x40, 0xa0, 0x40, 
	0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 
};

const uint8_t spikeleft[] PROGMEM
{
	// width, height,
	32, 9,
	0x40, 0xa0, 0x50, 0xaa, 0x55, 0xaa, 0x50, 0x80, 0x40, 0xa0, 0x40, 0xa0, 0x40, 0x80, 0x40, 0x80, 0x40, 0xa0, 0x40, 0xa0, 0x40, 0x80, 0x00, 0xa0, 0x40, 0xa0, 0x50, 0xa0, 0x50, 0xa0, 0x50, 0xa0, 
	0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 
};

const uint8_t spikeright[] PROGMEM
{
	// width, height,
	32, 9,
	0x40, 0xa0, 0x40, 0x80, 0x00, 0x80, 0x00, 0x80, 0x40, 0xa0, 0x40, 0xa0, 0x40, 0xa0, 0x50, 0xa0, 0x50, 0xa0, 0x40, 0xa0, 0x40, 0xa0, 0x50, 0xa0, 0x50, 0xa0, 0x50, 0xaa, 0x55, 0xaa, 0x54, 0xa0, 
	0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 
};

// Ceiling
const uint8_t flatup[] PROGMEM
{
	// width, height,
	32, 9,
	0x02, 0x05, 0x0a, 0x05, 0x02, 0x05, 0x02, 0x05, 0x0a, 0x05, 0x0a, 0x05, 0x0a, 0x15, 0x02, 0x05, 0x0a, 0x05, 0x0a, 0x05, 0x0a, 0x15, 0x0a, 0x05, 0x0a, 0x05, 0x02, 0x05, 0x0a, 0x05, 0x0a, 0x05, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

const uint8_t spikeleftup[] PROGMEM
{
	// width, height,
	32, 9,
	0x05, 0x0a, 0x15, 0xaa, 0x55, 0xaa, 0x15, 0x02, 0x05, 0x0a, 0x05, 0x0a, 0x05, 0x02, 0x05, 0x02, 0x05, 0x0a, 0x05, 0x0a, 0x05, 0x02, 0x01, 0x0a, 0x05, 0x0a, 0x15, 0x0a, 0x15, 0x0a, 0x15, 0x0a, 
	0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

const uint8_t spikerightup[] PROGMEM
{
	// width, height,
	32, 9,
	0x05, 0x0a, 0x05, 0x02, 0x01, 0x02, 0x01, 0x02, 0x05, 0x0a, 0x05, 0x0a, 0x05, 0x0a, 0x15, 0x0a, 0x15, 0x0a, 0x05, 0x0a, 0x05, 0x0a, 0x15, 0x0a, 0x15, 0x0a, 0x15, 0xaa, 0x55, 0xaa, 0x55, 0x0a, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 
};

const uint8_t crowflap[] PROGMEM
{
	// width, height,
	15, 8,
	0x00, 0x00, 0x00, 0x04, 0x04, 0xae, 0xfa, 0x0e, 0x3e, 0xec, 0xac, 0x88, 0x08, 0x00, 0x00, 
};

const uint8_t crowglide[] PROGMEM
{
	// width, height,
	15, 7,
	0x01, 0x01, 0x0b, 0x09, 0x1f, 0x16, 0x5c, 0x5c, 0x3e, 0x1b, 0x13, 0x11, 0x03, 0x01, 0x01, 
};
